/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:22:02
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 03:28:56
 *  Description:
 */

#include "Timeline.hpp"

namespace bya::ui {

    Timeline::Timeline()
    {
        m_box.setFillColor(sf::Color(52, 155, 235, 255));
        m_box.setOutlineColor(sf::Color::White);
        m_box.setOutlineThickness(2);
    }

    void Timeline::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        m_slider.handleEvent(event, window);
    }

    void Timeline::render(sf::RenderTarget &target)
    {
        target.draw(m_box);
        m_slider.render(target);
    }

    void Timeline::setSize(const sf::Vector2f &size)
    {
        m_box.setSize(size);
        m_box.setOrigin(size.x / 2, size.y / 2);
    }

    void Timeline::setPosition(const sf::Vector2f &pos)
    {
        m_position = pos;
        m_box.setPosition(pos);
        m_slider.setPosition(pos);
    }

}