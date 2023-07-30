/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-07 04:56:01
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 00:37:24
 *  Description:
 */

#include "AMultPartEntity.hpp"
#include "EntityPartBuilder.hpp"

#include "logger.hpp"

namespace bya::gameObj
{

    void AMultPartEntity::parseRotation(const std::string& name, const nlohmann::json& json)
    {
        getPart(name)->setRotation(json["rotation"].get<float>());

        if (json.contains("parts")) {
            for (auto& [partName, part] : json.at("parts").items()) {
                parseRotation(partName, part);
            }
        }
    }

    void AMultPartEntity::parsePart(const std::string& name, const nlohmann::json& json, IMultPartEntity* parent)
    {
        EntityPartBuilder builder;

        parent->addPart(builder
            .setName(name)
            .setOrigin(json["pivot"][0].get<float>(), json["pivot"][1].get<float>())
            .setPosition(json["position"][0].get<float>(), json["position"][1].get<float>())
            .setSize(json["size"][0].get<float>(), json["size"][1].get<float>())
            .setTint(sf::Color(json["tint"][0].get<float>(), json["tint"][1].get<float>(),
                json["tint"][2].get<float>(), json["tint"][3].get<float>()))
            .setZIndex(json["zIndex"].get<int>())
            .setParent(parent)
            .build()
        );

        if (json.contains("parts")) {
            for (auto& [partName, part] : json.at("parts").items()) {
                parsePart(partName, part, getPart(name).get());
            }
        }
    }

    void AMultPartEntity::loadFromJson(std::string path)
    {
        std::string folder = "asset/models/";
        path = parsing::removeExtension(path);
        path += ".json";

        std::string data = parsing::getFileContent(folder + path);
        nlohmann::json json = nlohmann::json::parse(data);
        EntityPartBuilder builder;

        auto& root = json.at("root");
        auto& parts = root.at("parts");
        m_name = root.at("name").get<std::string>();
        setOrigin({root["pivot"][0].get<float>(), root["pivot"][1].get<float>()});
        setPosition({root["position"][0].get<float>(), root["position"][1].get<float>()});
        setSize({root["size"][0].get<float>(), root["size"][1].get<float>()});
        setTint(sf::Color(root["tint"][0].get<float>(), root["tint"][1].get<float>(),
            root["tint"][2].get<float>(), root["tint"][3].get<float>()));
        setZIndex(root.at("zIndex").get<int>());
        setRotation(root.at("rotation").get<float>());

        for (auto& [partName, part] : parts.items())
            parsePart(partName, part, this);
        for (auto& [partName, part] : parts.items())
            parseRotation(partName, part);

        sortZIndex();

        if (!json.contains("partMapping"))
            return;
        for (auto& partMapping : json.at("partMapping").items())
            m_partMapping[partMapping.key()] = partMapping.value().get<std::string>();
    }

    void AMultPartEntity::savePartToJson(IMultPartEntity* part, nlohmann::json& json, std::map<std::string, float>& rotationMap)
    {
        sf::Vector2f position = part->getPosition() - getPosition();

        json[part->getName()]["position"] = {position.x, position.y};
        json[part->getName()]["size"] = {part->getSize().x, part->getSize().y};
        json[part->getName()]["pivot"] = {part->getOrigin().x, part->getOrigin().y};
        json[part->getName()]["tint"] = {part->getTint().r, part->getTint().g, part->getTint().b, part->getTint().a};
        json[part->getName()]["zIndex"] = part->getZIndex();
        json[part->getName()]["rotation"] = rotationMap[part->getName()];

        for (auto& child : part->getDirectChildren()) {
            savePartToJson(child.get(), json[part->getName()]["parts"], rotationMap);
        }
    }

    void AMultPartEntity::saveToJson(std::string path)
    {
        std::string folder = "asset/models/";
        path = parsing::removeExtension(path);
        path += ".json";

        std::map<std::string, float> rotationMap;

        for (auto& part : getRecursiveChildren())
            rotationMap[part->getName()] = part->getGlobalRotation();

        // set rotation to 0 to reset position
        for (auto& part : getRecursiveChildren())
            part->setRotation(0);

        sf::Vector2f position = getPosition() - getPosition();
        nlohmann::json json;
        json["root"]["name"] = m_name;
        json["root"]["pivot"] = {getOrigin().x, getOrigin().y};
        json["root"]["position"] = {position.x, position.y};
        json["root"]["size"] = {getSize().x, getSize().y};
        json["root"]["tint"] = {m_tint.r, m_tint.g, m_tint.b, m_tint.a};
        json["root"]["zIndex"] = getZIndex();
        json["root"]["rotation"] = getGlobalRotation();


        for (auto& part : getDirectChildren()) {
            savePartToJson(part.get(), json["root"]["parts"], rotationMap);
        }

        // reset rotation
        for (auto& [partName, rotation] : rotationMap)
            getPart(partName)->setRotation(rotation);

        for (auto& [partName, part] : m_partMapping)
            json["partMapping"][partName] = part;

        std::ofstream file(folder + path);
        file << json.dump(4);
        file.close();
    }
}