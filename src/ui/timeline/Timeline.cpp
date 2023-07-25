/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:22:02
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-25 21:59:49
 *  Description:
 */

#include "Timeline.hpp"

#include "logger.hpp"
#include "parsing.hpp"
#include "math.hpp"

#include "KeyframeHolder.hpp"

namespace bya::ui {

    Timeline::Timeline()
    {
        m_slider = std::make_shared<Slider>();
        m_slider->getWagon().setSize({10, 20});
        m_slider->getWagon().setOrigin({5, 10});
        addChild(m_slider);

        setTimer(0);

        auto& box = m_slider->getOuterRail();
        box.setFillColor(sf::Color(52, 155, 235, 255));
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2);

        m_keyframeHolders = std::make_shared<ScrollBox<KeyframeHolder>>();
        addChild(m_keyframeHolders);

        m_currentTimeText = std::make_shared<Text>();
        m_currentTimeText->setString(formatTime(m_currentTime));
        m_currentTimeText->setOrigin(m_currentTimeText->getGlobalBounds().width / 2, m_currentTimeText->getGlobalBounds().height / 2);
        m_currentTimeText->setCharacterSize(20);
        m_currentTimeText->setOutlineColor(sf::Color::Black);
        m_currentTimeText->setOutlineThickness(1);
        addChild(m_currentTimeText);

        addMarkers();
    }

    void Timeline::updateMarkersPos()
    {
        sf::FloatRect bounds = m_slider->getBounds();

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
        setTimer(0);

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
        // remove old markers
        for (auto& marker : m_markers)
            removeChild(marker);
        m_markers.clear();
        for (int i = 0; i <= m_markerCount; i++)
            addMarker(i);
        updateMarkersPos();
        for (auto& marker : m_markers) {
            marker->setCallback([this, &marker]() {
                sf::FloatRect bounds = m_slider->getBounds();
                float progress = (marker->getPosition().x - bounds.left) / bounds.width;
                setTimer(progress * m_maxTime);
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
        addChild(marker);
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
        m_animation.setEntity(entity);
    }

    void Timeline::setSelectedPart(std::shared_ptr<gameObj::IMultPartEntity> part)
    {
        m_selectedPart = part;

        if (m_selectedPart == nullptr)
            return;

        bool found = false;
        for (auto& keyframeHolder : m_keyframeHolders->getElements()) {
            if (keyframeHolder->getPart() == part) {
                found = true;
                m_keyframeHolders->setSelectedElement(keyframeHolder);
                break;
            }
        }
        if (!found) {
            auto holder = std::make_shared<KeyframeHolder>(*this, part, m_timer, m_maxTime, *m_slider, m_animation);
            m_keyframeHolders->addElement(holder);
            m_keyframeHolders->setSelectedElement(holder);
        }
    }

    void Timeline::anyEventHandler(sf::Event& event)
    {
        if (m_entity == nullptr)
            return;

        if (m_slider->getState() == Slider::State::GRABBED && !m_playing)
            setTimer(m_slider->getProgress() * m_maxTime);

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
                        setTimer(0);
                    }
                }
            }
        }
    }

    void Timeline::updateHandler(float dt)
    {
        m_currentTime = m_slider->getProgress() * m_maxTime;
        m_currentTimeText->setString(formatTime(m_currentTime));
        m_currentTimeText->setOrigin(m_currentTimeText->getGlobalBounds().width / 2, m_currentTimeText->getGlobalBounds().height / 2);
        // display time above slider wagon
        sf::FloatRect wagonBounds = m_slider->getWagon().getBounds();
        sf::Vector2f wagonPos = {wagonBounds.left + (wagonBounds.width / 2), wagonBounds.top + (wagonBounds.height / 2)};
        m_currentTimeText->setPosition({wagonPos.x, wagonPos.y - wagonBounds.height - m_currentTimeText->getGlobalBounds().height});

        if (m_playing) {
            if (m_timer >= m_maxTime) {
                m_playing = false;
            }
            setTimer(m_timer + dt);
        }
    }

    void Timeline::render(sf::RenderTarget &target)
    {
        m_slider->render(target);
        m_keyframeHolders->setPosition({m_slider->getBounds().left - 10, m_slider->getBounds().top + m_slider->getBounds().height + 10});
        m_keyframeHolders->render(target);
        for (auto& marker : m_markers)
            marker->render(target);
        m_currentTimeText->render(target);
    }

    void Timeline::setSize(const sf::Vector2f &size)
    {
        m_slider->setSize({size.x, size.y});
        updateMarkersPos();
    }

    void Timeline::setPosition(const sf::Vector2f &pos)
    {
        m_slider->setPosition(pos);
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

    sf::FloatRect Timeline::getBounds() const
    {
        std::unique_ptr<sf::FloatRect> resBounds = nullptr;

        for (auto &child : m_children)
        {
            auto bounds = child.handle->getBounds();
            if (resBounds == nullptr)
                resBounds = std::make_unique<sf::FloatRect>(bounds);
            else
                *resBounds = math::combineRects(*resBounds, bounds);
        }

        return *resBounds;
    }

    void Timeline::loadAnimation(std::string path)
    {
        // clear current animation
        m_animation = Animation::MultiPartAnimation(m_entity);
        m_keyframeHolders->clear();

        m_animation.loadFromJson(path);

        // add keyframes to timeline
        for (auto& [entity, keyframes] : m_animation.getKeyframesMap()) {
            setSelectedPart(entity);
            for (auto& keyframe : keyframes) {
                m_keyframeHolders->getSelectedElement()->addKeyframeMarker(std::make_shared<KeyframeMarker>(*this, keyframe.getTime(), m_maxTime, *m_slider, entity));
            }
        }
    }

    void Timeline::saveAnimation(std::string path)
    {
        m_animation.saveToJson(path);
    }

    void Timeline::setTimer(float timer)
    {
        m_timer = timer;
        m_slider->setProgress(m_timer / m_maxTime);
        m_animation.setTimer(m_timer);
        m_animation.update();
    }

}