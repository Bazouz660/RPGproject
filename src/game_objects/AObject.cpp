/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** AObject
*/

#include "AObject.hpp"

namespace bya {

    namespace gameObj {

        sf::FloatRect AObject::getBounds() const
        {
            return m_bounds;
        }

        sf::Vector2f AObject::getCenter() const
        {
            return sf::Vector2f(m_bounds.left + m_bounds.width / 2.0f, m_bounds.top + m_bounds.height / 2.0f);
        }

        sf::Vector2f AObject::getHalfSize() const
        {
            return sf::Vector2f(m_bounds.width / 2.0f, m_bounds.height / 2.0f);
        }

        sf::Vector2f AObject::getTopLeft() const
        {
            return sf::Vector2f(m_bounds.left, m_bounds.top);
        }

        sf::Vector2f AObject::getTopRight() const
        {
            return sf::Vector2f(m_bounds.left + m_bounds.width, m_bounds.top);
        }

        sf::Vector2f AObject::getBottomLeft() const
        {
            return sf::Vector2f(m_bounds.left, m_bounds.top + m_bounds.height);
        }

        sf::Vector2f AObject::getBottomRight() const
        {
            return sf::Vector2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height);
        }

    }

}