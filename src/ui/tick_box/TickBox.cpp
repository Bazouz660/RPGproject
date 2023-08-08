/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-08-08 17:41:54
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-08-08 18:25:25
 * @ Description:
 */

#include "TickBox.hpp"

namespace bya::ui
{
    TickBox::TickBox()
    {
        m_checked = false;
        m_tick.setFillColor(m_uncheckedColor);
        m_tick.setSize(sf::Vector2f(20, 20));
        m_tick.setOutlineColor(sf::Color(120, 120, 120, 255));
        m_tick.setOutlineThickness(1);
        m_tick.setOrigin(m_tick.getGlobalBounds().width / 2, m_tick.getGlobalBounds().height / 2);
    }

    void TickBox::render(sf::RenderTarget &target)
    {
        ButtonNBG::render(target);
        sf::FloatRect bounds = ButtonNBG::getBounds();
        m_tick.setPosition(bounds.left - m_tick.getGlobalBounds().width * 0.5, getPosition().y);
        target.draw(m_tick);
    }

    void TickBox::onClick()
    {
        m_checked = !m_checked;
        if (m_checked)
            m_tick.setFillColor(m_checkedColor);
        else
            m_tick.setFillColor(m_uncheckedColor);
        m_callback();
    }

    void TickBox::setChecked(bool checked)
    {
        m_checked = checked;
    }

    sf::FloatRect TickBox::getBounds() const
    {
        return math::combineRects(ButtonNBG::getBounds(), m_tick.getGlobalBounds());
    }
}