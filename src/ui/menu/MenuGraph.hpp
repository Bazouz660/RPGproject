/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-08-07 22:03:07
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-08-08 02:34:48
 * @ Description:
 */

#pragma once

#include "Menu.hpp"

namespace bya::ui {

    class MenuGraph : public AUIelement {
        public:
            MenuGraph() = default;
            ~MenuGraph() = default;

            void setPosition(const sf::Vector2f& pos) override;
            sf::FloatRect getBounds() const override;
            void render(sf::RenderTarget& target) override;

            void add(const std::string &id, std::shared_ptr<Menu> menu);
            void remove(const std::string &id);
            void remove(const std::shared_ptr<Menu> &menu);

            std::shared_ptr<Menu> get(const std::string &id) const { return m_menus.at(id); }

            void setCurrent(const std::string &id);
            void setCurrent(const std::shared_ptr<Menu> &menu);

            std::shared_ptr<Menu> getCurrent() const;
        private:
            std::shared_ptr<Menu> m_current = nullptr;
            std::map<std::string, std::shared_ptr<Menu>> m_menus;
    };

}