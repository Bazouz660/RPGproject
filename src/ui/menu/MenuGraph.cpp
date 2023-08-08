/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-08-08 02:12:36
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-08-08 02:31:22
 * @ Description:
 */

#include "MenuGraph.hpp"

namespace bya::ui {

    void MenuGraph::setPosition(const sf::Vector2f& pos)
    {
        for (auto& [id, menu] : m_menus)
            menu->setPosition(pos);
    }

    sf::FloatRect MenuGraph::getBounds() const
    {
        if (m_current == nullptr)
            return math::NULL_RECT;
        return m_current->getBounds();
    }

    void MenuGraph::render(sf::RenderTarget& target)
    {
        if (m_current != nullptr)
            m_current->render(target);
    }

    void MenuGraph::add(const std::string &id, std::shared_ptr<Menu> menu)
    {
        m_menus[id] = menu;
        if (m_current == nullptr)
            setCurrent(menu);
    }

    void MenuGraph::remove(const std::string &id)
    {
        m_menus.erase(id);
    }

    void MenuGraph::remove(const std::shared_ptr<Menu> &menu)
    {
        for (auto it = m_menus.begin(); it != m_menus.end(); ++it)
            if (it->second == menu) {
                m_menus.erase(it);
                break;
            }
    }

    void MenuGraph::setCurrent(const std::string &id)
    {
        m_current = m_menus[id];
        m_children.set("current", m_current);
    }

    void MenuGraph::setCurrent(const std::shared_ptr<Menu> &menu)
    {
        m_current = menu;
        m_children.set("current", m_current);
    }

    std::shared_ptr<Menu> MenuGraph::getCurrent() const
    {
        return m_current;
    }

}