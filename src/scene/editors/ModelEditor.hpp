/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** ModelEditor
*/

#pragma once

#include "AScene.hpp"
#include "Camera.hpp"
#include "IUIelement.hpp"
#include "OrientedBoundingBox.hpp"
#include "HumanoidEntity.hpp"

namespace bya
{

    class ModelEditor : public AScene
    {
    public:
        ModelEditor() = default;
        virtual ~ModelEditor() override = default;
        virtual void init() override;
        virtual void handleEvent(sf::Event &event, sf::RenderWindow &window) override;
        virtual void update(float dt) override;
        virtual void render(sf::RenderTarget &target) override;

    private:
        void configureLoadButton();
        void configureSaveButton();
        void setPartInfo();
        void resetPartInfo();

    private:
        std::shared_ptr<bya::gameObj::IMultPartEntity> m_entity = nullptr;
        std::shared_ptr<bya::gameObj::IMultPartEntity> m_selectedPart = nullptr;

        sf::RectangleShape m_editorBackground;
        sf::RectangleShape m_partInfoBackground;
    };

}
