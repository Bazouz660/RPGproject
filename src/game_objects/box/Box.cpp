/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Box
*/

#include "Box.hpp"
#include "info.hpp"

namespace bya {

    namespace gameObj {

        Box::Box()
        {
            AObject::m_bounds = sf::FloatRect(0, 0, 0, 0);
        }

        Box::Box(sf::Vector2f pos, sf::Vector2f size)
        {
            setPosition(pos);
            setSize(size);
            AObject::m_bounds = getGlobalBounds();
        }

        sf::FloatRect Box::getBounds() const
        {
            return getGlobalBounds();
        }

        sf::Vector2f Box::getCenter() const
        {
            sf::FloatRect bounds = getGlobalBounds();
            return sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        }

        sf::Vector2f Box::getHalfSize() const
        {
            sf::FloatRect bounds = getGlobalBounds();
            return sf::Vector2f(bounds.width / 2.0f, bounds.height / 2.0f);
        }

        void Box::draw(sf::RenderTarget &window, sf::RenderStates states)
        {
            window.draw(*this, states);
        }

        sf::Vector2f Box::getTopLeft() const
        {
            sf::FloatRect bounds = getGlobalBounds();
            return sf::Vector2f(bounds.left, bounds.top);
        }

        sf::Vector2f Box::getTopRight() const
        {
            sf::FloatRect bounds = getGlobalBounds();
            return sf::Vector2f(bounds.left + bounds.width, bounds.top);
        }

        sf::Vector2f Box::getBottomLeft() const
        {
            sf::FloatRect bounds = getGlobalBounds();
            return sf::Vector2f(bounds.left, bounds.top + bounds.height);
        }

        sf::Vector2f Box::getBottomRight() const
        {
            sf::FloatRect bounds = getGlobalBounds();
            return sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);
        }

        bool Box::isHovered()
        {
            sf::Vector2f mousePos = info::getMousePosition();
            return getGlobalBounds().contains(mousePos);
        }

        bool Box::isClicked()
        {
            if (isHovered()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    return true;
                }
            }
            return false;
        }

    }

}