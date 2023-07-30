/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 22:02:43
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 03:29:10
 * @ Description:
 */

#include "EditableText.hpp"
#include "context.hpp"
#include "Clock.hpp"

namespace bya::ui
{

    std::map<EditableText::Type, std::function<bool(char)>> EditableText::m_checkInputMap = {
        { EditableText::Type::ANY, [](char c) {
            return true;
        }},
        { EditableText::Type::TEXT, [](char c) {
            return std::isalpha(c);
        }},
        { EditableText::Type::ALPHA_NUM, [](char c) {
            return std::isalnum(c);
        }},
        { EditableText::Type::UNSIGNED_INT, [](char c) {
            return std::isdigit(c);
        }},
        { EditableText::Type::SIGNED_INT, [](char c) {
            return std::isdigit(c) || c == '-';
        }},
        { EditableText::Type::DECIMAL, [](char c) {
            return std::isdigit(c) || c == '.' || c == '-';
        }}
    };

    EditableText::EditableText(const std::string& text, unsigned int size,
    const sf::Font& font)
        : Text(text, size, font)
    {
        m_input = text;
        m_oldInput = text;

        m_validateInputMap[Type::ANY] = [this]() {
            m_input = m_input.substr(0, m_maxLength);
        };
        m_validateInputMap[Type::TEXT] = [this]() {
            m_input = m_input.substr(0, m_maxLength);
        };
        m_validateInputMap[Type::ALPHA_NUM] = [this]() {
            m_input = m_input.substr(0, m_maxLength);
        };
        m_validateInputMap[Type::UNSIGNED_INT] = [this]() {
            m_input = m_input.substr(0, m_maxLength);
        };
        m_validateInputMap[Type::SIGNED_INT] = [this]() {
            bool isNegative = !m_input.empty() && m_input[0] == '-';
            if (isNegative)
                m_input.erase(m_input.begin()); // Remove negative sign temporarily
            m_input.erase(std::remove_if(m_input.begin(), m_input.end(), [](char c) {
                return !std::isdigit(c);
            }), m_input.end());
            m_input.erase(m_input.begin(), std::find_if(m_input.begin(), m_input.end(), [](char c) {
                return c != '0';
            }));
            if (m_input.empty()) {
                m_input = "0"; // Set it to zero as a fallback
                return; // Or you can throw an error here, depending on your needs
            }
            if (isNegative)
                m_input.insert(m_input.begin(), '-');
        };
        m_validateInputMap[Type::DECIMAL] = [this]() {
            bool isNegative = !m_input.empty() && m_input[0] == '-';
            if (isNegative)
                m_input.erase(m_input.begin()); // Remove negative sign temporarily
            m_input.erase(std::remove_if(m_input.begin(), m_input.end(), [](char c) {
                return !std::isdigit(c) && c != '.';
            }), m_input.end());
            size_t decimalPos = m_input.find('.');
            if (decimalPos != std::string::npos)
                m_input.erase(std::remove(m_input.begin() + decimalPos + 1, m_input.end(), '.'), m_input.end());
            m_input.erase(m_input.begin(), std::find_if(m_input.begin(), m_input.end(), [](char c) {
                return c != '0';
            }));
            if (m_input.empty() || m_input == ".") {
                m_input = "0"; // Set it to zero as a fallback
                return; // Or you can throw an error here, depending on your needs
            }
            if (isNegative)
                m_input.insert(m_input.begin(), '-');
            if (decimalPos != std::string::npos) {
                if (decimalPos == 0) {
                    m_input.insert(m_input.begin(), '0'); // Insert leading zero if necessary (e.g., ".123" -> "0.123")
                } else if (decimalPos == m_input.size() - 1)
                    m_input.pop_back(); // Remove trailing dot (e.g., "123." -> "123")
            }
        };
    }

    void EditableText::setPreInpSufx(const std::string& string)
    {
        m_input = string;
        m_oldInput = string;
        setString(m_prefix + m_input + m_suffix);
    }

    void EditableText::setActive(bool active)
    {
        m_isActive = active;
        if (active)
            setFillColor(m_activeColor);
        else
            setFillColor(sf::Color::White);

        setPreInpSufx(m_oldInput);
        m_cursorPosition = m_input.size();
    }

    void EditableText::updateHandler(float dt)
    {
        if (!isActive())
            return;

        std::string str = m_input;

        if (getTime().asSeconds() > m_cursorBlinkTimer + 0.75 && isActive()) {
            m_cursorBlinkTimer = getTime().asSeconds();
            str.insert(m_cursorPosition, "|");
            setString(m_prefix + str + m_suffix);
        } else if (getTime().asSeconds() > m_cursorBlinkTimer + 0.5 || (!isActive())) {
            setString(m_prefix + str + m_suffix);
        }
    }

    void EditableText::validateInput()
    {
        m_validateInputMap[m_type]();
        m_oldInput = m_input;
        notify();
    }

    sf::FloatRect EditableText::getBounds() const
    {
        return getGlobalBounds();
    }

    void EditableText::hoverEventHandler(sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
            && getBounds().contains(context::getMousePosition()) && !isActive()) {
            setActive(true);
        }
    }

    void EditableText::anyEventHandler(sf::Event& event)
    {
        if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
            && !getBounds().contains(context::getMousePosition()) && isActive())
            || event.type == sf::Event::TextEntered && event.text.unicode == 27) {
            setActive(false);
        }

        if (event.type == sf::Event::KeyPressed && isActive()) {
            if (event.key.code == sf::Keyboard::Left && m_cursorPosition > 0) {
                m_cursorPosition--;
                m_cursorBlinkTimer = 0;
            } else if (event.key.code == sf::Keyboard::Right && m_cursorPosition < m_input.size()) {
                m_cursorPosition++;
                m_cursorBlinkTimer = 0;
            } else if (event.key.code == sf::Keyboard::BackSpace && m_cursorPosition > 0) {
                m_input.erase(m_cursorPosition - 1, 1);
                m_cursorPosition--;
                m_cursorBlinkTimer = 0;
            }
        }

        if (event.type == sf::Event::TextEntered && isActive()) {
            if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 27) {
                char c = static_cast<char>(event.text.unicode);
                if (!m_checkInputMap.at(m_type)(c))
                    return;
                m_input.insert(m_cursorPosition, 1, c);
                m_cursorBlinkTimer = 0;
                m_cursorPosition++;
            }
            std::string str = m_oldInput;
            setPreInpSufx(m_input);
            m_oldInput = str;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && isActive()) {
            validateInput();
            setActive(false);
        }
    }

    void EditableText::setType(Type type)
    {
        m_type = type;
        // reset the input
        m_input = m_oldInput;
        // validate the input
        validateInput();
    }
}