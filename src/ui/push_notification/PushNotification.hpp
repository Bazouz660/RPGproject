/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 17:18:40
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-08 17:25:35
 * @ Description:
 */

#pragma once

#include "AUIelement.hpp"
#include <queue>

namespace bya::ui {
    class PushNotification : public AUIelement {
        public:
            PushNotification() = default;

            virtual void handleEvent(sf::Event event, const sf::RenderWindow &window) override;
            virtual void setPosition(const sf::Vector2f &pos) override;
            virtual void render(sf::RenderTarget &target) override;

            virtual void pushMessage(const std::string& message);

        protected:
            std::queue<sf::Text> m_messages;
    };
}