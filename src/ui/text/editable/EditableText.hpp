/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 22:01:35
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-28 19:07:17
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

            enum class Type { ANY, TEXT, ALPHA_NUM, UNSIGNED_INT, SIGNED_INT, DECIMAL };

            void setPreInpSufx(const std::string& string);

            virtual sf::FloatRect getBounds() const override;

            void setActive(bool active);
            bool isActive() const { return m_isActive; }

            void setMaxLength(unsigned int length) { m_maxLength = length; }

            void setPrefix(const std::string& prefix) { m_prefix = prefix; setPreInpSufx(m_input); }
            void setSuffix(const std::string& suffix) { m_suffix = suffix; setPreInpSufx(m_input); }

            std::string getPrefix() const { return m_prefix; }
            std::string getSuffix() const { return m_suffix; }
            std::string getInput() const { return m_input; }

            void setType(Type type);
            Type getType() const { return m_type; }

        protected:
            void validateInput();
            virtual void hoverEventHandler(sf::Event& event) override;
            virtual void anyEventHandler(sf::Event& event) override;
            virtual void updateHandler(float dt) override;
            void setString(const sf::String& string) { Text::setString(string); }

        protected:
            bool m_isActive = false;
            unsigned int m_maxLength = 0;
            unsigned int m_cursorPosition = 0;
            float m_cursorBlinkTimer = 0;
            std::string m_input;
            std::string m_oldInput;
            std::string m_prefix;
            std::string m_suffix;
            sf::Color m_activeColor = sf::Color::White;
            static std::map<Type, std::function<bool(char)>> m_checkInputMap;
            std::map<Type, std::function<void()>> m_validateInputMap;
            Type m_type = Type::ANY;
    };
}