/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:29:58
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-27 01:55:50
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

            struct Element {
                std::shared_ptr<ui::IUIelement> handle;
                bool enabled = true;
            };

            template<typename T>
            std::shared_ptr<T> get(const std::string &id)
            {
                exists(id);
                return std::dynamic_pointer_cast<T>(at(id).handle);
            }

            void add(const std::string &id, std::shared_ptr<ui::IUIelement> element)
            {
                // if element already exists, replace it
                if (find(id) != m_elements.end())
                    m_elements.erase(find(id));
                m_elements.emplace_back(id, Element{element, true});
            }

            void remove(const std::string &id)
            {
                exists(id);
                m_elements.erase(find(id));
            }

            void remove(const std::shared_ptr<ui::IUIelement> &element)
            {
                for (auto it = m_elements.begin(); it != m_elements.end(); ++it) {
                    if (it->second.handle == element) {
                        m_elements.erase(it);
                        return;
                    }
                }
                THROW("element not found");
            }

            void disable(const std::string &id)
            {
                exists(id);
                at(id).enabled = false;
            }

            void enable(const std::string &id)
            {
                exists(id);
                at(id).enabled = true;
            }

            void toggle(const std::string &id)
            {
                exists(id);
                at(id).enabled = !at(id).enabled;
            }

            bool isEnabled(const std::string &id) const
            {
                exists(id);
                return at(id).enabled;
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

            void setOrder(const std::vector<std::string> &order)
            {
                std::vector<std::pair<std::string, Element>> newElements;
                for (auto &id : order) {
                    exists(id);
                    newElements.emplace_back(id, m_elements.at(find(id) - m_elements.begin()).second);
                }
                m_elements = newElements;
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


        private:
            std::vector<std::pair<std::string, Element>>::const_iterator find(const std::string &id) const
            {
                return std::find_if(m_elements.begin(), m_elements.end(), [&id](auto &elem) {
                    return elem.first == id;
                });
            }

            void exists(const std::string &id) const
            {
                if (find(id) == m_elements.end())
                    THROW("Element with id " + id + " does not exist");
            }

            Element& at(const std::string &id)
            {
                exists(id);
                return m_elements.at(find(id) - m_elements.begin()).second;
            }

            const Element& at(const std::string &id) const
            {
                exists(id);
                return m_elements.at(find(id) - m_elements.begin()).second;
            }

        protected:
            std::vector<std::pair<std::string, Element>> m_elements;

    };

}