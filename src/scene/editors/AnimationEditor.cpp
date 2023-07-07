/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** AnimationEditor
*/

#include "AnimationEditor.hpp"
#include "info.hpp"
#include "Button.hpp"
#include "InputBox.hpp"

namespace bya {

        void AnimationEditor::init()
        {
            sf::Vector2f wSize = sf::Vector2f(info::getWindowSize());
            ui::Button button = ui::Button();

            button.setLabel("Load from json");
            button.setPosition({wSize.x - 200, 0});
            sf::FloatRect bounds = button.getBounds();
            button.setPosition({wSize.x - bounds.width / 2, bounds.height / 2});
            button.setCallback([this]() {
                m_entity.loadFromJson("humanoid.json");
                m_entity.setPosition(info::getMousePosition());
            });

            ui::InputBox inputBox = ui::InputBox();
            sf::FloatRect inputBoxBounds = inputBox.getBounds();
            inputBox.setPosition({wSize.x / 2, wSize.y / 2});
            inputBox.setLabel("File name");
            inputBox.setCallback([this]() {
            });

            addUIelement("LoadModelInputBox", std::make_shared<ui::InputBox>(inputBox));
            addUIelement("LoadModelButton", std::make_shared<ui::Button>(button));
        }

        void AnimationEditor::handleEvent(sf::Event &event, sf::RenderWindow &window)
        {
            AScene::handleEvent(event, window);
        }

        void AnimationEditor::update(float dt)
        {
            m_entity.update(dt);
        }

        void AnimationEditor::render(sf::RenderTarget &target)
        {
            AScene::renderUi(target);
            m_entity.render(target);
        }
}