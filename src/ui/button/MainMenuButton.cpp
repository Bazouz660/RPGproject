/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-10 02:22:45
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-10 02:39:55
 *  Description:
 */

#include "MainMenuButton.hpp"

namespace bya::ui
{
    MainMenuButton::MainMenuButton()
    {
        m_drawBox = false;
    }

    void MainMenuButton::setLabel(const std::string &label)
    {
        Button::setLabel(label);
        setSize(sf::Vector2f(getLabel().getGlobalBounds().width + 10, getLabel().getGlobalBounds().height + 10));
    }

    void MainMenuButton::setIdle()
    {
        m_state = IDLE;
        setScale(m_scaling.getState(0));
        m_label.setFillColor(sf::Color(120, 120, 120, 255));
    }

    void MainMenuButton::setHovered()
    {
        m_state = HOVERED;
        setScale(m_scaling.getState(1));
        m_label.setFillColor(sf::Color(220, 220, 220, 255));
    }

    void MainMenuButton::setPressed()
    {
        m_state = PRESSED;
        setScale(m_scaling.getState(2));
        m_label.setFillColor(sf::Color(100, 100, 100, 255));
    }
}
