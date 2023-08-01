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
        m_children.add("slider", std::make_shared<Slider>(Slider::Orientation::VERTICAL));
        m_slider = m_children.get<Slider>("slider");
        m_slider->setPosition({getPosition().x + 200.f, getPosition().y});

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
            m_slider->render(target);
            float progress = m_slider->getProgress(); // between 0 and 1

            // the offset is the starting index of the options to display if the slider is at 0.5, we want to display the options from the middle of the list
            unsigned int offset = (m_options.size() - m_maxDisplayedOptions) * progress;

            for (unsigned int i = offset; i < offset + m_maxDisplayedOptions; i++) {
                m_options[i]->setPosition({getPosition().x, getPosition().y + (getSize().y * (i - offset + 1))});
                m_options[i]->render(target);
            }
        }
    }

    void DropDownButton::setPosition(const sf::Vector2f& pos)
    {
        Button::setPosition(pos);

        int i = 0;
        for (auto& option : m_options) {
            i++;
            option->setPosition({pos.x, pos.y + (getSize().y * i)});
        }

        unsigned int posY = m_options.size() > m_maxDisplayedOptions ? m_maxDisplayedOptions : m_options.size();

        m_slider->setPosition({pos.x + (getSize().x * 0.5f) + (m_slider->getSize().y * 0.5f), pos.y + (getSize().y * 0.5f) + (getSize().y * posY * 0.5f)});
    }

    void DropDownButton::setCharacterSize(unsigned int size)
    {
        Button::getLabel().setCharacterSize(size);
        for (auto& option : m_options) {
            option->getLabel().setCharacterSize(size);
        }
    }

    void DropDownButton::addOption(const std::string& optionLabel)
    {
        // if a button with the same label already exists, don't add it
        for (auto& option : m_options) {
            if (option->getLabel().getString() == optionLabel) {
                return;
            }
        }

        // add the button
        m_children.add("button_" + optionLabel, std::make_shared<Button>());
        auto button = m_children.get<Button>("button_" + optionLabel);
        m_options.push_back(button);

        // if its the first option, set the label to the option
        if (m_options.size() == 1) {
            setLabel(optionLabel);
        }

        button->setSize(getSize());
        button->getLabel().setCharacterSize(getLabel().getCharacterSize());
        button->setLabel(optionLabel);
        button->setCallback([this, button]() {
            setLabel(button->getLabel().getString());
            m_isOpen = false;
            this->notify();
        });
        button->setPosition({getPosition().x, getPosition().y + (getSize().y * m_options.size())});

        // set slider size to fit all options, or maxDisplayedOptions
        if (m_options.size() > m_maxDisplayedOptions) {
            m_slider->setSize({getSize().y * m_maxDisplayedOptions, m_slider->getSize().y});
        } else {
            m_slider->setSize({getSize().y * m_options.size(), m_slider->getSize().y});
        }
    }

    void DropDownButton::removeOption(const std::string& optionLabel)
    {
        for (auto& option : m_options) {
            if (option->getLabel().getString() == optionLabel) {
                m_children.remove(option);
                m_options.erase(std::remove(m_options.begin(), m_options.end(), option), m_options.end());
                return;
            }
        }
        if (m_options.empty()) {
            setLabel("No options");
        }
    }

    void DropDownButton::setSize(const sf::Vector2f& size)
    {
        Button::setSize(size);
        for (auto& option : m_options) {
            option->setSize(size);
        }
        setPosition(getPosition());
    }

    sf::FloatRect DropDownButton::getBounds() const
    {
        sf::FloatRect bounds = Button::getBounds();
        if (m_isOpen) {
            bounds = math::combineRects(bounds, m_children.getBounds());
        }
        return bounds;
    }
}