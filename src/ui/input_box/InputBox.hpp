/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-07 15:11:27
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-07 15:32:08
 *  Description:
 */

#pragma once

#include "Button.hpp"

namespace bya::ui {
    class InputBox : public AUIelement, public gameObj::Box {
        public:
            enum State { IDLE, HOVERED, PRESSED };

            InputBox(const InputBox& other) = delete;
            InputBox(const sf::Texture& texture = getResource().getTexture("default", "button"), const std::string& label = "");

            void setLabel(const std::string& label);

            virtual void handleEvent(sf::Event event, const sf::RenderWindow& window) override;
            virtual void update(float dt) override;

            virtual void setPosition(const sf::Vector2f& pos) override;
            virtual sf::FloatRect getBounds() const override;
            virtual std::string getInput() const { return m_input; }

            std::shared_ptr<Button> getApplyButton() const { return m_applyButton; }
            std::shared_ptr<Button> getCancelButton() const { return m_cancelButton; }

            virtual void render(sf::RenderTarget& target) override;

            void setActive(bool active);
            bool isActive() const { return m_isActive; }
            void setOpen(bool open) { m_isOpen = open; m_input = ""; setActive(open); }
            bool isOpen() const { return m_isOpen; }

        private:
            bool isInputContained() const;

        protected:
            std::shared_ptr<Button> m_applyButton;
            std::shared_ptr<Button> m_cancelButton;
            std::shared_ptr<Button> m_inputBox;

            bool m_isActive;
            bool m_isOpen = false;
            float m_cursorBlinkTimer = 0;

            sf::Text m_label;
            std::string m_input = "";
            sf::RectangleShape m_background;
    };
}
