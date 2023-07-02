/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Text
*/

#pragma once

#include "IUIelement.hpp"
#include "ResourceManager.hpp"

namespace bya::ui
{
    class Text : public IUIelement, public sf::Text
    {
        public:
            Text(const std::string& text = "",
            const sf::Font& font = getResource().getFont("defaultFont"), unsigned int size = 30);

            virtual ~Text() = default;

            virtual void handleEvent(sf::Event event, const sf::RenderWindow &window) override;

            virtual void setPosition(const sf::Vector2f &pos) override;
            virtual sf::FloatRect getBounds() const override;

            virtual void render(sf::RenderTarget &target) override;
    };
}