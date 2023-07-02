/*
** EPITECH PROJECT, 2022
** BurunyaEngine
** File description:
** UIScene.hpp
*/

#pragma once

#include "IScene.hpp"
#include "Camera.hpp"
#include "IUIelement.hpp"
#include "SmokeEmitter.hpp"

namespace bya
{

    class UIScene : public IScene
    {
    public:
        UIScene();
        virtual ~UIScene() override;
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
        std::shared_ptr<bya::effects::SmokeEmitter> m_emitter;
        sf::RectangleShape m_background;
    };

}
