/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 22:01:35
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-23 17:39:22
 * @ Description:
 */

#pragma once

#include "Text.hpp"

namespace bya::ui
{
    class EditableText : public Text
    {
        public:
            EditableText(const std::string& text = "", unsigned int size = 30,
            const sf::Font& font = RESOURCE().getFont("font", "game_font"));

            virtual ~EditableText() = default;

            void setString(const std::string& string);

            virtual sf::FloatRect getBounds() const override;

            virtual void setActive(bool active);
            virtual bool isActive() const { return m_isActive; }

            virtual void setMaxLength(unsigned int length) { m_maxLength = length; }
            virtual unsigned int getMaxLength() const { return m_maxLength; }

            virtual void allowNumbers(bool allow) { m_allowNumbers = allow; }
            virtual void allowLetters(bool allow) { m_allowLetters = allow; }
            virtual void allowSpecialChars(bool allow) { m_allowSpecialChars = allow; }
            virtual void onlyNumbers(bool allow);

            virtual bool isNumberAllowed() const { return m_allowNumbers; }
            virtual bool isLetterAllowed() const { return m_allowLetters; }
            virtual bool isSpecialCharAllowed() const { return m_allowSpecialChars; }
            virtual bool isOnlyNumbers() const { return m_onlyNumbers; }

            virtual void setPrefix(const std::string& prefix) { m_prefix = prefix; setString(m_input); }
            virtual void setSuffix(const std::string& suffix) { m_suffix = suffix; setString(m_input); }

            virtual std::string getPrefix() const { return m_prefix; }
            virtual std::string getSuffix() const { return m_suffix; }
            virtual std::string getInput() const { return m_input; }

        protected:
            void validateInput();
            virtual void hoverEventHandler(sf::Event& event) override;
            virtual void anyEventHandler(sf::Event& event) override;
            virtual void updateHandler(float dt) override;

        protected:
            bool m_isActive = false;
            bool m_allowNumbers = true;
            bool m_allowLetters = true;
            bool m_allowSpecialChars = false;
            bool m_onlyNumbers = false;
            unsigned int m_maxLength = 0;
            unsigned int m_cursorPosition = 0;
            float m_cursorBlinkTimer = 0;
            std::string m_input;
            std::string m_oldInput;
            std::string m_prefix;
            std::string m_suffix;
            sf::Color m_activeColor = sf::Color::White;
    };
}