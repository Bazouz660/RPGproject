/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** TestScene
*/

#pragma once

#include "IScene.hpp"
#include "Camera.hpp"
#include "IUIelement.hpp"

#include "OrientedBoundingBox.hpp"

#include "HumanoidEntity.hpp"

namespace bya
{

    class TestScene : public IScene
    {
    public:
        TestScene();
        virtual ~TestScene() override;
        virtual void init() override;
        virtual void close() override;
        virtual void reset() override;
        virtual void handleEvent(sf::Event &event, sf::RenderWindow &window) override;
        virtual void update(float dt) override;
        virtual void render(sf::RenderTarget &target) override;

    private:
        void addUIelement(const std::string& id, std::shared_ptr<ui::IUIelement> element);

    private:
        std::map<std::string, std::shared_ptr<ui::IUIelement>> m_UIelements;
        sf::RectangleShape m_background;
        bya::gameObj::HumanoidEntity m_humanoid;

        bya::gameObj::OrientedBoundingBox m_oobb1;
    };

}
