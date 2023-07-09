/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-09 00:38:37
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-09 01:20:08
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

            virtual void handleEvent(sf::Event event, const sf::RenderWindow &window) override;
            virtual void update(float dt) override;

            virtual void setPosition(const sf::Vector2f &pos) override;
            virtual sf::FloatRect getBounds() const override;

            virtual void render(sf::RenderTarget &target) override;


            void addText(std::shared_ptr<EditableText> text) { m_texts.push_back(text); }
            void removeText(std::shared_ptr<EditableText> text) { m_texts.erase(std::remove(m_texts.begin(), m_texts.end(), text), m_texts.end()); }
            void removeText(unsigned int index) { if (index < m_texts.size()) m_texts.erase(m_texts.begin() + index); }
            std::shared_ptr<EditableText> getText(unsigned int index) { if (index < m_texts.size()) return m_texts[index]; return nullptr; }
            std::vector<std::shared_ptr<EditableText>>& getTexts() { return m_texts; }

        protected:
            Axis m_axis = HORIZONTAL;
            sf::Vector2f m_position;
            std::vector<std::shared_ptr<EditableText>> m_texts;
    };
}