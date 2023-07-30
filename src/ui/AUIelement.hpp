/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 17:23:16
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 03:55:33
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
    public:
        virtual ~AUIelement() = default;

        virtual void update(float dt) override final {
            updateHandler(dt);
            for (const auto& child : m_children) {
                if (child.handle && child.enabled)
                    child.handle->update(dt);
            }
        }

        void handleInputAny(sf::Event& event, const sf::RenderWindow& window) override final
        {
            anyEventHandler(event);
            // Propagate the event to child elements
            for (const auto& child : m_children) {
                if (child.handle && child.enabled)
                    child.handle->handleInputAny(event, window);
            }
        }

        void handleHoverInput(sf::Event& event, const sf::RenderWindow& window) override final {
            // Propagate the event to child elements
            for (const auto& child : m_children) {
                if (child.handle && child.handle->getBounds().contains(context::getMousePosition()) && child.enabled) {
                    child.handle->handleHoverInput(event, window);
                    return;
                }
            }
            if (getBounds().contains(context::getMousePosition()))
                hoverEventHandler(event);
        }

        void addChild(std::shared_ptr<IUIelement> child) override final
        {
            m_children.push_back({child, true});
        }

        void removeChild(std::shared_ptr<IUIelement> child) override final
        {
            m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [child](const Element& element) {
                return element.handle == child;
            }), m_children.end());
        }

        void toggleChild(std::shared_ptr<IUIelement> child, bool enabled)
        {
            for (auto& element : m_children) {
                if (element.handle == child) {
                    element.enabled = enabled;
                    return;
                }
            }
        }

        bool isChildEnabled(std::shared_ptr<IUIelement> child)
        {
            for (auto& element : m_children) {
                if (element.handle == child)
                    return element.enabled;
            }
            return false;
        }

    protected:
        sf::FloatRect getChildsBounds() const
        {
            std::unique_ptr<sf::FloatRect> resBounds = nullptr;

            for (auto &child : m_children)
            {
                auto bounds = child.handle->getBounds();
                if (resBounds == nullptr)
                    resBounds = std::make_unique<sf::FloatRect>(bounds);
                else
                    *resBounds = math::combineRects(*resBounds, bounds);
            }
            return *resBounds;
        }

    protected:
        AUIelement() = default;

        struct Element {
            std::shared_ptr<ui::IUIelement> handle;
            bool enabled = true;
        };

        virtual void hoverEventHandler(sf::Event& event) {};
        virtual void anyEventHandler(sf::Event& event) {};
        virtual void updateHandler(float dt) {};

        std::vector<Element> m_children;

        bool m_recursiveKeyboardInput = true;
    };

}
