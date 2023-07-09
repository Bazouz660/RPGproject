/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 17:18:46
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-10 00:36:20
 * @ Description:
 */

#include "PushNotification.hpp"
#include "ResourceManager.hpp"

namespace bya::ui {

    void PushNotification::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
    }

    void PushNotification::update(float dt)
    {
        m_messageTimer += dt;
        if (m_messageTimer >= m_messageDuration) {
            m_messageTimer = 0;
            if (m_messages.size() > 0) {
                m_messages.erase(m_messages.begin());
            }
        }
    }

    void PushNotification::setPosition(const sf::Vector2f &pos)
    {
        m_position = pos;
    }

    void PushNotification::render(sf::RenderTarget &target)
    {
        sf::Vector2f pos = m_position;

        // start loop from begin to maxMessages
        for (auto it = m_messages.begin(); it != m_messages.end() && it - m_messages.begin() < m_maxMessages; ++it) {
            auto& msg = *it;
            msg->setPosition(pos);
            target.draw(*msg);
            pos.y += msg->getGlobalBounds().height;
        }
    }

    void PushNotification::pushMessage(const std::string& message)
    {
        sf::Text text;
        text.setFont(getResource().getFont("gameFont"));
        text.setString(message);
        text.setFillColor(m_color);
        text.setCharacterSize(m_fontSize);
        text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);

        if (!m_allowDuplicatesInQueue && m_messages.size() >= m_maxMessages) {
            for (auto& msg : m_messages) {
                if (msg->getString() == message) {
                    return;
                }
            }
        }

        m_messages.push_back(std::make_shared<sf::Text>(text));
    }

    void PushNotification::pushMessage(const std::string& message, sf::Color color)
    {
        sf::Text text;
        text.setFont(getResource().getFont("gameFont"));
        text.setString(message);
        text.setFillColor(color);
        text.setCharacterSize(m_fontSize);
        text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
        m_messages.push_back(std::make_shared<sf::Text>(text));
    }

    void PushNotification::setDuration(float duration)
    {
        m_messageDuration = duration;
    }

    void PushNotification::setMaxMessages(unsigned int maxMessages)
    {
        m_maxMessages = maxMessages;
    }

    void PushNotification::setColor(const sf::Color& color)
    {
        m_color = color;
    }

}