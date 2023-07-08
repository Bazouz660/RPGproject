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
#include "logger.hpp"

namespace bya {

        void AnimationEditor::init()
        {
            sf::Vector2f wSize = sf::Vector2f(info::getWindowSize());

            addUIelement("LoadModelInputBox", std::make_shared<ui::InputBox>());
            addUIelement("LoadModelButton", std::make_shared<ui::Button>());

            auto inputBox = getUIelement<ui::InputBox>("LoadModelInputBox");
            sf::FloatRect inputBoxBounds = inputBox->getBounds();
            inputBox->setPosition({wSize.x / 2, wSize.y / 2});
            inputBox->setLabel("File name");
            inputBox->getApplyButton()->setCallback([this, inputBox]() {
                try {
                    m_entity.loadFromJson(inputBox->getInput());
                    sf::Vector2f pos = sf::Vector2f(info::getWindowSize());
                    m_entity.setPosition({pos.x / 4, pos.y / 2});
                    auto inputBox = getUIelement<ui::InputBox>("LoadModelInputBox");
                    inputBox->setOpen(false);
                } catch (std::exception &e) {
                    logger::error(e.what());
                }
            });

            auto loadModelButton = getUIelement<ui::Button>("LoadModelButton");
            loadModelButton->setLabel("Load from json");
            loadModelButton->setPosition({wSize.x - 200, 0});
            sf::FloatRect bounds = loadModelButton->getBounds();
            loadModelButton->setPosition({wSize.x - bounds.width / 2, bounds.height / 2});
            loadModelButton->setCallback([this]() {
                auto loadModelInputBox = getUIelement<ui::InputBox>("LoadModelInputBox");
                loadModelInputBox->setOpen(!loadModelInputBox->isOpen());
                if (loadModelInputBox->isOpen())
                    loadModelInputBox->setActive(true);
            });
        }

        void AnimationEditor::handleEvent(sf::Event &event, sf::RenderWindow &window)
        {
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