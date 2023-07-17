/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:22:02
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-17 22:30:24
 *  Description:
 */

#include "Timeline.hpp"

#include "logger.hpp"
#include "parsing.hpp"

#include "KeyframeHolder.hpp"

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

    void Timeline::setMaxTime(float time)
    {
        m_maxTime = time;
        m_slider.setProgress(0);

        // update markers
        addMarkers();

        //// check if keyframes are still in range
        //for (auto& partTimeline : m_partsTimelines.getElements()) {
        //    for (auto& keyframe : partTimeline->getKeyframeMarkers()) {
        //        if (keyframe->getTime() > m_maxTime) {
        //            removeKeyframeMarker(keyframe);
        //            break;
        //        }
        //    }
        //}
//
        //// update keyframes
        //for (auto& partTimeline : m_partsTimelines.getElements()) {
        //    for (auto& keyframe : partTimeline->getKeyframeMarkers()) {
        //        keyframe->setPosition();
        //    }
        //}
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

    void Timeline::setEntity(std::shared_ptr<gameObj::IMultPartEntity> entity)
    {
        m_entity = entity;

        if (m_selectedPart == nullptr) {
            setSelectedPart(m_entity);
        }
    }

    void Timeline::setSelectedPart(std::shared_ptr<gameObj::IMultPartEntity> part)
    {
        m_selectedPart = part;

        if (m_selectedPart == nullptr)
            return;

        bool found = false;
        for (auto& keyframeHolder : m_keyframeHolders.getElements()) {
            if (keyframeHolder->getPart() == part) {
                found = true;
                m_keyframeHolders.setSelectedElement(keyframeHolder);
                break;
            }
        }
        if (!found) {
            auto holder = std::make_shared<KeyframeHolder>(part, m_timer, m_maxTime, m_slider, m_animation);
            m_keyframeHolders.addElement(holder);
            m_keyframeHolders.setSelectedElement(holder);
        }
    }

    void Timeline::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        if (m_entity == nullptr)
            return;

        for (auto& marker : m_markers)
            marker->handleEvent(event, window);
        m_slider.handleEvent(event, window);

        m_keyframeHolders.handleEvent(event, window);

        if (m_slider.getState() == Slider::State::GRABBED && !m_playing)
            m_timer = m_slider.getProgress() * m_maxTime;

        if (event.type == sf::Event::MouseWheelScrolled && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            float zoom = event.mouseWheelScroll.delta * 0.1f;
            setMarkerZoom(getMarkerZoom() + zoom);
        }

        if (event.type == sf::Event::KeyPressed) {
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
            m_animation.setTimer(m_timer);
            m_animation.update();
        }
    }

    void Timeline::render(sf::RenderTarget &target)
    {
        m_slider.render(target);
        m_keyframeHolders.setPosition({m_slider.getBounds().left, m_slider.getBounds().top + m_slider.getBounds().height + 10});
        m_keyframeHolders.render(target);
        for (auto& marker : m_markers)
            marker->render(target);
        target.draw(m_currentTimeText);
    }

    void Timeline::setSize(const sf::Vector2f &size)
    {
        m_slider.setSize({size.x, size.y});
        updateMarkersPos();
    }

    void Timeline::setPosition(const sf::Vector2f &pos)
    {
        m_slider.setPosition(pos);
        updateMarkersPos();
    }

    void Timeline::clear()
    {
    }

    void Timeline::play()
    {
        m_animation.play();
        m_playing = true;
    }

    void Timeline::pause()
    {
        m_playing = false;
        m_animation.pause();
    }

}