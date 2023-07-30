/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-17 21:08:20
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 03:40:46
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

    KeyframeMarker::KeyframeMarker(float time, float& maxTime, const Slider& slider)
        : m_time(time), m_maxTime(maxTime), m_slider(slider)
    {
        setSize({10, 10});
    }

}