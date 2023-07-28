/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-26 00:26:37
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-28 02:38:05
 * @ Description:
 */

#include "DropDownButton.hpp"
#include "Button.hpp"

namespace bya::ui {

    DropDownButton::DropDownButton()
    {
        setSize({100, 20});
        setLabel("No options");

        Button::setCallback([this]() {
            m_isOpen = !m_isOpen;
        });
    }

    void DropDownButton::render(sf::RenderTarget& target)
    {
        Button::render(target);

        if (m_isOpen) {
            for (auto& child : m_children) {
                child.handle->render(target);
            }
        }
    }

    void DropDownButton::setPosition(const sf::Vector2f& pos)
    {
        Button::setPosition(pos);

        int i = 0;
        for (auto& child : m_children) {
            i++;
            child.handle->setPosition({pos.x, pos.y + (getSize().y * i)});
        }
    }

    void DropDownButton::setCharacterSize(unsigned int size)
    {
        Button::getLabel().setCharacterSize(size);
        for (auto& child : m_children) {
            dynamic_cast<Button*>(child.handle.get())->getLabel().setCharacterSize(size);
        }
    }

    void DropDownButton::addOption(const std::string& option)
    {
        // if a button with the same label already exists, don't add it
        for (auto& child : m_children) {
            if (dynamic_cast<Button*>(child.handle.get())->getLabel().getString() == option) {
                return;
            }
        }

        // add the button
        addChild(std::make_shared<Button>());
        Button* button = dynamic_cast<Button*>(m_children.back().handle.get());

        // if its the first option, set the label to the option
        if (m_children.size() == 1) {
            setLabel(option);
        }

        button->setSize(getSize());
        button->getLabel().setCharacterSize(getLabel().getCharacterSize());
        button->setLabel(option);
        button->setCallback([this, button]() {
            setLabel(button->getLabel().getString());
            m_isOpen = false;
        });
        button->setPosition({getPosition().x, getPosition().y + (getSize().y * m_children.size())});
    }

    void DropDownButton::removeOption(const std::string& option)
    {
        for (auto& child : m_children) {
            if (dynamic_cast<Button*>(child.handle.get())->getLabel().getString() == option) {
                removeChild(child.handle);
                return;
            }
        }
        if (m_children.empty()) {
            setLabel("No options");
        }
    }

    void DropDownButton::setSize(const sf::Vector2f& size)
    {
        Button::setSize(size);
        for (auto& child : m_children) {
            dynamic_cast<Button*>(child.handle.get())->setSize(size);
        }
    }

    sf::FloatRect DropDownButton::getBounds() const
    {
        sf::FloatRect bounds = Button::getBounds();
        if (m_isOpen) {
            for (auto& child : m_children) {
                bounds.height += child.handle->getBounds().height;
            }
        }
        return bounds;
    }
}