/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-08-08 18:09:39
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-08-08 18:27:15
 * @ Description:
 */

#pragma once

#include "Button.hpp"

namespace bya::ui
{
    class ButtonNBG : public Button
    {
        public:
            ButtonNBG() {
                m_drawBox = false;
            }

            virtual void setLabel(const std::string& label) override {
                Button::setLabel(label);
                setSize(sf::Vector2f(getLabel().getGlobalBounds().width + 10, getLabel().getGlobalBounds().height + 10));
            }

            virtual void setIdle() override
            {
                m_state = IDLE;
                setFillColor(sf::Color(85, 85, 85, 255));
                m_label.setFillColor(sf::Color(85, 85, 85, 255));
            }

            virtual void setHovered() override
            {
                m_state = HOVERED;
                setFillColor(sf::Color(170, 170, 170, 255));
                m_label.setFillColor(sf::Color::White);
            }

            virtual void setPressed() override
            {
                m_state = PRESSED;
                setFillColor(sf::Color::White);
                m_label.setFillColor(sf::Color::White);
            }

            virtual void setDisabled() override
            {
                m_state = DISABLED;
                setFillColor(sf::Color(85, 85, 85, 180));
                m_label.setFillColor(sf::Color(50, 50, 50, 255));
            }

            virtual ~ButtonNBG() override = default;
    };
}