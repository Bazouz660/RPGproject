/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-07 15:20:09
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-07 15:33:25
 *  Description:
 */

#include "InputBox.hpp"
#include "logger.hpp"
#include "info.hpp"
#include "Clock.hpp"

namespace bya::ui {

    InputBox::InputBox(const sf::Texture& texture, const std::string& label)
    : m_isActive(false)
    {
        m_label.setString(label);
        m_label.setFont(getResource().getFont("gameFont"));
        m_label.setOrigin(m_label.getGlobalBounds().width / 2, m_label.getGlobalBounds().height / 2);
        m_label.setPosition(getPosition() + sf::Vector2f(0, -m_background.getGlobalBounds().height / 2 + m_label.getCharacterSize()));

        m_background.setFillColor(sf::Color(100, 100, 100, 255));
        m_background.setSize(sf::Vector2f(400, 300));
        m_background.setOrigin(m_background.getGlobalBounds().width / 2, m_background.getGlobalBounds().height / 2);
        m_background.setPosition(getPosition());
        m_background.setOutlineColor(sf::Color(30, 30, 30, 255));
        m_background.setOutlineThickness(5);

        m_inputBox = std::make_shared<Button>();
        m_inputBox->getLabel().setCharacterSize(20);
        m_inputBox->setSize(sf::Vector2f(300, 50));
        m_inputBox->setPosition(getPosition() + sf::Vector2f(0, -m_background.getGlobalBounds().height / 2 + 100));
        m_inputBox->setCallback([this]() {
            if (m_inputBox->getLabel().getString() == "Enter text here...")
                m_inputBox->setLabel("");
            this->setActive(true);
        });

        m_applyButton = std::make_shared<Button>();
        m_applyButton->getLabel().setCharacterSize(20);
        m_applyButton->setLabel("Apply");
        m_applyButton->setSize(sf::Vector2f(100, 75));
        m_applyButton->setPosition(getPosition() + sf::Vector2f(m_background.getGlobalBounds().width / 2 - 100, m_background.getGlobalBounds().height / 2 - 100));
        m_applyButton->setCallback([this]() {
        });

        m_cancelButton = std::make_shared<Button>();
        m_cancelButton->getLabel().setCharacterSize(20);
        m_cancelButton->setLabel("Cancel");
        m_cancelButton->setSize(sf::Vector2f(100, 75));
        m_cancelButton->setPosition(getPosition() + sf::Vector2f(-m_background.getGlobalBounds().width / 2 + 100, m_background.getGlobalBounds().height / 2 - 100));
        m_cancelButton->setCallback([this]() {
            setActive(false);
            m_input = "";
            setOpen(false);
        });
    }

    void InputBox::setActive(bool active)
    {
        m_isActive = active;

        if (m_isActive) {
            m_inputBox->setLabel("");
        } else {
            m_inputBox->setLabel("Enter text here...");
        }
    }

    void InputBox::setLabel(const std::string& label)
    {
        m_label.setString(label);
        m_label.setOrigin(m_label.getGlobalBounds().width / 2, m_label.getGlobalBounds().height / 2);
    }

    bool InputBox::isInputContained() const
    {
        sf::FloatRect inputBounds = m_inputBox->getBounds();
        sf::FloatRect textBounds = m_inputBox->getLabel().getGlobalBounds();
        int charSize = m_inputBox->getLabel().getCharacterSize();

        return !(textBounds.left - charSize < inputBounds.left
            || textBounds.left + textBounds.width + charSize > inputBounds.left + inputBounds.width);
    }

    void InputBox::handleEvent(sf::Event event, const sf::RenderWindow& window)
    {
        if (!isOpen())
            return;

        m_inputBox->handleEvent(event, window);
        m_applyButton->handleEvent(event, window);
        m_cancelButton->handleEvent(event, window);

        if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
            && !m_inputBox->getBounds().contains(info::getMousePosition()))
            || event.type == sf::Event::TextEntered && event.text.unicode == 27) {
            setActive(false);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            m_applyButton->activate();
        }

        if (event.type == sf::Event::TextEntered && isActive() && event.text.unicode != 13) {
            if (event.text.unicode == 8 && m_input.size() > 0)
                m_input.pop_back();
            else if (event.text.unicode < 128 && event.text.unicode != 8
                && isInputContained()) {
                m_input += static_cast<char>(event.text.unicode);
            }
            m_inputBox->setLabel(m_input);
        }

        if (isActive()) {
            m_inputBox->setHovered();
        }
    }

    void InputBox::setPosition(const sf::Vector2f& pos)
    {
        m_background.setPosition(pos);
        m_label.setPosition(pos + sf::Vector2f(0, -m_background.getGlobalBounds().height / 2 + m_label.getCharacterSize()));
        m_inputBox->setPosition(pos + sf::Vector2f(0, -m_background.getGlobalBounds().height / 2 + 100));
        m_applyButton->setPosition(pos + sf::Vector2f(m_background.getGlobalBounds().width / 2 - 100, m_background.getGlobalBounds().height / 2 - 100));
        m_cancelButton->setPosition(pos + sf::Vector2f(-m_background.getGlobalBounds().width / 2 + 100, m_background.getGlobalBounds().height / 2 - 100));
    }

    sf::FloatRect InputBox::getBounds() const
    {
        return m_background.getGlobalBounds();
    }

    void InputBox::update(float dt)
    {
        if (!isOpen())
            return;

        if (getTime().asSeconds() > m_cursorBlinkTimer + 0.75 && isActive()) {
            m_cursorBlinkTimer = getTime().asSeconds();
            m_inputBox->setLabel(m_input + "|");
        } else if (getTime().asSeconds() > m_cursorBlinkTimer + 0.5 || (!isActive()
            && m_label.getString() != m_input)) {
            if (m_input.size() == 0 && !isActive())
                m_inputBox->setLabel("Enter text here...");
            else
                m_inputBox->setLabel(m_input);
        }
    }

    void InputBox::render(sf::RenderTarget& target)
    {
        if (!isOpen())
            return;

        target.draw(m_background);
        target.draw(m_label);
        m_inputBox->render(target);
        m_applyButton->render(target);
        m_cancelButton->render(target);
    }

}