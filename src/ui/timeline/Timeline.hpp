/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:18:21
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 03:28:50
 *  Description:
 */

#pragma once

#include "AUIelement.hpp"
#include "Box.hpp"
#include "Slider.hpp"

namespace bya::ui {

    class Timeline : public AUIelement {
        public:
            Timeline();
            virtual ~Timeline() override = default;

            virtual void update(float dt) override {};
            virtual void handleEvent(sf::Event event, const sf::RenderWindow &window) override;
            virtual void render(sf::RenderTarget &target) override;

            virtual void setPosition(const sf::Vector2f &pos) override;
            virtual void setSize(const sf::Vector2f &size);

            virtual sf::FloatRect getBounds() const override { return m_box.getBounds(); }

        protected:
            sf::Vector2f m_position = {0, 0};
            gameObj::Box m_box;
            Slider m_slider;
    };

}