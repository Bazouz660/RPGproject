/*
** EPITECH PROJECT, 2023
** RPG3
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-24 16:20:49
*/

#pragma once

#include "common.hpp"

namespace bya::ui {

    class IUIelement : public std::enable_shared_from_this<IUIelement> {
    public:
        virtual ~IUIelement() = default;

        // Handle input events
        virtual void handleHoverInput(sf::Event& event, const sf::RenderWindow& window) = 0;
        virtual void handleInputAny(sf::Event& event, const sf::RenderWindow& window) = 0;

        // Update the element each frame
        virtual void update(float dt) = 0;

        // Set the position of the element
        virtual void setPosition(const sf::Vector2f& pos) = 0;

        // Get the bounding box of the element
        virtual sf::FloatRect getBounds() const = 0;

        // Render the element to the target
        virtual void render(sf::RenderTarget& target) = 0;

        // Add  children references
        virtual void addChild(std::shared_ptr<IUIelement> child) = 0;
        virtual void removeChild(std::shared_ptr<IUIelement> child) = 0;
    };

}
