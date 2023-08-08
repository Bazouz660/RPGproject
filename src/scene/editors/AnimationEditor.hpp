/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** AnimationEditor
*/

#pragma once

#include "AScene.hpp"
#include "Camera.hpp"
#include "IUIelement.hpp"
#include "OrientedBoundingBox.hpp"
#include "HumanoidEntity.hpp"

namespace bya
{

    class AnimationEditor : public AScene
    {
    public:
        AnimationEditor() = default;
        virtual ~AnimationEditor() override = default;
        virtual void load() override;
        virtual void handleEvent(sf::Event &event, sf::RenderWindow &window) override;
        virtual void update(float dt) override;
        virtual void render(sf::RenderTarget &target) override;

    private:
        void configureLoadModelButton();
        void configureSaveAnimationButton();
        void configureLoadAnimationButton();
        void setPartInfo();
        void resetPartInfo();

    private:
        std::shared_ptr<bya::gameObj::IMultPartEntity> m_entity = nullptr;
        std::shared_ptr<bya::gameObj::IMultPartEntity> m_selectedPart = nullptr;

        sf::RectangleShape m_editorBackground;
        sf::RectangleShape m_partInfoBackground;
    };

}
