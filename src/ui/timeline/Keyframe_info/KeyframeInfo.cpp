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
    {
        m_background.setFillColor(sf::Color(50, 50, 50, 255));
        m_background.setSize(sf::Vector2f(300, 350));

        m_rotationInput = std::make_shared<EditableText>();
        m_rotationInput->setPrefix("Rotation: [");
        m_rotationInput->setSuffix("]");
        m_rotationInput->setPreInpSufx("0");
        m_rotationInput->setCharacterSize(20);
        m_rotationInput->setPosition(m_background.getPosition() + sf::Vector2f(10, 80));
        addChild(m_rotationInput);

        m_easingDropDown = std::make_shared<DropDownButton>();
        m_easingDropDown->setSize(sf::Vector2f(150, 25));
        m_easingDropDown->setCharacterSize(20);
        for (auto& easing : Animation::Keyframe::easingFunctions) {
            m_easingDropDown->addOption(easing.first);
        }
        m_easingDropDown->setPosition(m_background.getPosition() + sf::Vector2f(200, 30));
        addChild(m_easingDropDown);
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

    void KeyframeInfo::anyEventHandler(sf::Event& event)
    {
        if (m_keyframe) {
            if (!m_rotationInput->isActive())
                m_keyframe->setRotation(std::stof(m_rotationInput->getInput()));
            m_keyframe->setEasingFunction(m_easingDropDown->getLabel().getString());
        }
    }

    void KeyframeInfo::updateHandler(float dt)
    {
    }

    void KeyframeInfo::setKeyframe(Animation::Keyframe& keyframe)
    {
        m_keyframe = &keyframe;
        m_rotationInput->setPreInpSufx(std::to_string(keyframe.getRotation()));
        m_easingDropDown->setLabel(keyframe.getEasingFunctionName());
    }

}