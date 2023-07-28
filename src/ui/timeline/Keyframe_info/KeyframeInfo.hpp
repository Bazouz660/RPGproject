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

namespace bya::ui {

    // class that displays a keyframe info and allows to edit it
    class KeyframeInfo : public AUIelement {
        public:
            KeyframeInfo();
            virtual ~KeyframeInfo() = default;

            virtual void render(sf::RenderTarget &target) override;
            virtual void setPosition(const sf::Vector2f &pos) override;

            void setKeyframe(Animation::Keyframe& keyframe);
            const Animation::Keyframe& getKeyframe() const { return *m_keyframe; }

            sf::FloatRect getBounds() const;

        protected:
            virtual void anyEventHandler(sf::Event& event) override;
            virtual void updateHandler(float dt) override;

        private:
            Animation::Keyframe* m_keyframe = nullptr;
            sf::RectangleShape m_background;

            std::shared_ptr<EditableText> m_rotationInput;
            std::shared_ptr<DropDownButton> m_easingDropDown;
    };

}