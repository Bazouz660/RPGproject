/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-06 23:29:16
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-08-08 02:49:56
 *  Description:
 */

#pragma once

#include "UIelementContainer.hpp"
#include "IScene.hpp"
#include "context.hpp"

namespace bya
{
    class AScene : public IScene {
        public:
            ~AScene() override = default;
            virtual void load() override {};

            virtual void handleUIEvent(sf::Event &event, sf::RenderWindow &window) override final
            {
                m_UIelements.handleInputAny(event, window);
                m_UIelements.handleHoverInput(event, window);
            }

            virtual void updateUI(float dt) override final
            {
                m_UIelements.update(dt);
            }

            virtual void handleEvent(sf::Event &event, sf::RenderWindow &window) override {}

            virtual void renderUi(sf::RenderTarget &target) override final
            {
                m_UIelements.render(target);
            }

            virtual void close() override {}
            virtual void reset() override {}

        protected:
            ui::UIelementContainer m_UIelements;
            sf::RectangleShape m_background;

            AScene()
            {
                m_background.setSize(sf::Vector2f(context::getWindowSize().x, context::getWindowSize().y));
                m_background.setFillColor(sf::Color(15, 15, 15, 255));
            };
    };
}
