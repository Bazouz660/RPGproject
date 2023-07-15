/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-15 16:48:05
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-15 17:34:51
 * @ Description:
 */

#include "ScrollBox.hpp"
#include "context.hpp"

#ifndef SCROLLBOX_CPP
    #define SCROLLBOX_CPP

namespace bya::ui {

    template<typename T>
    ScrollBox<T>::ScrollBox()
    {
        m_background.setFillColor(sf::Color::Transparent);
        m_background.setOutlineColor(sf::Color::White);
        m_background.setOutlineThickness(2.f);
    }

    template<typename T>
    void ScrollBox<T>::setPosition(const sf::Vector2f &pos)
    {
        m_position = pos;
    }

    template<typename T>
    void ScrollBox<T>::addElement(std::shared_ptr<T> element)
    {
        m_elements.emplace_back(element, false);

        if (m_selectedElement == nullptr) {
            m_selectedElement = element;
        }
    }

    template<typename T>
    void ScrollBox<T>::update(float dt)
    {
        if (m_selectedElement != nullptr) {
            m_selectedElement->update(dt);
        }
    }

    template<typename T>
    void ScrollBox<T>::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        if (m_selectedElement != nullptr) {
            m_selectedElement->handleEvent(event, window);
        }

        if (m_background.getGlobalBounds().contains(context::getMousePosition())) {
            if (event.type == sf::Event::MouseWheelScrolled) {
                // get selected element's position in the vector
                auto it = std::find_if(m_elements.begin(), m_elements.end(), [this](const auto &element) {
                    return element.first == m_selectedElement;
                });
                if (it != m_elements.end()) {
                    // scroll up
                    if (event.mouseWheelScroll.delta > 0) {
                        // if not at the top of the list
                        if (it != m_elements.begin()) {
                            // select the previous element
                            m_selectedElement = (it - 1)->first;
                        }
                    }
                    // scroll down
                    else if (event.mouseWheelScroll.delta < 0) {
                        // if not at the bottom of the list
                        if (it != m_elements.end() - 1) {
                            // select the next element
                            m_selectedElement = (it + 1)->first;
                        }
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
            m_background.setSize({bounds.width, bounds.height});
            m_background.setPosition(bounds.left, bounds.top);
            target.draw(m_background);
            m_selectedElement->render(target);
        }
    }
}

#endif /* !SCROLLBOX_CPP */