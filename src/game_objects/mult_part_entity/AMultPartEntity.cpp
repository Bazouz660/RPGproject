/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-07 04:56:01
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-07 12:50:40
 *  Description:
 */

#include "AMultPartEntity.hpp"
#include "EntityPartBuilder.hpp"

namespace bya::gameObj
{

    void AMultPartEntity::parseRotation(const std::string& name, const nlohmann::json& json)
    {
        getPart(name)->setFixedRotation(json["rotation"].get<float>());

        if (json.contains("parts")) {
            for (auto& [partName, part] : json.at("parts").items()) {
                parseRotation(partName, part);
            }
        }
    }

    void AMultPartEntity::parsePart(const std::string& name, const nlohmann::json& json, IMultPartEntity* parent)
    {
        EntityPartBuilder builder;

        parent->addPart(name, builder
            .setName(name)
            .setPivotPoint(json["pivot"][0].get<float>(), json["pivot"][1].get<float>())
            .setPosition(json["position"][0].get<float>(), json["position"][1].get<float>())
            .setSize(json["size"][0].get<float>(), json["size"][1].get<float>())
            .setTint(sf::Color(json["tint"][0].get<float>(), json["tint"][1].get<float>(), json["tint"][2].get<float>(), json["tint"][3].get<float>()))
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

    void AMultPartEntity::loadFromJson(const std::string& path)
    {
        std::string data = parsing::getFileContent(path);
        nlohmann::json json = nlohmann::json::parse(data);
        EntityPartBuilder builder;

        auto& root = json.at("root");
        auto& parts = root.at("parts");
        m_name = root.at("name").get<std::string>();
        setPivotPoint({root["pivot"][0].get<float>(), root["pivot"][1].get<float>()});
        setPosition({root["position"][0].get<float>(), root["position"][1].get<float>()});
        setSize({root["size"][0].get<float>(), root["size"][1].get<float>()});
        setTint({root["tint"][0].get<float>(), root["tint"][1].get<float>(), root["tint"][2].get<float>(), root["tint"][3].get<float>()});
        setZIndex(root.at("zIndex").get<int>());
        setFixedRotation(root.at("rotation").get<float>());

        for (auto& [partName, part] : parts.items())
            parsePart(partName, part, this);
        for (auto& [partName, part] : parts.items())
            parseRotation(partName, part);

        sortZIndex();
    }
}