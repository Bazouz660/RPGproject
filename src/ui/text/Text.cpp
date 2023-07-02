/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Text
*/

#include "Text.hpp"

namespace bya::ui
{
    Text::Text(const std::string &text, const sf::Font &font, unsigned int size)
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