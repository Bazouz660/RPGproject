/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 17:23:16
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-08-01 17:09:56
 * @ Description:
 */

#pragma once

#include "IUIelement.hpp"
#include <functional>
#include "context.hpp"
#include "logger.hpp"
#include "math.hpp"

namespace bya::ui {

    class AUIelement : public IUIelement {

    protected:
        struct Element {
            std::shared_ptr<ui::IUIelement> handle;
            bool enabled = true;
            bool interceptParentEvent = true;
        };

    public:

        class ElementContainer {
            public:
                template<typename T>
                std::shared_ptr<T> get(const std::string &id)
                {
                    exists(id);
                    return std::dynamic_pointer_cast<T>(at(id).handle);
                }

                template<typename T>
                std::shared_ptr<T> get(unsigned int index)
                {
                    return std::dynamic_pointer_cast<T>(at(index).handle);
                }

                void set(const std::string &id, std::shared_ptr<ui::IUIelement> element)
                {
                    bool enabled = true;
                    bool interceptParentEvent = true;
                    // if element already exists, replace it
                    if (find(id) != m_elements.end()) {
                        enabled = at(id).enabled;
                        interceptParentEvent = at(id).interceptParentEvent;
                        m_elements.erase(find(id));
                    }
                    m_elements.emplace_back(id, Element{element, enabled, interceptParentEvent});
                }

                std::size_t size() const { return m_elements.size(); }

                bool empty() const { return m_elements.empty(); }

                void add(const std::string &id, std::shared_ptr<ui::IUIelement> element)
                {
                    // if element already exists, replace it
                    if (find(id) != m_elements.end()) {
                        m_elements.erase(find(id));
                        logger::warn("element with id {\"" + id + "\"} already exists, replacing");
                    }
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

                void update(float dt)
                {
                    for (const auto& [key, elem] : m_elements) {
                        if (elem.handle && elem.enabled)
                            elem.handle->update(dt);
                    }
                }

                void setInterceptParentEvent(const std::string &id, bool interceptParentEvent)
                {
                    exists(id);
                    at(id).interceptParentEvent = interceptParentEvent;
                }

                void handleInputAny(sf::Event& event, const sf::RenderWindow& window)
                {
                    for (const auto& [key, elem] : m_elements) {
                        if (elem.handle && elem.enabled) {
                            elem.handle->handleInputAny(event, window);
                        }
                    }
                }

                bool handleHoverInput(sf::Event& event, const sf::RenderWindow& window)
                {
                    for (const auto& [key, elem] : m_elements) {
                        if (elem.handle && elem.handle->getBounds().contains(context::getMousePosition()) && elem.enabled) {
                            elem.handle->handleHoverInput(event, window);
                            if (elem.interceptParentEvent)
                                return true;
                            break;
                        }
                    }
                    return false;
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

                sf::FloatRect getBounds() const
                {
                    if (m_elements.empty())
                        return math::NULL_RECT;
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

                void render(sf::RenderTarget& target) const
                {
                    for (const auto& [key, elem] : m_elements) {
                        if (elem.handle && elem.enabled)
                            elem.handle->render(target);
                    }
                }

                // iterator stuff
                std::vector<std::pair<std::string, Element>>::iterator begin() { return m_elements.begin(); }
                std::vector<std::pair<std::string, Element>>::iterator end() { return m_elements.end(); }
                std::vector<std::pair<std::string, Element>>::const_iterator begin() const { return m_elements.begin(); }
                std::vector<std::pair<std::string, Element>>::const_iterator end() const { return m_elements.end(); }
                std::vector<std::pair<std::string, Element>>::const_iterator cbegin() const { return m_elements.cbegin(); }
                std::vector<std::pair<std::string, Element>>::const_iterator cend() const { return m_elements.cend(); }

            private:
                std::vector<std::pair<std::string, Element>>::const_iterator find(const std::string &id) const
                {
                    return std::find_if(m_elements.begin(), m_elements.end(), [&id](auto &elem) {
                        return elem.first == id;
                    });
                }

                std::vector<std::pair<std::string, Element>>::iterator find(const std::string &id)
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

                Element& at(unsigned int index)
                {
                    if (index >= m_elements.size())
                        THROW("Index out of bounds");
                    return m_elements.at(index).second;
                }

                const Element& at(unsigned int index) const
                {
                    if (index >= m_elements.size())
                        THROW("Index out of bounds");
                    return m_elements.at(index).second;
                }

                protected:
                    std::vector<std::pair<std::string, Element>> m_elements;
            };

        virtual ~AUIelement() = default;

        virtual void update(float dt) override final {
            updateHandler(dt);
            m_children.update(dt);
        }

        void handleInputAny(sf::Event& event, const sf::RenderWindow& window) override final
        {
            anyEventHandler(event);
            // Propagate the event to child elements
            m_children.handleInputAny(event, window);
        }

        void handleHoverInput(sf::Event& event, const sf::RenderWindow& window) override final {
            // Propagate the event to child elements
            if (m_children.handleHoverInput(event, window))
                return; // a child element intercepted the event
            if (getBounds().contains(context::getMousePosition()))
                hoverEventHandler(event);
        }

    protected:
        AUIelement() = default;

        virtual void hoverEventHandler(sf::Event& event) {};
        virtual void anyEventHandler(sf::Event& event) {};
        virtual void updateHandler(float dt) {};

        ElementContainer m_children;

        bool m_recursiveKeyboardInput = true;
    };

}
