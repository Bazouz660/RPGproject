/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-09 00:38:37
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-24 19:12:01
 * @ Description:
 */

#pragma once

#include "EditableText.hpp"

namespace bya::ui {

    class EditableTextList : public AUIelement {

        public:
            enum Axis { HORIZONTAL, VERTICAL };

            EditableTextList() = default;
            ~EditableTextList() = default;

            virtual void setPosition(const sf::Vector2f &pos) override;
            virtual sf::FloatRect getBounds() const override;

            virtual void render(sf::RenderTarget &target) override;


            void addText(std::shared_ptr<EditableText> text) { addChild(text); }
            void removeText(std::shared_ptr<EditableText> text) { removeChild(text); }
            void removeText(unsigned int index) { removeChild(m_children[index].handle); }
            EditableText* getText(unsigned int index) { return dynamic_cast<EditableText*>(m_children[index].handle.get()); }

        protected:
            virtual void anyEventHandler(sf::Event &event) override;

        protected:
            Axis m_axis = HORIZONTAL;
            sf::Vector2f m_position;
    };
}