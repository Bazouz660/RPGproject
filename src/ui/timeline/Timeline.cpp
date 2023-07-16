/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:22:02
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-13 16:49:48
 *  Description:
 */

#include "Timeline.hpp"

#include "logger.hpp"
#include "parsing.hpp"

namespace bya::ui {

    Timeline::Timeline()
    {
        m_slider.setProgress(0);
        m_slider.getWagon().setSize({10, 20});
        m_slider.getWagon().setOrigin({5, 10});
        auto& box = m_slider.getOuterRail();
        box.setFillColor(sf::Color(52, 155, 235, 255));
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2);

        m_currentTimeText.setString(formatTime(m_currentTime));
        m_currentTimeText.setOrigin(m_currentTimeText.getGlobalBounds().width / 2, m_currentTimeText.getGlobalBounds().height / 2);
        m_currentTimeText.setCharacterSize(20);
        m_currentTimeText.setOutlineColor(sf::Color::Black);
        m_currentTimeText.setOutlineThickness(1);

        addMarkers();
    }

    void Timeline::updateMarkersPos()
    {
        sf::FloatRect bounds = m_slider.getBounds();

        // distribute markers evenly
        float markerSpacing = bounds.width / m_markerCount;
        for (int i = 0; i <= m_markerCount; i++) {
            auto& label = m_markers[i]->getLabel();
            m_markers[i]->setPosition({bounds.left + markerSpacing * i, bounds.top - label.getGlobalBounds().height * 1.5f});
        }
    }

    void Timeline::Keyframe::setPosition()
    {
        sf::FloatRect bounds = m_slider.getBounds();
        Button::setPosition({bounds.left + (bounds.width * (this->getTime() / m_maxTime)) * 2, bounds.top + bounds.height / 2.f});
    }

    void Timeline::addKeyframe(float time)
    {
        std::shared_ptr<Keyframe> keyframe = std::make_shared<Keyframe>(time, m_maxTime, m_slider);
        keyframe->setSize({10, 10});
        keyframe->setCallback([this, keyframe]() {
            m_timer = keyframe->getTime();
            m_slider.setProgress(m_timer / m_maxTime);
        });
        keyframe->setPosition();
        m_keyframes.push_back(keyframe);
    }

    void Timeline::removeKeyframe(std::shared_ptr<Button> keyframe)
    {
        m_keyframes.erase(std::remove(m_keyframes.begin(), m_keyframes.end(), keyframe), m_keyframes.end());
    }

    void Timeline::setMaxTime(float time)
    {
        m_maxTime = time;
    }

    void Timeline::addMarkers()
    {
        m_markers.clear();
        for (int i = 0; i <= m_markerCount; i++)
            addMarker(i);
        updateMarkersPos();
        for (auto& marker : m_markers) {
            marker->setCallback([this, &marker]() {
                sf::FloatRect bounds = m_slider.getBounds();
                float progress = (marker->getPosition().x - bounds.left) / bounds.width;
                m_timer = progress * m_maxTime;
                m_slider.setProgress(progress);
            });
        }
    }

    void Timeline::addMarker(unsigned int i)
    {
        std::shared_ptr<Button> marker = std::make_shared<Button>();
        auto& label = marker->getLabel();
        label.setCharacterSize(15);
        marker->setLabel(formatTime(m_maxTime / m_markerCount * i));
        marker->setSize({label.getGlobalBounds().width, label.getGlobalBounds().height + 10});
        marker->drawBox(false);
        m_markers.push_back(marker);
    }

    void Timeline::setMarkerZoom(float zoom)
    {
        m_markerZoom = zoom;
        m_markerZoom = std::clamp(m_markerZoom, 0.1f, 2.f);

        m_markerCount = 10 * m_markerZoom;
        addMarkers();
    }

    std::string Timeline::formatTime(float time) const
    {
        // format time to string (ss::ms), round ms to 2 digits
        int seconds = time;
        int minutes = seconds / 60;
        seconds %= 60;
        int milliseconds = (time - (int)time) * 100;
        return std::to_string(seconds) + ":" + std::to_string(milliseconds);
    }

    void Timeline::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        for (auto& marker : m_markers)
            marker->handleEvent(event, window);
        for (auto& keyframe : m_keyframes)
            keyframe->handleEvent(event, window);
        m_slider.handleEvent(event, window);

        if (m_slider.getState() == Slider::State::GRABBED && !m_playing)
            m_timer = m_slider.getProgress() * m_maxTime;

        if (event.type == sf::Event::MouseWheelScrolled && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            float zoom = event.mouseWheelScroll.delta * 0.1f;
            setMarkerZoom(getMarkerZoom() + zoom);
        }

        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::Add) {
                addKeyframe(m_currentTime);
            }
            if (event.key.code == sf::Keyboard::Subtract) {
                for (auto& keyframe : m_keyframes) {
                    if (keyframe->isHovered()) {
                        removeKeyframe(keyframe);
                        break;
                    }
                }
            }

            if (event.key.code == sf::Keyboard::Space) {
                if (m_playing)
                    pause();
                else {
                    play();
                    if (m_timer >= m_maxTime) {
                        m_timer = 0;
                        m_slider.setProgress(0);
                    }
                }
            }
        }
    }

    void Timeline::update(float dt)
    {
        m_currentTime = m_slider.getProgress() * m_maxTime;
        m_currentTimeText.setString(formatTime(m_currentTime));
        m_currentTimeText.setOrigin(m_currentTimeText.getGlobalBounds().width / 2, m_currentTimeText.getGlobalBounds().height / 2);
        // display time above slider wagon
        sf::FloatRect wagonBounds = m_slider.getWagon().getBounds();
        sf::Vector2f wagonPos = {wagonBounds.left + (wagonBounds.width / 2), wagonBounds.top + (wagonBounds.height / 2)};
        m_currentTimeText.setPosition({wagonPos.x, wagonPos.y - wagonBounds.height - m_currentTimeText.getGlobalBounds().height});

        if (m_playing) {
            if (m_timer >= m_maxTime) {
                m_playing = false;
            }
            m_timer += dt;
            m_slider.setProgress(m_timer / m_maxTime);
        }
    }

    void Timeline::render(sf::RenderTarget &target)
    {
        m_slider.render(target);
        for (auto& marker : m_markers)
            marker->render(target);
        for (auto& keyframe : m_keyframes)
            keyframe->render(target);
        target.draw(m_currentTimeText);
    }

    void Timeline::setSize(const sf::Vector2f &size)
    {
        m_slider.setSize({size.x, size.y});
        updateMarkersPos();
        updateKeyframesPos();
    }

    void Timeline::updateKeyframesPos()
    {
        for (auto& keyframe : m_keyframes)
            keyframe->setPosition();
    }

    void Timeline::setPosition(const sf::Vector2f &pos)
    {
        m_slider.setPosition(pos);
        updateMarkersPos();
        updateKeyframesPos();
    }

}