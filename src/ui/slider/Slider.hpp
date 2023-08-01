/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Slider
*/

#ifndef SLIDER_HPP_
    #define SLIDER_HPP_

    #include "AUIelement.hpp"
    #include "Spritesheet.hpp"
    #include "Scaling.hpp"
    #include "ResourceManager.hpp"
    #include "Box.hpp"
    #include "OrientedBoundingBox.hpp"

    namespace bya::ui {
        class Slider : public AUIelement {
            public:
                enum State { IDLE, HOVERED, GRABBED };
                enum Orientation { VERTICAL, HORIZONTAL };

                Slider(Orientation orientation = HORIZONTAL);

                virtual void setPosition(const sf::Vector2f& pos) override;
                virtual sf::FloatRect getBounds() const override;
                virtual void render(sf::RenderTarget& target) override;

                float getProgress() const;
                void setProgress(float progress);

                State getState() const { return m_state; }

                gameObj::Box& getInternRail() { return m_internRail; }
                gameObj::Box& getOuterRail() { return m_outerRail; }
                gameObj::OrientedBoundingBox& getWagon() { return m_wagon; }

                void setSize(const sf::Vector2f& size);
                sf::Vector2f getSize() const { return m_size; }

                void drawDebug(bool draw) { m_drawInternRail = draw; }
                void drawRail(bool draw) { m_drawOuterRail = draw; }

            protected:
                void lockWagonPositon();
                virtual void hoverEventHandler(sf::Event& event) override;
                virtual void anyEventHandler(sf::Event& event) override;

            protected:
                float m_progress = 0.5f;
                float m_wagonPadding = 0;
                bool m_drawInternRail = false;
                bool m_drawOuterRail = true;
                sf::Vector2f m_diffToOrigin;
                sf::Vector2f m_size;
                sf::Vector2f m_lastPosition;
                Orientation m_orientation;
                Animation::Scaling m_scaling;
                State m_state = IDLE;
                gameObj::Box m_internRail;
                gameObj::Box m_outerRail;
                gameObj::OrientedBoundingBox m_wagon;
        };
    }

#endif /* !SLIDER_HPP_ */
