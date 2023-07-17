/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-16 21:26:06
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-17 16:36:32
 * @ Description:
 */

#include "MultiPartAnimation.hpp"
#include "logger.hpp"

namespace bya::Animation {

    void MultiPartAnimation::addKeyframe(Keyframe keyframe)
    {
        if (m_keyframesMap.find(keyframe.getEntity()) == m_keyframesMap.end()) {
            m_keyframesMap[keyframe.getEntity()] = std::vector<Keyframe>();
        }

        m_keyframesMap[keyframe.getEntity()].push_back(keyframe);
    }

    void MultiPartAnimation::removeKeyframe(Keyframe keyframe)
    {
        if (m_keyframesMap.find(keyframe.getEntity()) == m_keyframesMap.end()) {
            return;
        }

        std::vector<Keyframe>& keyframes = m_keyframesMap[keyframe.getEntity()];
        for (int i = 0; i < keyframes.size(); i++) {
            if (keyframes[i].getTime() == keyframe.getTime()) {
                keyframes.erase(keyframes.begin() + i);
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
                    return;
                }

                // if there is only one keyframe, apply it
                if (keyframes.size() == 1) {
                    keyframes[0].apply();
                    return;
                }

                if (m_timer > keyframes.back().getTime()) {
                    return;
                }


                // find the two keyframes to interpolate between
                int keyframeIndex = 0;
                while (keyframes[keyframeIndex + 1].getTime() < m_timer) {
                    keyframeIndex++;
                }

                Keyframe& a = keyframes[keyframeIndex];
                Keyframe& b = keyframes[keyframeIndex + 1];

                float blendFactor = (m_timer - a.getTime()) / (b.getTime() - a.getTime());

                Keyframe interpolated = a.interpolate(b, blendFactor);
                interpolated.apply();
            }
        }
    }

    void MultiPartAnimation::update(float dt)
    {
        m_timer += dt;
        update();
        // get max keyframe time
        float maxTime = 0;
        for (auto& [entity, keyframes] : m_keyframesMap) {
            if (keyframes.size() > 0) {
                maxTime = std::max(maxTime, keyframes.back().getTime());
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
                Keyframe keyframe = keyframes[i].interpolate(other.m_keyframesMap[entity][i], blendFactor);
                result.addKeyframe(keyframe);
            }
        }
        return result;
    }

    void MultiPartAnimation::sortKeyframes()
    {
        // sort keyframes by time ascending
        for (auto& [entity, keyframes] : m_keyframesMap) {
            std::sort(keyframes.begin(), keyframes.end(), [](Keyframe& a, Keyframe& b) {
                return a.getTime() < b.getTime();
            });
        }
    }

}