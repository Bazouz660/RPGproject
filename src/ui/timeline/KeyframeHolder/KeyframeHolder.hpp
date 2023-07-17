/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-17 20:41:54
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-17 21:58:52
 * @ Description:
 */

#pragma once

#include "KeyframeMarker.hpp"
#include "MultiPartAnimation.hpp"

namespace bya::ui {

        // class that hold the keyframes of a part
        class KeyframeHolder : public AUIelement {
            public:
                KeyframeHolder(std::shared_ptr<gameObj::IMultPartEntity> part, float& time, float& maxTime, const Slider& slider, Animation::MultiPartAnimation& m_animation);
                virtual ~KeyframeHolder() = default;

                void addKeyframeMarker(std::shared_ptr<KeyframeMarker> keyframeMarker);
                void removeKeyframeMarker(std::shared_ptr<KeyframeMarker> keyframeMarker);

                virtual void update(float dt) override;
                virtual void handleEvent(sf::Event event, const sf::RenderWindow &window) override;
                virtual void render(sf::RenderTarget &target) override;

                virtual void setPosition(const sf::Vector2f &pos) override;

                std::vector<std::shared_ptr<KeyframeMarker>>& getKeyframeMarkers() { return m_keyframeMarkers; }

                std::shared_ptr<gameObj::IMultPartEntity> getPart() const { return m_part; }

                sf::FloatRect getBounds() const { return m_background.getGlobalBounds(); }

            private:
                sf::RectangleShape m_background;

                Animation::MultiPartAnimation& m_animation;
                std::shared_ptr<gameObj::IMultPartEntity> m_part;
                float& m_maxTime;
                float &m_timer;
                const Slider& m_slider;
                std::vector<std::shared_ptr<KeyframeMarker>> m_keyframeMarkers;
        };

}