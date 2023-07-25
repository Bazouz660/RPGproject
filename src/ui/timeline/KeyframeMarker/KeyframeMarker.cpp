/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-17 21:08:20
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-25 19:07:54
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

    KeyframeMarker::KeyframeMarker(Timeline& timeline, float time, float& maxTime, const Slider& slider, std::shared_ptr<gameObj::IMultPartEntity> entity)
        : m_timeline(timeline),  m_time(time), m_maxTime(maxTime), m_slider(slider), m_part(entity),
        m_keyframe(entity, entity->getPosition(), entity->getSize(), entity->getPivotPoint(), entity->getOwnRotation(), entity->getZIndex())
    {
        m_keyframe.setTime(time);

        setSize({10, 10});

        setCallback([this]() {
            m_timeline.setTimer(this->getTime());
        });
    }

}