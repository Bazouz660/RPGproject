/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 22:02:43
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-09 01:58:36
 * @ Description:
 */

#include "EditableText.hpp"
#include "info.hpp"
#include "Clock.hpp"

namespace bya::ui
{
    EditableText::EditableText(const std::string& text, unsigned int size,
    const sf::Font& font)
        : Text(text, size, font)
    {
        m_input = text;
        m_oldInput = text;
    }

    void EditableText::setString(const std::string& string)
    {
        m_input = string;
        m_oldInput = string;
        Text::setString(m_prefix + m_input + m_suffix);
    }

    void EditableText::setActive(bool active)
    {
        m_isActive = active;
        if (active)
            setFillColor(m_activeColor);
        else
            setFillColor(sf::Color::White);

        setString(m_oldInput);
        m_cursorPosition = m_input.size();
    }

    void EditableText::update(float dt)
    {
        if (!isActive())
            return;

        std::string str = m_input;

        if (getTime().asSeconds() > m_cursorBlinkTimer + 0.75 && isActive()) {
            m_cursorBlinkTimer = getTime().asSeconds();
            str.insert(m_cursorPosition, "|");
            Text::setString(m_prefix + str + m_suffix);
        } else if (getTime().asSeconds() > m_cursorBlinkTimer + 0.5 || (!isActive())) {
            Text::setString(m_prefix + str + m_suffix);
        }
    }

    void EditableText::onlyNumbers(bool allow)
    {
        m_onlyNumbers = allow;
        m_allowNumbers = allow;
        m_allowLetters = !allow;
        m_allowSpecialChars = !allow;
    }

    void EditableText::validateInput()
    {
        m_oldInput = m_input;
    }

    sf::FloatRect EditableText::getBounds() const
    {
        return getGlobalBounds();
    }

    void EditableText::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
            && !getBounds().contains(info::getMousePosition()) && isActive())
            || event.type == sf::Event::TextEntered && event.text.unicode == 27) {
            setActive(false);
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
            && getBounds().contains(info::getMousePosition()) && !isActive()) {
            setActive(true);
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
            if (event.text.unicode < 128 && event.text.unicode != 8) {
                char c = static_cast<char>(event.text.unicode);
                if (m_onlyNumbers && !std::isdigit(c) && c != '.' && c != ',' && c != '-' && c != ' ')
                    return;
                if (!m_allowNumbers && std::isdigit(c))
                    return;
                if (!m_allowLetters && std::isalpha(c))
                    return;
                if (!m_allowSpecialChars && !std::isalnum(c) && !((c == '.' || c == ',' || c == '-') && m_onlyNumbers))
                    return;
                if (m_maxLength > 0 && m_input.size() >= m_maxLength)
                    return;
                m_input.insert(m_cursorPosition, 1, c);
                m_cursorBlinkTimer = 0;
                m_cursorPosition++;
            }
            std::string str = m_oldInput;
            setString(m_input);
            m_oldInput = str;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && isActive()) {
            validateInput();
            setActive(false);
        }
    }
}