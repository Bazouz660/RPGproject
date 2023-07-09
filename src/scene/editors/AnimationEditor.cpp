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
#include "PushNotification.hpp"
#include "EditableText.hpp"
#include "EditableTextList.hpp"
#include "logger.hpp"
#include "parsing.hpp"

namespace bya {

        void AnimationEditor::init()
        {
            sf::Vector2f wSize = sf::Vector2f(info::getWindowSize());

            addUIelement("LoadModelInputBox", std::make_shared<ui::InputBox>());
            addUIelement("LoadModelButton", std::make_shared<ui::Button>());
            addUIelement("LoadNotification", std::make_shared<ui::PushNotification>());

            addUIelement("PartName", std::make_shared<ui::EditableText>("", 24));
            addUIelement("PartPosition", std::make_shared<ui::EditableTextList>());
            addUIelement("PartSize", std::make_shared<ui::EditableTextList>());
            addUIelement("PartRotation", std::make_shared<ui::EditableText>("", 24));
            addUIelement("PartPivot", std::make_shared<ui::EditableTextList>());
            addUIelement("PartParent", std::make_shared<ui::EditableText>("", 24));
            addUIelement("PartZIndex", std::make_shared<ui::EditableText>("", 24));

            {
                auto posList = getUIelement<ui::EditableTextList>("PartPosition");
                posList->addText(std::make_shared<ui::EditableText>("0", 24));
                posList->addText(std::make_shared<ui::EditableText>("0", 24));
                posList->getText(0)->setPrefix("Position: x[");
                posList->getText(0)->setSuffix("]");
                posList->getText(1)->setPrefix(" y[");
                posList->getText(1)->setSuffix("]");
                posList->getText(0)->onlyNumbers(true);
                posList->getText(1)->onlyNumbers(true);

                auto sizeList = getUIelement<ui::EditableTextList>("PartSize");
                sizeList->addText(std::make_shared<ui::EditableText>("0", 24));
                sizeList->addText(std::make_shared<ui::EditableText>("0", 24));
                sizeList->getText(0)->setPrefix("Size: x[");
                sizeList->getText(0)->setSuffix("]");
                sizeList->getText(1)->setPrefix(" y[");
                sizeList->getText(1)->setSuffix("]");
                sizeList->getText(0)->onlyNumbers(true);
                sizeList->getText(1)->onlyNumbers(true);

                auto pivotList = getUIelement<ui::EditableTextList>("PartPivot");
                pivotList->addText(std::make_shared<ui::EditableText>("0", 24));
                pivotList->addText(std::make_shared<ui::EditableText>("0", 24));
                pivotList->getText(0)->setPrefix("Pivot: x[");
                pivotList->getText(0)->setSuffix("]");
                pivotList->getText(1)->setPrefix(" y[");
                pivotList->getText(1)->setSuffix("]");
                pivotList->getText(0)->onlyNumbers(true);
                pivotList->getText(1)->onlyNumbers(true);

                float offset = 0.6f;
                getUIelement<ui::EditableText>("PartName")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableTextList>("PartPosition")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableTextList>("PartSize")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableText>("PartRotation")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableTextList>("PartPivot")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableText>("PartParent")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableText>("PartZIndex")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});

                // add prefix
                getUIelement<ui::EditableText>("PartName")->setPrefix("Name: ");
                getUIelement<ui::EditableText>("PartRotation")->setPrefix("Rotation: ");
                getUIelement<ui::EditableText>("PartParent")->setPrefix("Parent: ");
                getUIelement<ui::EditableText>("PartZIndex")->setPrefix("Z-index: ");

