/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-31 17:38:37
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-31 17:52:11
 * @ Description:
 */

#include "UIelementContainer.hpp"

namespace bya::ui {

    class Menu : public AUIelement {
        public:
            Menu();
            virtual ~Menu() = default;

            virtual void setPosition(const sf::Vector2f& pos) override;
            virtual sf::FloatRect getBounds() const override;

            virtual void render(sf::RenderTarget& target) override;

        protected:
            virtual void hoverEventHandler(sf::Event& event) override;
            virtual void anyEventHandler(sf::Event& event) override;

        protected:
    };

}