/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-07 15:11:27
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 03:55:47
 *  Description:
 */

#pragma once

#include "Button.hpp"

namespace bya::ui {
    class InputBox : public AUIelement, public gameObj::Box {
        public:
            enum State { IDLE, HOVERED, PRESSED };

            InputBox(const InputBox& other) = delete;
            InputBox(const sf::Texture& texture = RESOURCE().getTexture("default", "button"), const std::string& label = "");

            void setLabel(const std::string& label);
            void reset();

            virtual void setPosition(const sf::Vector2f& pos) override;
            virtual sf::FloatRect getBounds() const override;
            virtual std::string getInput() const { return m_input; }

            std::shared_ptr<Button> getApplyButton() const { return m_applyButton; }
            std::shared_ptr<Button> getCancelButton() const { return m_cancelButton; }

            virtual void render(sf::RenderTarget& target) override;

            void setActive(bool active);
            bool isActive() const { return m_isActive; }

        private:
            bool isInputContained() const;

        protected:
            virtual void anyEventHandler(sf::Event& event) override;
            virtual void hoverEventHandler(sf::Event& event) override;
            virtual void updateHandler(float dt) override;

        protected:
            std::shared_ptr<Button> m_applyButton;
            std::shared_ptr<Button> m_cancelButton;
            std::shared_ptr<Button> m_inputBox;

            bool m_isActive;
            float m_cursorBlinkTimer = 0;

            sf::Text m_label;
            std::string m_input = "";
            sf::RectangleShape m_background;
    };
}
