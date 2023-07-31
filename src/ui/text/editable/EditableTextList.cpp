/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-09 00:48:02
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-31 18:42:08
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
            auto text = m_children.get<EditableText>(i);
            if (i > 0) {
                auto prevText = m_children.get<EditableText>(i - 1);
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
        return m_children.getBounds();
    }

    void EditableTextList::render(sf::RenderTarget &target)
    {
        setPosition(m_position);
        m_children.render(target);
    }

}
