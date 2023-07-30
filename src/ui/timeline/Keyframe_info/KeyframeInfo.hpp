/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-28 01:29:20
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-28 03:07:28
 *  Description:
 */

#pragma once

#include "Keyframe.hpp"
#include "DropDownButton.hpp"
#include "EditableText.hpp"
#include "KeyframeMarker.hpp"
#include "Observer.hpp"

namespace bya::ui {

    // class that displays a keyframe info and allows to edit it
    class KeyframeInfo : public AUIelement {
        public:
            KeyframeInfo();
            virtual ~KeyframeInfo() = default;

            virtual void render(sf::RenderTarget &target) override;
            virtual void setPosition(const sf::Vector2f &pos) override;

            void setKeyframe(Animation::Keyframe& keyframe);

            sf::FloatRect getBounds() const;

        private:
            sf::RectangleShape m_background;

            Animation::Keyframe* m_keyframe;

            std::shared_ptr<EditableText> m_rotationInput;
            std::shared_ptr<DropDownButton> m_easingDropDown;

            Observer m_rotationObserver;
            Observer m_easingObserver;
    };

}