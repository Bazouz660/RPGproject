/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-15 16:43:40
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-24 18:52:09
 * @ Description:
 */

#ifndef SCROLLBOX_HPP
    #define SCROLLBOX_HPP

#include "common.hpp"
#include "AUIelement.hpp"
#include "Text.hpp"

namespace bya::ui {

    // class to store multiple UIelements of the same type in a scrollable box
    template <typename T>
    class ScrollBox : public AUIelement {
        public:
            ScrollBox();
            virtual ~ScrollBox() = default;

            virtual void render(sf::RenderTarget &target) override;
            virtual void setPosition(const sf::Vector2f &pos) override;

            void setSelectedElement(std::shared_ptr<T> element);
            std::shared_ptr<T> getSelectedElement() const { return m_selectedElement; }

            void addElement(std::shared_ptr<T> element);
            void removeElement(std::shared_ptr<T> element) { m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), element), m_elements.end()); }

            void clear() { m_elements.clear(); m_selectedElement = nullptr; }

            std::vector<std::shared_ptr<T>>& getElements() { return m_elements; }

            sf::FloatRect getBounds() const;

        private:
            int getSelectedIndex() const;
            bool isFirstElementSelected() const { return m_selectedElement == m_elements.front(); }
            bool isLastElementSelected() const { return m_selectedElement == m_elements.back(); }

        protected:
            virtual void hoverEventHandler(sf::Event &event) override;

        private:
            sf::Vector2f m_position = {0.f, 0.f};
            std::vector<std::shared_ptr<T>> m_elements;
            std::shared_ptr<T> m_selectedElement = nullptr;
            sf::RectangleShape m_background;
            sf::ConvexShape m_arrowUp;
            sf::ConvexShape m_arrowDown;
            Text m_indexText;
    };
}

#include "ScrollBox.cpp"

#endif /* !SCROLLBOX_HPP */
