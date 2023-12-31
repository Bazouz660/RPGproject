/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-17 21:16:55
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-31 21:58:55
 * @ Description:
 */

#include "Timeline.hpp"

namespace bya::ui {

    KeyframeHolder::KeyframeHolder(Timeline& timeline, std::shared_ptr<gameObj::IMultPartEntity> part, float& timer, float& maxTime, const Slider& slider, Animation::MultiPartAnimation& m_animation)
        : m_timeline(timeline),  m_part(part), m_timer(timer), m_maxTime(maxTime), m_slider(slider), m_animation(m_animation)
    {
        m_background.setFillColor(sf::Color::Cyan);
        m_background.setOutlineColor(sf::Color::White);
        m_background.setOutlineThickness(1.f);
    }

    void KeyframeHolder::addKeyframeMarker(std::shared_ptr<Animation::Keyframe> newKeyframe)
    {
        auto keyframeMarker = std::make_shared<KeyframeMarker>(newKeyframe->getTime(), m_maxTime, m_slider, newKeyframe);
        keyframeMarker->setCallback([this, keyframeMarker]() {
            m_timeline.setTimer(keyframeMarker->getTime());
            this->setSelectedKeyframeMarker(keyframeMarker);
            m_timeline.getKeyframeInfo().setKeyframeMarker(keyframeMarker);
        });
        m_keyframeMarkers.push_back(keyframeMarker);
        m_children.add("keyframeMarke_" + std::to_string(keyframeMarker->getTime()), keyframeMarker);
    }

    void KeyframeHolder::addKeyframeMarker(float time)
    {
        auto keyframe = std::make_shared<Animation::Keyframe>(m_part);
        keyframe->setTime(time)
        .setPosition(m_part->getPosition())
        .setRotation(m_part->getOwnRotation())
        .setSize(m_part->getSize())
        .setPivot(m_part->getOrigin())
        .setZIndex(m_part->getZIndex())
        .setEasingFunction(Animation::Keyframe::easingFunctions["linear"]);

        m_animation.addKeyframe(keyframe);

        auto keyframeMarker = std::make_shared<KeyframeMarker>(time, m_maxTime, m_slider, keyframe);
        keyframeMarker->setCallback([this, keyframeMarker]() {
            m_timeline.setTimer(keyframeMarker->getTime());
            this->setSelectedKeyframeMarker(keyframeMarker);
            m_timeline.getKeyframeInfo().setKeyframeMarker(keyframeMarker);
        });
        m_keyframeMarkers.push_back(keyframeMarker);
        m_children.add("keyframeMarke_" + std::to_string(keyframeMarker->getTime()), keyframeMarker);
    }

    void KeyframeHolder::removeKeyframeMarker(std::shared_ptr<KeyframeMarker> keyframeMarker)
    {
        m_animation.removeKeyframe(m_part, keyframeMarker->getTime());
        m_keyframeMarkers.erase(std::remove(m_keyframeMarkers.begin(), m_keyframeMarkers.end(), keyframeMarker), m_keyframeMarkers.end());
        m_children.remove(keyframeMarker);
    }

    void KeyframeHolder::anyEventHandler(sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Delete) {
                for (auto& keyframeMarker : m_keyframeMarkers) {
                    if (keyframeMarker->isHovered()) {
                        removeKeyframeMarker(keyframeMarker);
                        break;
                    }
                }
            }
            if (event.key.code == sf::Keyboard::Add) {
                addKeyframeMarker(m_timer);
            }
        }
    }

    void KeyframeHolder::render(sf::RenderTarget &target)
    {
        m_background.setSize({m_slider.getSize().x + 20, 20});
        m_background.setPosition(m_slider.getBounds().left - 10, m_slider.getBounds().top + m_slider.getBounds().height + 10);
        target.draw(m_background);
        for (auto& keyframeMarker : m_keyframeMarkers)
            keyframeMarker->render(target);
    }

    void KeyframeHolder::setPosition(const sf::Vector2f &pos)
    {
        m_background.setPosition(pos);
        for (auto& keyframeMarker : m_keyframeMarkers)
            keyframeMarker->setPosition();
    }

}