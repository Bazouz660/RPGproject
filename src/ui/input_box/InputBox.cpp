/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-07 15:20:09
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-07 15:33:25
 *  Description:
 */

#include "InputBox.hpp"

namespace bya::ui {

    InputBox::InputBox(const sf::Texture& texture, const std::string& label)
    {
        m_label.setString(label);
        m_label.setFont(getResource().getFont("gameFont"));
        m_label.setOrigin(m_label.getGlobalBounds().width / 2, m_label.getGlobalBounds().height / 2);
        m_label.setPosition(getPosition());
        m_label.setFillColor(sf::Color(30, 30, 30, 255));

        m_background.setFillColor(sf::Color::White);
        m_background.setSize(sf::Vector2f(400, 300));
        m_background.setOrigin(m_background.getGlobalBounds().width / 2, m_background.getGlobalBounds().height / 2);
        m_background.setPosition(getPosition());
    }

    void InputBox::setCallback(std::function<void(void)> func)
    {
        m_callback = func;
    }

    void InputBox::setLabel(const std::string& label)
    {
        m_label.setString(label);
        m_label.setOrigin(m_label.getGlobalBounds().width / 2, m_label.getGlobalBounds().height / 2);
    }

    void InputBox::handleEvent(sf::Event event, const sf::RenderWindow& window)
    {

    }

    void InputBox::setPosition(const sf::Vector2f& pos)
    {
        m_background.setPosition(pos);
        m_label.setPosition(pos + sf::Vector2f(0, -m_background.getGlobalBounds().height / 2 + 20));
    }

    sf::FloatRect InputBox::getBounds() const
    {
        return m_background.getGlobalBounds();
    }

    void InputBox::render(sf::RenderTarget& target)
    {
        target.draw(m_background);
        target.draw(m_label);
    }

}