/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-06 23:29:16
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-07 02:11:13
 *  Description:
 */

#pragma once

#include "IUIelement.hpp"
#include "IScene.hpp"

namespace bya
{
    class AScene : public IScene {
        public:
            ~AScene() override = default;
            void init() override {};
            void handleEvent(sf::Event &event, sf::RenderWindow &window) override
            {
                for (auto &[key, elem] : m_UIelements)
                    elem->handleEvent(event, window);
            }
            void renderUi(sf::RenderTarget &target)
            {
                for (auto &[key, elem] : m_UIelements)
                    elem->render(target);
            }
            void close() override {};
            void reset() override {};

        protected:
            std::map<std::string, std::shared_ptr<ui::IUIelement>> m_UIelements;

            AScene() = default;
            void addUIelement(const std::string &id, std::shared_ptr<ui::IUIelement> element)
            {
                m_UIelements.insert(std::make_pair(id, std::move(element)));
            }
    };
}
