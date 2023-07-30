/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:18:21
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 22:57:20
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
#include "KeyframeInfo.hpp"

// MultPartAnimation includes
#include "MultiPartAnimation.hpp"
#include "Keyframe.hpp"
#include "KeyframeHolder.hpp"

namespace bya::ui {

    class Timeline : public AUIelement {
        public:

            Timeline(KeyframeInfo& keyframeInfo);
            virtual ~Timeline() override = default;

            virtual void render(sf::RenderTarget &target) override;

            virtual void setPosition(const sf::Vector2f &pos) override;
            virtual void setSize(const sf::Vector2f &size);

            virtual void play();
            virtual void pause();

            void setEntity(std::shared_ptr<gameObj::IMultPartEntity> entity);
            std::shared_ptr<gameObj::IMultPartEntity> getEntity() const { return m_entity; }

            void setSelectedPart(std::shared_ptr<gameObj::IMultPartEntity> selectedPart);
            std::shared_ptr<gameObj::IMultPartEntity> getSelectedPart() const { return m_selectedPart; }

            void loadAnimation(std::string path);
            void saveAnimation(std::string path);

            virtual void setMarkerZoom(float zoom);
            virtual float getMarkerZoom() const { return m_markerZoom; }

            KeyframeInfo& getKeyframeInfo() { return m_keyframeInfo; }

            void setTimer(float timer);

            virtual void setMaxTime(float time);

            virtual void clear();

            virtual sf::FloatRect getBounds() const override;

        private:
            std::string formatTime(float time) const;
            void updateMarkersPos();
            void addMarker(unsigned int index);
            void addMarkers();

        protected:
            Timeline(const Timeline& other) = delete;
            void operator=(const Timeline& other) = delete;
            virtual void anyEventHandler(sf::Event& event);
            virtual void updateHandler(float dt);

            std::shared_ptr<Slider> m_slider;
            std::shared_ptr<Text> m_currentTimeText;

            std::shared_ptr<gameObj::IMultPartEntity> m_entity = nullptr;
            std::shared_ptr<gameObj::IMultPartEntity> m_selectedPart = nullptr;

            Animation::MultiPartAnimation m_animation;

            std::shared_ptr<ScrollBox<KeyframeHolder>> m_keyframeHolders;

            KeyframeInfo& m_keyframeInfo;

            std::vector<std::shared_ptr<Button>> m_markers;
            unsigned int m_markerCount = 10;

            float m_markerZoom = 1;
            float m_maxTime = 5;
            float m_currentTime = 0;
            float m_timer = 0;

            bool m_playing = false;
    };

}