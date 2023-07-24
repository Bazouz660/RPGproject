/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Text
*/

#pragma once

#include "AUIelement.hpp"
#include "ResourceManager.hpp"

namespace bya::ui
{
    class Text : public AUIelement, public sf::Text
    {
        public:
            Text(const std::string& text = "", unsigned int size = 30,
            const sf::Font& font = RESOURCE().getFont("font", "game_font"));

            virtual ~Text() = default;

            virtual void setPosition(const sf::Vector2f &pos) override;
            virtual sf::FloatRect getBounds() const override;

            virtual void render(sf::RenderTarget &target) override;
    };
}