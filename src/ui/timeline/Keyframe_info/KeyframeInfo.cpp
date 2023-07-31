/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-28 01:35:17
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-28 04:38:21
 *  Description:
 */

#include "KeyframeInfo.hpp"
#include "parsing.hpp"

namespace bya::ui {

    KeyframeInfo::KeyframeInfo()
    : m_rotationInput(std::make_shared<EditableText>()), m_easingDropDown(std::make_shared<DropDownButton>()), m_timeInput(std::make_shared<EditableText>())
    , m_rotationObserver(*m_rotationInput), m_easingObserver(*m_easingDropDown), m_timeObserver(*m_timeInput)
    {
        m_background.setFillColor(sf::Color(50, 50, 50, 255));
        m_background.setSize(sf::Vector2f(300, 350));

        m_rotationInput->setPrefix("Rotation: [");
        m_rotationInput->setSuffix("]");
        m_rotationInput->setPreInpSufx("0");
        m_rotationInput->setCharacterSize(20);
        m_rotationInput->setType(EditableText::Type::DECIMAL);
        m_rotationInput->setPosition(m_background.getPosition() + sf::Vector2f(10, 80));
        addChild(m_rotationInput);

        m_timeInput->setPrefix("Time: [");
        m_timeInput->setSuffix("]");
        m_timeInput->setPreInpSufx("0");
        m_timeInput->setCharacterSize(20);
        m_timeInput->setType(EditableText::Type::DECIMAL);
        m_timeInput->setPosition(m_background.getPosition() + sf::Vector2f(10, 30));
        addChild(m_timeInput);

        m_easingDropDown->setSize(sf::Vector2f(150, 25));
        m_easingDropDown->setCharacterSize(20);
        for (auto& easing : Animation::Keyframe::easingFunctions) {
            m_easingDropDown->addOption(easing.first);
        }
        m_easingDropDown->setPosition(m_background.getPosition() + sf::Vector2f(200, 30));
        addChild(m_easingDropDown);

        m_easingObserver.setOnUpdate([this]() {
            if (this->m_keyframeMarker == nullptr)
                return;
            auto keyframe = this->m_keyframeMarker->getKeyframe();
            keyframe->setEasingFunction(this->m_easingDropDown->getLabel().getString());
        });
        m_rotationObserver.setOnUpdate([this]() {
            if (this->m_keyframeMarker == nullptr)
                return;
            float rotation = std::stof(this->m_rotationInput->getInput());
            auto keyframe = this->m_keyframeMarker->getKeyframe();
            keyframe->setRotation(rotation);
        });
        m_timeObserver.setOnUpdate([this]() {
            if (this->m_keyframeMarker == nullptr)
                return;
            auto keyframe = this->m_keyframeMarker->getKeyframe();
            float time = std::stof(this->m_timeInput->getInput());
            m_keyframeMarker->setTime(time);
        });
    }

    void KeyframeInfo::render(sf::RenderTarget &target)
    {
        target.draw(m_background);

        for (auto& child : m_children) {
            child.handle->render(target);
        }
    }

    void KeyframeInfo::setPosition(const sf::Vector2f &pos)
    {
        m_background.setPosition(pos);
        m_rotationInput->setPosition(m_background.getPosition() + sf::Vector2f(10, 80));
        m_timeInput->setPosition(m_background.getPosition() + sf::Vector2f(10, 30));
        m_easingDropDown->setPosition(m_background.getPosition() + sf::Vector2f(200, 30));
    }

    sf::FloatRect KeyframeInfo::getBounds() const
    {
        sf::FloatRect bounds = m_background.getGlobalBounds();
        bounds = math::combineRects(bounds, getChildsBounds());
        return bounds;
    }

    void KeyframeInfo::setKeyframeMarker(std::shared_ptr<KeyframeMarker> keyframeMarker)
    {
        m_keyframeMarker = keyframeMarker;
        auto keyframe = m_keyframeMarker->getKeyframe();
        m_rotationInput->setPreInpSufx(parsing::floatToString(keyframe->getRotation()));
        m_timeInput->setPreInpSufx(parsing::floatToString(keyframe->getTime()));
        m_easingDropDown->setLabel(keyframe->getEasingFunctionName());
    }
}