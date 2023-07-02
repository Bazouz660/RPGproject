/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Slider
*/

#ifndef SLIDER_HPP_
    #define SLIDER_HPP_

    #include "IUIelement.hpp"
    #include "Spritesheet.hpp"
    #include "Scaling.hpp"
    #include "ResourceManager.hpp"
    #include "Box.hpp"

    namespace bya::ui {
        class Slider : public IUIelement {
            public:
                enum State { IDLE, HOVERED, GRABBED };
                enum Orientation { VERTICAL, HORIZONTAL };

                Slider(const sf::Texture& wagonTexture = getResource().getTexture("defaultSliderWagon"),
                    const sf::Texture& railTexture = getResource().getTexture("defaultSliderRail"),
                    Orientation orientation = HORIZONTAL);

                void setWagonPadding(float padding);
                float getWagonPadding() const;

                virtual void handleEvent(sf::Event event, const sf::RenderWindow& window) override;
                virtual void setPosition(const sf::Vector2f& pos) override;
                virtual sf::FloatRect getBounds() const override;
                virtual void render(sf::RenderTarget& target) override;
                float getProgress() const;

            protected:
                bool isOnTrack() const;
                void fixWagonPosition();

            protected:
                float m_progress = 0.5f;
                bool m_mouseDown = false;
                float m_wagonPadding = 0;
                sf::Vector2f m_lastPosition;
                Orientation m_orientation;
                Animation::Scaling m_scaling;
                State m_state = IDLE;
                gameObj::Box m_internRail;
                gameObj::Box m_outerRail;
                gameObj::Box m_wagon;
        };
    }

#endif /* !SLIDER_HPP_ */
