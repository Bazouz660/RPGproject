/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-09 00:48:02
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-24 19:15:47
 * @ Description:
 */

#include "EditableTextList.hpp"
#include "math.hpp"

namespace bya::ui {

    void EditableTextList::anyEventHandler(sf::Event& event)
    {

    }

    void EditableTextList::setPosition(const sf::Vector2f &pos)
    {
        m_position = pos;

        for (int i = 0; i < m_children.size(); i++) {
            auto& text = m_children[i];
            if (i > 0) {
                auto& prevText = m_children[i - 1];
                auto prevBounds = prevText.handle->getBounds();
                if (m_axis == HORIZONTAL) {
                    text.handle->setPosition(sf::Vector2f(prevBounds.left + prevBounds.width, m_position.y));
                } else {
                    text.handle->setPosition(sf::Vector2f(m_position.x, prevBounds.top + prevBounds.height));
                }
            } else {
                text.handle->setPosition(m_position);
            }
        }
    }

    sf::FloatRect EditableTextList::getBounds() const
    {
        return getChildsBounds();
    }

    void EditableTextList::render(sf::RenderTarget &target)
    {
        setPosition(m_position);
        for (auto& text : m_children) {
            text.handle->render(target);
        }
    }

}
