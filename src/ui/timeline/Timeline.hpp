/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:18:21
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-17 21:41:34
 *  Description:
 */

#pragma once

// ui includes
#include "AUIelement.hpp"
#include "Box.hpp"
#include "Slider.hpp"
#include "Text.hpp"
#include "ScrollBox.hpp"
#include "Button.hpp"

// MultPartAnimation includes
#include "MultiPartAnimation.hpp"
#include "Keyframe.hpp"
#include "KeyframeHolder.hpp"

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

            virtual void play();
            virtual void pause();

            void setEntity(std::shared_ptr<gameObj::IMultPartEntity> entity);
            std::shared_ptr<gameObj::IMultPartEntity> getEntity() const { return m_entity; }

            void setSelectedPart(std::shared_ptr<gameObj::IMultPartEntity> selectedPart);
            std::shared_ptr<gameObj::IMultPartEntity> getSelectedPart() const { return m_selectedPart; }

            virtual void setMarkerZoom(float zoom);
            virtual float getMarkerZoom() const { return m_markerZoom; }

            virtual void setMaxTime(float time);

            virtual void clear();

            virtual sf::FloatRect getBounds() const override { return m_slider.getBounds(); }

        private:
            std::string formatTime(float time) const;
            void updateMarkersPos();
            void addMarker(unsigned int index);
            void addMarkers();

        protected:
            Timeline(const Timeline& other) = delete;
            void operator=(const Timeline& other) = delete;

            Slider m_slider;
            Text m_currentTimeText;

            std::shared_ptr<gameObj::IMultPartEntity> m_entity = nullptr;
            std::shared_ptr<gameObj::IMultPartEntity> m_selectedPart = nullptr;

            Animation::MultiPartAnimation m_animation;

            ScrollBox<KeyframeHolder> m_keyframeHolders;

            std::vector<std::shared_ptr<Button>> m_markers;
            unsigned int m_markerCount = 10;

            float m_markerZoom = 1;
            float m_maxTime = 5;
            float m_currentTime = 0;
            float m_timer = 0;

            bool m_playing = false;
    };

}