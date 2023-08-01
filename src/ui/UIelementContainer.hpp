/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-12 03:29:58
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-27 01:55:50
 *  Description:
 */

#pragma once

#include "AUIelement.hpp"

// change this to inherit from AUIelement

namespace bya::ui {

    class UIelementContainer : public AUIelement {
        public:
            virtual void setPosition(const sf::Vector2f& pos) override {};
            virtual sf::FloatRect getBounds() const override { return m_children.getBounds(); }
            virtual void render(sf::RenderTarget& target) override { m_children.render(target); }

            // public children methods
                template<typename T>
                std::shared_ptr<T> get(const std::string &id)
                {
                    return m_children.get<T>(id);
                }

                template<typename T>
                std::shared_ptr<T> get(unsigned int index)
                {
                    return m_children.get<T>(index);
                }

                std::size_t size() const { return m_children.size(); }

                bool empty() const { return m_children.empty(); }

                void set(const std::string &id, std::shared_ptr<ui::IUIelement> element)
                {
                    m_children.set(id, element);
                }

                void add(const std::string &id, std::shared_ptr<ui::IUIelement> element)
                {
                    m_children.add(id, element);
                }

                void remove(const std::string &id)
                {
                    m_children.remove(id);
                }

                void remove(const std::shared_ptr<ui::IUIelement> &element)
                {
                    m_children.remove(element);
                }

                void disable(const std::string &id)
                {
                    m_children.disable(id);
                }

                void enable(const std::string &id)
                {
                    m_children.enable(id);
                }

                void toggle(const std::string &id)
                {
                    m_children.toggle(id);
                }

                bool isEnabled(const std::string &id) const
                {
                    return m_children.isEnabled(id);
                }

                void setInterceptParentEvent(const std::string &id, bool interceptParentEvent)
                {
                    m_children.setInterceptParentEvent(id, interceptParentEvent);
                }

                void setOrder(const std::vector<std::string> &order)
                {
                    m_children.setOrder(order);
                }

                // iterator stuff
                std::vector<std::pair<std::string, Element>>::iterator begin() { return m_children.begin(); }
                std::vector<std::pair<std::string, Element>>::iterator end() { return m_children.end(); }
                std::vector<std::pair<std::string, Element>>::const_iterator begin() const { return m_children.begin(); }
                std::vector<std::pair<std::string, Element>>::const_iterator end() const { return m_children.end(); }
                std::vector<std::pair<std::string, Element>>::const_iterator cbegin() const { return m_children.cbegin(); }
                std::vector<std::pair<std::string, Element>>::const_iterator cend() const { return m_children.cend(); }

    };

}