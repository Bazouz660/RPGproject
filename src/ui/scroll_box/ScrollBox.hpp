/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-15 16:43:40
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-15 17:34:05
 * @ Description:
 */

#ifndef SCROLLBOX_HPP
    #define SCROLLBOX_HPP

#include "common.hpp"
#include "AUIelement.hpp"

namespace bya::ui {

    // class to store multiple UIelements of the same type in a scrollable box
    template <typename T>
    class ScrollBox : public AUIelement {
        public:
            ScrollBox();
            virtual ~ScrollBox() = default;

            virtual void update(float dt) override;
            virtual void handleEvent(sf::Event event, const sf::RenderWindow &window) override;
            virtual void render(sf::RenderTarget &target) override;
            virtual void setPosition(const sf::Vector2f &pos) override;

            void addElement(std::shared_ptr<T> element);
            void removeElement(std::shared_ptr<T> element) { m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), element), m_elements.end()); }

            void clear() { m_elements.clear(); }

            std::vector<T> getElements() const { return m_elements; }

            sf::FloatRect getBounds() const { return m_background.getGlobalBounds(); }

        private:
            sf::Vector2f m_position = {0.f, 0.f};
            std::vector<std::pair<std::shared_ptr<T>, bool>> m_elements;
            std::shared_ptr<T> m_selectedElement = nullptr;
            sf::RectangleShape m_background;
    };
}

#include "ScrollBox.cpp"

#endif /* !SCROLLBOX_HPP */
