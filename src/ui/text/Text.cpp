/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Text
*/

#include "Text.hpp"

namespace bya::ui
{
    Text::Text(const std::string &text, unsigned int size, const sf::Font &font)
        : sf::Text(text, font, size)
    {
    }

    void Text::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
    }

    void Text::setPosition(const sf::Vector2f &pos)
    {
        sf::Text::setPosition(pos);
    }

    sf::FloatRect Text::getBounds() const
    {
        return sf::Text::getGlobalBounds();
    }

    void Text::render(sf::RenderTarget &target)
    {
        target.draw(*this);
    }
}