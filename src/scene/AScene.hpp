/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-06 23:29:16
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-07 15:03:15
 *  Description:
 */

#pragma once

#include "IUIelement.hpp"
#include "IScene.hpp"
#include "info.hpp"

namespace bya
{
    class AScene : public IScene {
        public:
            ~AScene() override = default;
            virtual void init() override {};

            virtual void handleUIEvent(sf::Event &event, sf::RenderWindow &window) override final
            {
                for (auto &[key, elem] : m_UIelements)
                    elem->handleEvent(event, window);
            }

            virtual void updateUI(float dt) override final
            {
                for (auto &[key, elem] : m_UIelements)
                    elem->update(dt);
            }

            virtual void handleEvent(sf::Event &event, sf::RenderWindow &window) override {}

            virtual void renderUi(sf::RenderTarget &target)
            {
                for (auto &[key, elem] : m_UIelements)
                    elem->render(target);
            }

            virtual void close() override {}
            virtual void reset() override {}

            template<typename T>
            std::shared_ptr<T> getUIelement(const std::string &id)
            {
                return std::dynamic_pointer_cast<T>(m_UIelements.at(id));
            }

        protected:
            std::map<std::string, std::shared_ptr<ui::IUIelement>> m_UIelements;
            sf::RectangleShape m_background;

            AScene() = default;
            void addUIelement(const std::string &id, std::shared_ptr<ui::IUIelement> element)
            {
                m_UIelements.insert(std::make_pair(id, std::move(element)));
                m_background.setSize(sf::Vector2f(info::getWindowSize()));
                m_background.setFillColor(sf::Color(50, 50, 50, 255));
            }
    };
}
