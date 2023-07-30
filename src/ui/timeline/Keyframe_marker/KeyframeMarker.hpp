/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-17 20:40:03
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 03:40:51
 * @ Description:
 */

#pragma once

#include "Button.hpp"
#include "Slider.hpp"
#include "IMultPartEntity.hpp"
#include "Keyframe.hpp"

namespace bya::ui {

        // subclass of Timeline that represent a keyframe
        class Timeline;

        class KeyframeMarker : public Button {
            public:
                KeyframeMarker(float time, float& maxTime, const Slider& slider);
                virtual ~KeyframeMarker() override = default;

                float getTime() const { return m_time; }
                void setPosition();

            private:
                float m_time;
                float& m_maxTime;
                const Slider& m_slider;
        };
}