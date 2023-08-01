/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-16 21:26:06
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-08-01 16:11:42
 * @ Description:
 */

#include "MultiPartAnimation.hpp"
#include "logger.hpp"
#include "json.hpp"
#include "parsing.hpp"

namespace bya::Animation {

    void MultiPartAnimation::addKeyframe(std::shared_ptr<Keyframe> keyframe)
    {
        if (m_keyframesMap.find(keyframe->getEntity()) == m_keyframesMap.end()) {
            m_keyframesMap[keyframe->getEntity()] = std::vector<std::shared_ptr<Keyframe>>();
        }

        // if there is already a keyframe at this time, replace it
        for (unsigned int i = 0; i < m_keyframesMap[keyframe->getEntity()].size(); i++) {
            if (m_keyframesMap[keyframe->getEntity()][i]->getTime() == keyframe->getTime()) {
                logger::warn("Keyframe at time {" + std::to_string(keyframe->getTime()) + "} already exists, replacing it");
            }
        }

        m_keyframesMap[keyframe->getEntity()].push_back(keyframe);
        sortKeyframes();
    }

    void MultiPartAnimation::removeKeyframe(std::shared_ptr<gameObj::IMultPartEntity> entity, float time)
    {
        if (m_keyframesMap.find(entity) == m_keyframesMap.end()) {
            return;
        }

        for (unsigned int i = 0; i < m_keyframesMap[entity].size(); i++) {
            if (m_keyframesMap[entity][i]->getTime() == time) {
                m_keyframesMap[entity].erase(m_keyframesMap[entity].begin() + i);
                return;
            }
        }
    }

    void MultiPartAnimation::play()
    {
        m_state = PLAYING;
    }

    void MultiPartAnimation::pause()
    {
        m_state = PAUSED;
    }

    void MultiPartAnimation::update()
    {
        if (m_state == PLAYING) {
            for (auto& [entity, keyframes] : m_keyframesMap) {

                if (keyframes.size() == 0) {
                    continue;
                }

                // if there is only one keyframe, apply it
                if (keyframes.size() == 1) {
                    keyframes[0]->apply();
                    continue;
                }

                if (m_timer > keyframes.back()->getTime()) {
                    continue;
                }


                // find the two keyframes to interpolate between
                int keyframeIndex = 0;
                while (keyframes[keyframeIndex + 1]->getTime() < m_timer) {
                    keyframeIndex++;
                }

                auto a = keyframes[keyframeIndex];
                auto b = keyframes[keyframeIndex + 1];

                float blendFactor = (m_timer - a->getTime()) / (b->getTime() - a->getTime());

                if (m_timer <= 0)
                    blendFactor = 0;

                Keyframe interpolated = a->interpolate(*b, blendFactor);
                interpolated.apply();
            }
        }
    }

    void MultiPartAnimation::update(float dt)
    {
        m_timer += dt;
        if (dt > 0)
            update();
        // get max keyframe time
        float maxTime = 0;
        for (auto& [entity, keyframes] : m_keyframesMap) {
            if (keyframes.size() > 0) {
                maxTime = std::max(maxTime, keyframes.back()->getTime());
            }
        }
        if (m_timer > maxTime) {
            if (m_loop) {
                m_timer = 0;
            } else {
                m_state = PAUSED;
            }
        }
    }

    MultiPartAnimation MultiPartAnimation::blend(MultiPartAnimation& other, float blendFactor)
    {
        MultiPartAnimation result(m_entity);

        for (auto& [entity, keyframes] : m_keyframesMap) {
            for (int i = 0; i < keyframes.size(); i++) {
                Keyframe keyframe = keyframes[i]->interpolate(*other.m_keyframesMap[entity][i], blendFactor);
                result.addKeyframe(std::make_shared<Keyframe>(keyframe));
            }
        }
        return result;
    }

    void MultiPartAnimation::sortKeyframes()
    {
        // sort keyframes by time ascending
        for (auto& [entity, keyframes] : m_keyframesMap) {
            std::sort(keyframes.begin(), keyframes.end(), [](std::shared_ptr<Keyframe> a, std::shared_ptr<Keyframe> b) {
                return a->getTime() < b->getTime();
            });
        }
    }

