/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-17 21:08:20
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-31 03:46:01
 * @ Description:
 */

#include "KeyframeMarker.hpp"
#include "Timeline.hpp"

namespace bya::ui {

    void KeyframeMarker::setPosition()
    {
        sf::FloatRect bounds = m_slider.getBounds();
        Button::setPosition({bounds.left + (bounds.width * (this->getTime() / m_maxTime)), bounds.top + bounds.height + 20});
    }

    void KeyframeMarker::setTime(float time)
    {
        m_keyframe->setTime(time);
        setPosition();
    }

    KeyframeMarker::KeyframeMarker(float time, float& maxTime, const Slider& slider, std::shared_ptr<Animation::Keyframe> keyframe)
        : m_maxTime(maxTime), m_slider(slider), m_keyframe(keyframe)
    {
        setSize({10, 10});
    }

}