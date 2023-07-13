/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:18:21
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-13 03:19:12
 *  Description:
 */

#pragma once

#include "AUIelement.hpp"
#include "Box.hpp"
#include "Slider.hpp"
#include "Text.hpp"
#include "Button.hpp"

namespace bya::ui {

    class Timeline : public AUIelement {
        public:
            Timeline();
            virtual ~Timeline() override = default;

            virtual void update(float dt) override;
            virtual void handleEvent(sf::Event event, const sf::RenderWindow &window) override;
            virtual void render(sf::RenderTarget &target) override;

            virtual void setPosition(const sf::Vector2f &pos) override;
            virtual void setSize(const sf::Vector2f &size);

            virtual void play() { m_playing = true; }
            virtual void pause() { m_playing = false; }

            virtual void setMarkerZoom(float zoom);

            virtual void setMaxTime(float time);

            virtual sf::FloatRect getBounds() const override { return m_slider.getBounds(); }

        private:
            std::string formatTime(float time) const;
            void updateMarkersPos();

        protected:
            Timeline(const Timeline& other) = delete;
            void operator=(const Timeline& other) = delete;

            Slider m_slider;
            Text m_currentTimeText;

            std::vector<std::shared_ptr<Button>> m_markers;
            unsigned int m_markerCount = 10;

            float m_markerZoom = 1;
            float m_maxTime = 5;
            float m_currentTime = 0;
            float m_timer = 0;

            bool m_playing = false;
    };

}