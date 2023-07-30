/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-28 01:35:17
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-28 04:38:21
 *  Description:
 */

#include "KeyframeInfo.hpp"

namespace bya::ui {

    KeyframeInfo::KeyframeInfo()
    : m_rotationInput(std::make_shared<EditableText>()), m_easingDropDown(std::make_shared<DropDownButton>())
    , m_rotationObserver(*m_rotationInput), m_easingObserver(*m_easingDropDown)
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

        m_easingDropDown->setSize(sf::Vector2f(150, 25));
        m_easingDropDown->setCharacterSize(20);
        for (auto& easing : Animation::Keyframe::easingFunctions) {
            m_easingDropDown->addOption(easing.first);
        }
        m_easingDropDown->setPosition(m_background.getPosition() + sf::Vector2f(200, 30));
        addChild(m_easingDropDown);

        m_easingObserver.setOnUpdate([this]() {
            if (this->m_keyframe == nullptr)
                return;
            m_keyframe->setEasingFunction(this->m_easingDropDown->getLabel().getString());
        });
        m_rotationObserver.setOnUpdate([this]() {
            if (this->m_keyframe == nullptr)
                return;
            float rotation = std::stof(this->m_rotationInput->getInput());
            this->m_keyframe->setRotation(rotation);
            logger::debug("rotation: " + std::to_string(rotation));
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
        m_easingDropDown->setPosition(m_background.getPosition() + sf::Vector2f(200, 30));
    }

    sf::FloatRect KeyframeInfo::getBounds() const
    {
        sf::FloatRect bounds = m_background.getGlobalBounds();
        bounds = math::combineRects(bounds, getChildsBounds());
        return bounds;
    }

    void KeyframeInfo::setKeyframe(Animation::Keyframe& keyframe)
    {
        m_keyframe = &keyframe;
        m_rotationInput->setPreInpSufx(std::to_string(keyframe.getRotation()));
        m_easingDropDown->setLabel(keyframe.getEasingFunctionName());
    }
}