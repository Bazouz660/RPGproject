/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-17 20:40:03
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-31 03:46:41
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
                KeyframeMarker(float time, float& maxTime, const Slider& slider, std::shared_ptr<Animation::Keyframe> keyframe);
                virtual ~KeyframeMarker() override = default;

                float getTime() const { return m_keyframe->getTime(); }
                void setTime(float time);
                void setPosition();
                std::shared_ptr<Animation::Keyframe> getKeyframe() const { return m_keyframe; }

            private:
                float& m_maxTime;
                const Slider& m_slider;
                std::shared_ptr<Animation::Keyframe> m_keyframe;
        };
}