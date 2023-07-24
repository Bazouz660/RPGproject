/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-10 23:05:30
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 03:36:25
 *  Description:
 */

#include "GrabBoxOrbital.hpp"
#include "logger.hpp"
#include "math.hpp"

namespace bya::ui {

    void GrabBoxOrbital::applyTransform(float angle)
    {
        angle = math::toRad(angle);
        setPosition(m_center + sf::Vector2f(m_radius * std::cos(angle), m_radius * std::sin(angle)) + m_diffToOrigin);
        setRotation(math::toDeg(angle) + 90.f);
        m_angle = math::toDeg(angle);
    }

    void GrabBoxOrbital::anyEventHandler(sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && m_grabbed) {
                m_grabbed = false;
        } else if (event.type == sf::Event::MouseMoved) {
            if (m_grabbed) {
                float angle = math::toDeg(math::angle(m_center, context::getMousePosition()));
                applyTransform(angle);
            }
        }
    }

    void GrabBoxOrbital::hoverEventHandler(sf::Event& event)
    {
        sf::Vector2f mousePos = context::getMousePosition();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (contains(mousePos)) {
                m_diffToOrigin =  getPosition() - mousePos;
                m_grabbed = true;
            }
        }
    }

}
