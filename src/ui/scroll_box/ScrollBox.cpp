/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-15 16:48:05
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-24 19:37:23
 * @ Description:
 */

#include "ScrollBox.hpp"
#include "context.hpp"
#include "math.hpp"

#ifndef SCROLLBOX_CPP
    #define SCROLLBOX_CPP

namespace bya::ui {

    template<typename T>
    ScrollBox<T>::ScrollBox()
    {
        m_background.setFillColor(sf::Color::Transparent);
        m_background.setOutlineColor(sf::Color::White);
        m_background.setOutlineThickness(2.f);

        m_arrowUp.setPointCount(3);
        m_arrowUp.setPoint(0, {0.f, 0.f});
        m_arrowUp.setPoint(1, {1.f, 2.f});
        m_arrowUp.setPoint(2, {2.f, 0.f});
        m_arrowUp.setFillColor(sf::Color(85, 85, 85, 255));
        m_arrowUp.setOrigin(1.f, 1.f);
        m_arrowUp.setScale(5.f, 5.f);

        m_arrowDown = m_arrowUp;
        m_arrowDown.setRotation(180.f);

        m_indexText.setString("0/0");
        m_indexText.setCharacterSize(20);

        addChild(m_selectedElement);
    }

    template<typename T>
    void ScrollBox<T>::setSelectedElement(std::shared_ptr<T> element)
    {
        if (std::find_if(m_elements.begin(), m_elements.end(), [element](const auto &pair) {
            return pair == element;
        }) == m_elements.end()) {
            throw std::runtime_error("ScrollBox::setSelectedElement: element not found");
        }
        m_selectedElement = element;
        m_children[0].handle = m_selectedElement;
    }

    template<typename T>
    void ScrollBox<T>::setPosition(const sf::Vector2f &pos)
    {
        m_position = pos;
    }

    template<typename T>
    int ScrollBox<T>::getSelectedIndex() const
    {
        auto it = std::find_if(m_elements.begin(), m_elements.end(), [this](const auto &element) {
            return element == m_selectedElement;
        });
        if (it != m_elements.end()) {
            return it - m_elements.begin();
        }
        return -1;
    }

    template<typename T>
    void ScrollBox<T>::addElement(std::shared_ptr<T> element)
    {
        m_elements.push_back(element);

        if (m_selectedElement == nullptr) {
            m_selectedElement = element;
            m_children[0].handle = m_selectedElement;
        }
    }

    template<typename T>
    void ScrollBox<T>::hoverEventHandler(sf::Event& event)
    {
        if (m_background.getGlobalBounds().contains(context::getMousePosition())) {
            if (event.type == sf::Event::MouseWheelScrolled) {
                int index = getSelectedIndex();
                if (event.mouseWheelScroll.delta > 0) {
                    if (index > 0) {
                        m_selectedElement = m_elements[index - 1];
                        m_children[0].handle = m_selectedElement;
                    }
                }
                else {
                    if (index < m_elements.size() - 1) {
                        m_selectedElement = m_elements[index + 1];
                        m_children[0].handle = m_selectedElement;
                    }
                }
            }
        }
    }

    template<typename T>
    void ScrollBox<T>::render(sf::RenderTarget &target)
    {
        if (m_selectedElement != nullptr) {
            m_selectedElement->setPosition(m_position);
            sf::FloatRect bounds = m_selectedElement->getBounds();
            m_background.setSize({bounds.width + 5, bounds.height + 5});
            m_background.setPosition(bounds.left - 2.5f, bounds.top - 2.5f);
            target.draw(m_background);

            if (isFirstElementSelected())
                m_arrowUp.setFillColor(sf::Color(85, 85, 85, 255));
            else
                m_arrowUp.setFillColor(sf::Color::White);
            if (isLastElementSelected())
                m_arrowDown.setFillColor(sf::Color(85, 85, 85, 255));
            else
                m_arrowDown.setFillColor(sf::Color::White);


            m_arrowUp.setPosition(bounds.left + bounds.width + 10.f, (bounds.top + bounds.height * 0.5f) + 10.f);
            target.draw(m_arrowUp);
            m_arrowDown.setPosition(bounds.left + bounds.width + 10.f, (bounds.top + bounds.height * 0.5f - 10.f));
            target.draw(m_arrowDown);

            m_indexText.setString({std::to_string(getSelectedIndex() + 1) + "/" + std::to_string(m_elements.size())});
            m_indexText.setOrigin(0, m_indexText.getBounds().height * 0.5f);
            m_indexText.setPosition({bounds.left + bounds.width + m_arrowDown.getGlobalBounds().width * 2, bounds.top + bounds.height * 0.5f});
            target.draw(m_indexText);

            m_selectedElement->render(target);
        }
    }

    template<typename T>
    sf::FloatRect ScrollBox<T>::getBounds() const
    {
        if (m_selectedElement != nullptr) {
            sf::FloatRect bounds = m_selectedElement->getBounds();
            bounds.width += m_arrowDown.getGlobalBounds().width * 2 + m_indexText.getBounds().width;
            return bounds;
        } else {
            return math::NULL_RECT;
        }
    }
}

#endif /* !SCROLLBOX_CPP */