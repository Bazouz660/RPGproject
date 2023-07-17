/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-10 02:22:45
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-11 02:16:05
 *  Description:
 */

#include "MenuButton.hpp"

namespace bya::ui
{
    MenuButton::MenuButton()
    {
        m_drawBox = false;
    }

    void MenuButton::setLabel(const std::string &label)
    {
        Button::setLabel(label);
        setSize(sf::Vector2f(getLabel().getGlobalBounds().width + 10, getLabel().getGlobalBounds().height + 10));
    }

    void MenuButton::setIdle()
    {
        m_state = IDLE;
        setScale(m_scaling.getState(0));
        m_label.setFillColor(sf::Color(120, 120, 120, 255));
    }

    void MenuButton::setHovered()
    {
        m_state = HOVERED;
        setScale(m_scaling.getState(1));
        m_label.setFillColor(sf::Color(220, 220, 220, 255));
    }

    void MenuButton::setPressed()
    {
        m_state = PRESSED;
        setScale(m_scaling.getState(2));
        m_label.setFillColor(sf::Color(100, 100, 100, 255));
    }
}
