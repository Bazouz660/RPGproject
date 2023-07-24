/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 17:18:40
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-23 17:38:40
 * @ Description:
 */

#pragma once

#include "AUIelement.hpp"
#include <vector>

namespace bya::ui {
    class PushNotification : public AUIelement {
        public:
            PushNotification() = default;

            virtual void setPosition(const sf::Vector2f &pos) override;
            virtual void render(sf::RenderTarget &target) override;

            virtual void pushMessage(const std::string& message);
            virtual void pushMessage(const std::string& message, sf::Color color);

            virtual void allowDuplicatesInQueue(bool allow) { m_allowDuplicatesInQueue = allow; }
            virtual bool isDuplicatesInQueueAllowed() const { return m_allowDuplicatesInQueue; }

            virtual void setDuration(float duration);
            virtual void setMaxMessages(unsigned int maxMessages);
            virtual void setColor(const sf::Color& color);
            virtual void setFontSize(unsigned int size) { m_fontSize = size; }

            virtual float getDuration() const { return m_messageDuration; }
            virtual unsigned int getMaxMessages() const { return m_maxMessages; }
            virtual sf::Color getColor() const { return m_color; }
            virtual sf::FloatRect getBounds() const override { return sf::FloatRect(); }

        protected:
            virtual void updateHandler(float dt) override;

        protected:
            std::vector<std::shared_ptr<sf::Text>> m_messages;
            sf::Vector2f m_position;
            sf::Color m_color = sf::Color::White;
            unsigned int m_maxMessages = 3;
            unsigned int m_fontSize = 24;
            float m_messageDuration = 3;
            float m_messageTimer = 0;
            bool m_allowDuplicatesInQueue = false;
    };
}