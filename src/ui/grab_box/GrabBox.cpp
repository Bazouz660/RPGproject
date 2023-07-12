/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-10 23:05:30
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 03:06:21
 *  Description:
 */

#include "GrabBox.hpp"
#include "logger.hpp"

namespace bya::ui {

    void GrabBox::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        if (!isEnabled())
            return;

        sf::Vector2f mousePos = context::getMousePosition();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (contains(mousePos)) {
                m_diffToOrigin =  getPosition() - mousePos;
                m_grabbed = true;
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && m_grabbed) {
                m_grabbed = false;
        } else if (event.type == sf::Event::MouseMoved)
            if (m_grabbed)
                setPosition(mousePos + m_diffToOrigin);
    }

    void GrabBox::render(sf::RenderTarget &target)
    {
        if (isEnabled())
            OrientedBoundingBox::render(target);
    }

}
