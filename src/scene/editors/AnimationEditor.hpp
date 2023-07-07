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
        virtual void init() override;
        virtual void handleEvent(sf::Event &event, sf::RenderWindow &window) override;
        virtual void update(float dt) override;
        virtual void render(sf::RenderTarget &target) override;

    private:
        bya::gameObj::HumanoidEntity m_humanoid;
        bya::gameObj::PartEntity m_entity;
    };

}
