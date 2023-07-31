/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-09 00:38:37
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-31 19:42:17
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


            void addText(std::shared_ptr<EditableText> text) { m_children.add("text_" + std::to_string(m_children.size()), text); }
            void removeText(std::shared_ptr<EditableText> text) { m_children.remove(text); }
            std::shared_ptr<EditableText> getText(unsigned int index) { return m_children.get<EditableText>(index); }
        protected:
            virtual void anyEventHandler(sf::Event &event) override;

        protected:
            Axis m_axis = HORIZONTAL;
            sf::Vector2f m_position;
    };
}