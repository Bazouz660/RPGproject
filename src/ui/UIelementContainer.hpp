/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:29:58
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 04:00:11
 *  Description:
 */

#pragma once

#include "IUIelement.hpp"

namespace bya::ui {

    class UIelementContainer : public IUIelement {
        public:
            UIelementContainer() = default;
            virtual ~UIelementContainer() override = default;

            template<typename T>
            std::shared_ptr<T> get(const std::string &id)
            {
                exists(id);
                return std::dynamic_pointer_cast<T>(m_elements.at(id).first);
            }

            void add(const std::string &id, std::shared_ptr<ui::IUIelement> element)
            {
                m_elements[id] = {element, true};
            }

            void remove(const std::string &id)
            {
                exists(id);
                m_elements.erase(id);
            }

            void disable(const std::string &id)
            {
                exists(id);
                m_elements[id].second = false;
            }

            void enable(const std::string &id)
            {
                exists(id);
                m_elements[id].second = true;
            }

            void toggle(const std::string &id)
            {
                exists(id);
                m_elements[id].second = !m_elements[id].second;
            }

            bool isEnabled(const std::string &id) const
            {
                exists(id);
                return m_elements.at(id).second;
            }

            void update(float dt) override
            {
                for (auto &[key, elem] : m_elements)
                    if (elem.second)
                        elem.first->update(dt);
            }

            void handleEvent(sf::Event event, const sf::RenderWindow &window) override
            {
                for (auto &[key, elem] : m_elements)
                    if (elem.second)
                        elem.first->handleEvent(event, window);
            }

            void setPosition(const sf::Vector2f &pos) override
            {
                for (auto &[key, elem] : m_elements)
                    elem.first->setPosition(pos);
            }

            sf::FloatRect getBounds() const
            {
                float left = 0;
                float top = 0;
                float width = 0;
                float height = 0;

                for (auto &[key, elem] : m_elements)
                {
                    auto bounds = elem.first->getBounds();
                    if (bounds.left < left)
                        left = bounds.left;
                    if (bounds.top < top)
                        top = bounds.top;
                    if (bounds.width > width)
                        width = bounds.width;
                    if (bounds.height > height)
                        height = bounds.height;
                }
                return sf::FloatRect(left, top, width, height);
            }

            virtual void render(sf::RenderTarget &target)
            {
                for (auto &[key, elem] : m_elements)
                    if (elem.second)
                        elem.first->render(target);
            }

        private:
            void exists(const std::string &id) const
            {
                if (m_elements.find(id) == m_elements.end())
                    throw std::runtime_error("Element with id " + id + " does not exist");
            }

        protected:
            std::map<std::string, std::pair<std::shared_ptr<ui::IUIelement>, bool>> m_elements;

    };

}