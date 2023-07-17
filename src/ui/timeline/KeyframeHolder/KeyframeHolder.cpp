/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-17 21:16:55
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-17 22:30:54
 * @ Description:
 */

#include "KeyframeHolder.hpp"

namespace bya::ui {

    KeyframeHolder::KeyframeHolder(std::shared_ptr<gameObj::IMultPartEntity> part, float& timer, float& maxTime, const Slider& slider, Animation::MultiPartAnimation& m_animation)
        : m_part(part), m_timer(timer), m_maxTime(maxTime), m_slider(slider), m_animation(m_animation)
    {
        m_background.setFillColor(sf::Color::Cyan);
        m_background.setOutlineColor(sf::Color::White);
        m_background.setOutlineThickness(1.f);
    }

    void KeyframeHolder::addKeyframeMarker(std::shared_ptr<KeyframeMarker> keyframeMarker)
    {
        m_keyframeMarkers.push_back(keyframeMarker);
        m_animation.addKeyframe(keyframeMarker->getKeyframe());
    }

    void KeyframeHolder::removeKeyframeMarker(std::shared_ptr<KeyframeMarker> keyframeMarker)
    {
        m_keyframeMarkers.erase(std::remove(m_keyframeMarkers.begin(), m_keyframeMarkers.end(), keyframeMarker), m_keyframeMarkers.end());
        m_animation.removeKeyframe(keyframeMarker->getKeyframe());
    }

    void KeyframeHolder::update(float dt)
    {
    }

    void KeyframeHolder::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        for (auto& keyframeMarker : m_keyframeMarkers)
            keyframeMarker->handleEvent(event, window);

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
                addKeyframeMarker(std::make_shared<KeyframeMarker>(m_timer, m_maxTime, m_slider, m_part));
            }
        }
    }

    void KeyframeHolder::render(sf::RenderTarget &target)
    {
        m_background.setSize({m_slider.getSize().x, 20});
        m_background.setPosition(m_slider.getBounds().left, m_slider.getBounds().top + m_slider.getBounds().height + 10);
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