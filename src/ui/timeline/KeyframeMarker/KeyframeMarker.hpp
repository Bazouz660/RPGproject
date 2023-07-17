/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-17 20:40:03
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-17 21:40:46
 * @ Description:
 */

#pragma once

#include "Button.hpp"
#include "Slider.hpp"
#include "IMultPartEntity.hpp"
#include "Keyframe.hpp"

namespace bya::ui {

        // subclass of Timeline that represent a keyframe
        class KeyframeMarker : public Button {
            public:
                KeyframeMarker(float time, float& maxTime, const Slider& slider, std::shared_ptr<gameObj::IMultPartEntity> entity);
                virtual ~KeyframeMarker() override = default;

                float getTime() const { return m_time; }
                void setPosition();

                Animation::Keyframe& getKeyframe() { return m_keyframe; }

            private:
                float m_time;
                float& m_maxTime;
                const Slider& m_slider;

                Animation::Keyframe m_keyframe;
                std::shared_ptr<gameObj::IMultPartEntity> m_part;
        };
}