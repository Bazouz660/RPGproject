/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** TestScene
*/

#pragma once

#include "AScene.hpp"
#include "Camera.hpp"
#include "IUIelement.hpp"
#include "OrientedBoundingBox.hpp"
#include "HumanoidEntity.hpp"

namespace bya
{

    class TestScene : public AScene
    {
        public:
            TestScene();
            virtual ~TestScene() override;
            virtual void init() override;
            virtual void close() override;
            virtual void reset() override;
            virtual void update(float dt) override;
            virtual void render(sf::RenderTarget &target) override;

        private:
            bya::gameObj::HumanoidEntity m_humanoid;
            bya::gameObj::OrientedBoundingBox m_oobb1;
    };

}