                getUIelement<ui::EditableText>("PartRotation")->onlyNumbers(true);
                getUIelement<ui::EditableText>("PartZIndex")->onlyNumbers(true);
            }

            auto inputBox = getUIelement<ui::InputBox>("LoadModelInputBox");
            sf::FloatRect inputBoxBounds = inputBox->getBounds();
            inputBox->setPosition({wSize.x / 2, wSize.y / 2});
            inputBox->setLabel("File name");
            inputBox->getApplyButton()->setCallback([this, inputBox]() {
                if (inputBox->getInput().empty())
                    return;
                try {
                    if (m_entity == nullptr)
                        m_entity = std::make_shared<gameObj::PartEntity>();
                    m_entity->loadFromJson(inputBox->getInput());
                    logger::log("Model: " + inputBox->getInput() + " loaded successfully");
                    sf::Vector2f pos = sf::Vector2f(info::getWindowSize());
                    m_entity->setPosition({pos.x / 4, pos.y / 2});
                    auto inputBox = getUIelement<ui::InputBox>("LoadModelInputBox");
                    inputBox->setOpen(false);
                    auto loadNotification = getUIelement<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage("Model loaded successfully", sf::Color::Green);
                } catch (std::exception &e) {
                    auto loadNotification = getUIelement<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage(e.what());
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

            auto loadNotification = getUIelement<ui::PushNotification>("LoadNotification");
            loadNotification->setPosition(sf::Vector2f(wSize.x / 2, wSize.y * 0.2));
            loadNotification->setDuration(3);
            loadNotification->setColor(sf::Color::Red);
            loadNotification->setMaxMessages(3);
            loadNotification->setFontSize(20);

            m_partInfoBackground.setSize(sf::Vector2f(300, wSize.y));
            m_partInfoBackground.setOrigin(m_partInfoBackground.getSize() / 2.f);
            m_partInfoBackground.setPosition(wSize.x - m_partInfoBackground.getSize().x / 2.f, wSize.y / 2.f);
            m_partInfoBackground.setFillColor(sf::Color(50, 50, 50, 255));
            m_partInfoBackground.setOutlineColor(sf::Color::Black);
            m_partInfoBackground.setOutlineThickness(5);
        }

        bool AnimationEditor::isHoveringUI()
        {
            sf::Vector2f mousePos = info::getMousePosition();

            for (auto &element : m_UIelements) {
                if (element.second->getBounds().contains(mousePos))
                    return true;
            }
            return false;
        }

        void AnimationEditor::setPartInfo()
        {
            if (m_selectedPart == nullptr)
                return;

            getUIelement<ui::EditableText>("PartName")->setString(m_selectedPart->getName());
            getUIelement<ui::EditableText>("PartRotation")->setString(parsing::floatToString(m_selectedPart->getRotation()));

            auto posList = getUIelement<ui::EditableTextList>("PartPosition");
            posList->getText(0)->setString(parsing::floatToString(m_selectedPart->getPosition().x - m_entity->getPosition().x));
            posList->getText(1)->setString(parsing::floatToString(m_selectedPart->getPosition().y - m_entity->getPosition().y));

            auto sizeList = getUIelement<ui::EditableTextList>("PartSize");
            sizeList->getText(0)->setString(parsing::floatToString(m_selectedPart->getSize().x));
            sizeList->getText(1)->setString(parsing::floatToString(m_selectedPart->getSize().y));

            auto pivotList = getUIelement<ui::EditableTextList>("PartPivot");
            pivotList->getText(0)->setString(parsing::floatToString(m_selectedPart->getPivotPoint().x));
            pivotList->getText(1)->setString(parsing::floatToString(m_selectedPart->getPivotPoint().y));

            auto partParent = getUIelement<ui::EditableText>("PartParent");
            auto parent = m_selectedPart->getParent();
            if (parent)
                partParent->setString(parent->getName());
            else
                partParent->setString("None");

            getUIelement<ui::EditableText>("PartZIndex")->setString(std::to_string(m_selectedPart->getZIndex()));
        }

        void AnimationEditor::handleEvent(sf::Event &event, sf::RenderWindow &window)
        {
            if (m_entity != nullptr) {
                auto& parts = m_entity->getSortedZParts();
                gameObj::IMultPartEntity* lastFound = nullptr;
                for (auto& part : parts) {
                    if (part != m_selectedPart)
                        part->setTint(sf::Color::White);
                    if (part->isHovered() && !isHoveringUI()) {
                        lastFound = part;
                        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                            m_selectedPart = part;
                            setPartInfo();
                        }
                    }
                }
                if (lastFound)
                    lastFound->setTint(sf::Color::Green);
                if (m_selectedPart)
                    m_selectedPart->setTint(sf::Color::Yellow);
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && m_selectedPart) {
                sf::Vector2f pos = sf::Vector2f(std::atof(getUIelement<ui::EditableTextList>("PartPosition")->getText(0)->getInput().c_str()),
                                    std::atof(getUIelement<ui::EditableTextList>("PartPosition")->getText(1)->getInput().c_str()));
                sf::Vector2f size = sf::Vector2f(std::atof(getUIelement<ui::EditableTextList>("PartSize")->getText(0)->getInput().c_str()),
                                    std::atof(getUIelement<ui::EditableTextList>("PartSize")->getText(1)->getInput().c_str()));
                sf::Vector2f pivot = sf::Vector2f(std::atof(getUIelement<ui::EditableTextList>("PartPivot")->getText(0)->getInput().c_str()),
                                    std::atof(getUIelement<ui::EditableTextList>("PartPivot")->getText(1)->getInput().c_str()));
                float rotation = std::atof(getUIelement<ui::EditableText>("PartRotation")->getInput().c_str());
                int zIndex = std::atoi(getUIelement<ui::EditableText>("PartZIndex")->getInput().c_str());

                m_selectedPart->setPosition(pos + m_entity->getPosition());
                m_selectedPart->setSize(size);
                m_selectedPart->setPivotPoint(pivot);
                m_selectedPart->setFixedRotation(rotation);
                m_selectedPart->setZIndex(zIndex);
                m_entity->sortZIndex();
            }
        }

        void AnimationEditor::update(float dt)
        {
        }

        void AnimationEditor::render(sf::RenderTarget &target)
        {
            target.draw(m_partInfoBackground);
            AScene::renderUi(target);

            if (m_entity)
                m_entity->render(target, true);
        }
}