    void MultiPartAnimation::saveToJson(std::string path)
    {
        std::string folder = "asset/animations/";
        path = parsing::removeExtension(path);
        path += ".json";

        nlohmann::json json;
        // save each keyframe from each vector in the map
        // each keyframe vector is associated with an entity
        // the keyframe vector is sorted by time ascending
        // the file is saved with the entity name as key
        // each entity has its list of keyframes
        for (auto& [entity, keyframes] : m_keyframesMap) {
            std::string entityName = entity->getName();
            json[entityName] = nlohmann::json::array();
            for (auto& keyframe : keyframes) {
                nlohmann::json keyframeJson;
                keyframeJson["time"] = keyframe->getTime();
                keyframeJson["position"] = { keyframe->getPosition().x, keyframe->getPosition().y };
                keyframeJson["size"] = { keyframe->getSize().x, keyframe->getSize().y };
                keyframeJson["pivot"] = { keyframe->getPivot().x, keyframe->getPivot().y };
                keyframeJson["rotation"] = keyframe->getRotation();
                keyframeJson["zIndex"] = keyframe->getZIndex();
                keyframeJson["easingFunction"] = keyframe->getEasingFunctionName();
                json[entityName].push_back(keyframeJson);
            }
        }

        std::ofstream file(folder + path);
        file << json.dump(4);
        file.close();
    }

    void MultiPartAnimation::loadFromJson(std::string path)
    {
        std::string folder = "asset/animations/";
        path = parsing::removeExtension(path);
        path += ".json";

        std::ifstream file(folder + path);
        nlohmann::json json;
        file >> json;
        file.close();

        if (m_entity == nullptr) {
            logger::error("Could not load animation " + path + " : no entity set");
            THROW("Multi part animation: Could not load animation " + path + " : no entity set");
        }

        for (auto& [entityName, keyframesJson] : json.items()) {
            std::shared_ptr<gameObj::IMultPartEntity> entity = m_entity->getPart(entityName, true);
            if (entity == nullptr) {
                logger::log("Entity " + entityName + " not found in animation " + path);
                THROW("Multi part animation: Entity " + entityName + " not found in animation " + path);
            }
            for (auto& keyframeJson : keyframesJson) {
                Keyframe keyframe(entity);
                keyframe.setTime(keyframeJson["time"]);
                keyframe.setPosition({keyframeJson["position"][0], keyframeJson["position"][1]});
                keyframe.setSize({keyframeJson["size"][0], keyframeJson["size"][1]});
                keyframe.setPivot({keyframeJson["pivot"][0], keyframeJson["pivot"][1]});
                keyframe.setRotation(keyframeJson["rotation"]);
                keyframe.setZIndex(keyframeJson["zIndex"]);
                try {
                    keyframe.setEasingFunction(keyframeJson["easingFunction"]);
                } catch (std::exception& e) {
                    clear();
                    logger::error("Could not load easing function for keyframe in animation " + path + " : " + e.what());
                    THROW("Multi part animation: Could not load easing function for keyframe in animation " + path + " : " + e.what());
                }
                addKeyframe(std::make_shared<Keyframe>(keyframe));
            }
        }
    }

    std::shared_ptr<Keyframe> MultiPartAnimation::getKeyframe(std::shared_ptr<gameObj::IMultPartEntity> entity, unsigned int index)
    {
        if (index >= m_keyframesMap[entity].size()) {
            logger::error("Keyframe index out of range");
            THROW("Multi part animation: Keyframe index out of range");
        }
        return m_keyframesMap[entity][index];
    }

    std::shared_ptr<Keyframe> MultiPartAnimation::getKeyframe(std::shared_ptr<gameObj::IMultPartEntity> entity, float time)
    {
        for (int i = 0; i < m_keyframesMap[entity].size(); i++) {
            if (m_keyframesMap[entity][i]->getTime() == time) {
                return m_keyframesMap[entity][i];
            }
        }
        logger::error("Keyframe not found");
        THROW("Multi part animation: Keyframe not found");
    }

    void MultiPartAnimation::clear()
    {
        m_keyframesMap.clear();
        setEntity(nullptr);
    }


}