/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:29:58
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 04:00:11
 *  Description:
 */

#pragma once

#include "AUIelement.hpp"
#include "math.hpp"

// change this to inherit from AUIelement

namespace bya::ui {

    class UIelementContainer {
        public:
            UIelementContainer() = default;
            ~UIelementContainer() = default;

            template<typename T>
            std::shared_ptr<T> get(const std::string &id)
            {
                exists(id);
                return std::dynamic_pointer_cast<T>(m_elements.at(id).handle);
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
                m_elements[id].enabled = false;
            }

            void enable(const std::string &id)
            {
                exists(id);
                m_elements[id].enabled = true;
            }

            void toggle(const std::string &id)
            {
                exists(id);
                m_elements[id].enabled = !m_elements[id].enabled;
            }

            bool isEnabled(const std::string &id) const
            {
                exists(id);
                return m_elements.at(id).enabled;
            }

            void handleEvent(sf::Event event, const sf::RenderWindow &window)
            {
                // check if mouse is hovering over an element, parse map in reverse order (because of z-index)
                for (auto it = m_elements.rbegin(); it != m_elements.rend(); ++it) {
                    auto &[key, elem] = *it;
                    if (!elem.enabled)
                        continue;
                    if (elem.handle->getBounds().contains(context::getMousePosition())) {
                        elem.handle->handleHoverInput(event, window);
                        break;
                    }
                }

                // check if keyboard input is being handled by an element, order doesn't matter
                for (auto &[key, elem] : m_elements) {
                    if (!elem.enabled)
                        continue;
                    elem.handle->handleInputAny(event, window);
                }
            }

            void update(float dt)
            {
                for (auto &[key, elem] : m_elements)
                    if (elem.enabled)
                        elem.handle->update(dt);
            }

            sf::FloatRect getBounds() const
            {
                std::unique_ptr<sf::FloatRect> resBounds = nullptr;

                for (auto &[key, elem] : m_elements)
                {
                    auto bounds = elem.handle->getBounds();
                    if (resBounds == nullptr)
                        resBounds = std::make_unique<sf::FloatRect>(bounds);
                    else
                        *resBounds = math::combineRects(*resBounds, bounds);
                }
                return *resBounds;
            }

            void render(sf::RenderTarget &target)
            {
                for (auto &[key, elem] : m_elements)
                    if (elem.enabled)
                        elem.handle->render(target);
            }

        protected:
            void exists(const std::string &id) const
            {
                if (m_elements.find(id) == m_elements.end())
                    throw std::runtime_error("Element with id " + id + " does not exist");
            }

        protected:
            struct Element {
                std::shared_ptr<ui::IUIelement> handle;
                bool enabled = true;
            };

            std::map<std::string, Element> m_elements;

    };

}