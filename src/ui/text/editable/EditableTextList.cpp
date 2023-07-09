/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-09 00:48:02
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-09 01:32:56
 * @ Description:
 */

#include "EditableTextList.hpp"

namespace bya::ui {

    void EditableTextList::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        for (auto& text : m_texts) {
            text->handleEvent(event, window);
        }
    }

    void EditableTextList::update(float dt)
    {
        for (auto& text : m_texts) {
            text->update(dt);
        }
    }

    void EditableTextList::setPosition(const sf::Vector2f &pos)
    {
        m_position = pos;

        for (int i = 0; i < m_texts.size(); i++) {
            auto& text = m_texts[i];
            if (i > 0) {
                auto& prevText = m_texts[i - 1];
                auto prevBounds = prevText->getBounds();
                if (m_axis == HORIZONTAL) {
                    text->setPosition(sf::Vector2f(prevBounds.left + prevBounds.width, m_position.y));
                } else {
                    text->setPosition(sf::Vector2f(m_position.x, prevBounds.top + prevBounds.height));
                }
            } else {
                text->setPosition(m_position);
            }
        }
    }

    sf::FloatRect EditableTextList::getBounds() const
    {
        float left = 0;
        float top = 0;
        float width = 0;
        float height = 0;

        for (auto& text : m_texts) {
            auto bounds = text->getBounds();
            left = std::max(left, bounds.left);
            top = std::max(top, bounds.top);
            width = std::max(width, bounds.width);
            height = std::max(height, bounds.height);
        }

        return sf::FloatRect(left, top, width, height);
    }

    void EditableTextList::render(sf::RenderTarget &target)
    {
        setPosition(m_position);
        for (auto& text : m_texts) {
            text->render(target);
        }
    }

}
