/*
** EPITECH PROJECT, 2023
** RPGproject
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 22:59:06
*/

#include "ModelEditor.hpp"

#include "Button.hpp"
#include "InputBox.hpp"
#include "PushNotification.hpp"
#include "EditableText.hpp"
#include "EditableTextList.hpp"
#include "Timeline.hpp"
#include "ScrollBox.hpp"

#include "ResourceManager.hpp"

#include "context.hpp"
#include "logger.hpp"
#include "parsing.hpp"

namespace bya {

        void ModelEditor::load()
        {
            sf::Vector2f wSize = sf::Vector2f(context::getWindowSize());

            m_UIelements.add("LoadModelInputBox", std::make_shared<ui::InputBox>());
            m_UIelements.add("LoadModelButton", std::make_shared<ui::Button>());
            m_UIelements.add("SaveModelInputBox", std::make_shared<ui::InputBox>());
            m_UIelements.add("SaveModelButton", std::make_shared<ui::Button>());
            m_UIelements.add("LoadNotification", std::make_shared<ui::PushNotification>());

            m_UIelements.add("PartName", std::make_shared<ui::EditableText>("", 20));
            m_UIelements.add("PartPosition", std::make_shared<ui::EditableTextList>());
            m_UIelements.add("PartSize", std::make_shared<ui::EditableTextList>());
            m_UIelements.add("PartPivot", std::make_shared<ui::EditableTextList>());
            m_UIelements.add("PartParent", std::make_shared<ui::EditableText>("", 20));
            m_UIelements.add("PartZIndex", std::make_shared<ui::EditableText>("", 20));

            m_UIelements.add("PartScrollBox", std::make_shared<ui::ScrollBox<ui::Text>>());
            auto scrollBox = m_UIelements.get<ui::ScrollBox<ui::Text>>("PartScrollBox");
            scrollBox->setPosition(sf::Vector2f(wSize.x * 0.85f, wSize.y * 0.610f));
            scrollBox->addElement(std::make_shared<ui::Text>("No part selected", 20));

            m_UIelements.disable("LoadModelInputBox");
            m_UIelements.disable("SaveModelInputBox");

            {
                auto posList = m_UIelements.get<ui::EditableTextList>("PartPosition");
                posList->addText(std::make_shared<ui::EditableText>("0", 20));
                posList->addText(std::make_shared<ui::EditableText>("0", 20));
                posList->getText(0)->setPrefix("Position: x[");
                posList->getText(0)->setSuffix("]");
                posList->getText(1)->setPrefix(" y[");
                posList->getText(1)->setSuffix("]");
                posList->getText(0)->setType(ui::EditableText::Type::DECIMAL);
                posList->getText(1)->setType(ui::EditableText::Type::DECIMAL);
                posList->getText(0)->setMaxLength(4);
                posList->getText(1)->setMaxLength(4);

                auto sizeList = m_UIelements.get<ui::EditableTextList>("PartSize");
                sizeList->addText(std::make_shared<ui::EditableText>("0", 20));
                sizeList->addText(std::make_shared<ui::EditableText>("0", 20));
                sizeList->getText(0)->setPrefix("Size: x[");
                sizeList->getText(0)->setSuffix("]");
                sizeList->getText(1)->setPrefix(" y[");
                sizeList->getText(1)->setSuffix("]");
                sizeList->getText(0)->setType(ui::EditableText::Type::DECIMAL);
                sizeList->getText(1)->setType(ui::EditableText::Type::DECIMAL);
                sizeList->getText(0)->setMaxLength(4);
                sizeList->getText(1)->setMaxLength(4);

                auto pivotList = m_UIelements.get<ui::EditableTextList>("PartPivot");
                pivotList->addText(std::make_shared<ui::EditableText>("0", 20));
                pivotList->addText(std::make_shared<ui::EditableText>("0", 20));
                pivotList->getText(0)->setPrefix("Pivot: x[");
                pivotList->getText(0)->setSuffix("]");
                pivotList->getText(1)->setPrefix(" y[");
                pivotList->getText(1)->setSuffix("]");
                pivotList->getText(0)->setType(ui::EditableText::Type::DECIMAL);
                pivotList->getText(1)->setType(ui::EditableText::Type::DECIMAL);
                pivotList->getText(0)->setMaxLength(4);
                pivotList->getText(1)->setMaxLength(4);

                float offset = 0.615f;
                m_UIelements.get<ui::EditableText>("PartName")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableTextList>("PartPosition")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableTextList>("PartSize")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableTextList>("PartPivot")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableText>("PartParent")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableText>("PartZIndex")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});

                // add prefix
                m_UIelements.get<ui::EditableText>("PartName")->setPrefix("Name: [");
                m_UIelements.get<ui::EditableText>("PartParent")->setPrefix("Parent: [");
                m_UIelements.get<ui::EditableText>("PartZIndex")->setPrefix("Z-index: [");

                // add suffix
                m_UIelements.get<ui::EditableText>("PartName")->setSuffix("]");
                m_UIelements.get<ui::EditableText>("PartParent")->setSuffix("]");
                m_UIelements.get<ui::EditableText>("PartZIndex")->setSuffix("]");

                m_UIelements.get<ui::EditableText>("PartZIndex")->setType(ui::EditableText::Type::DECIMAL);

                m_UIelements.get<ui::EditableText>("PartName")->setMaxLength(12);
                m_UIelements.get<ui::EditableText>("PartParent")->setMaxLength(12);
                m_UIelements.get<ui::EditableText>("PartZIndex")->setMaxLength(2);
            }

            configureLoadButton();
            configureSaveButton();

            auto loadNotification = m_UIelements.get<ui::PushNotification>("LoadNotification");
            loadNotification->setPosition(sf::Vector2f(wSize.x / 2, wSize.y * 0.2));
            loadNotification->setDuration(3);
            loadNotification->setColor(sf::Color::Red);
            loadNotification->setMaxMessages(3);
            loadNotification->setFontSize(20);

            m_editorBackground.setSize(sf::Vector2f(wSize.x * 0.16, wSize.y));
            m_editorBackground.setOrigin(m_editorBackground.getSize() / 2.f);
            m_editorBackground.setPosition(wSize.x - m_editorBackground.getSize().x / 2.f, wSize.y / 2.f);
            m_editorBackground.setFillColor(sf::Color(50, 50, 50, 255));
            m_editorBackground.setOutlineColor(sf::Color::Black);
            m_editorBackground.setOutlineThickness(5);

            m_partInfoBackground.setSize(sf::Vector2f(wSize.x * 0.15, wSize.y * 0.33));
            m_partInfoBackground.setOrigin(m_partInfoBackground.getSize() / 2.f);
            m_partInfoBackground.setPosition((wSize.x * 0.995) - m_partInfoBackground.getSize().x / 2.f, wSize.y * 0.82);
            m_partInfoBackground.setFillColor(sf::Color(50, 50, 50, 255));
            m_partInfoBackground.setOutlineColor(sf::Color::Black);
            m_partInfoBackground.setOutlineThickness(5);
        }

        void ModelEditor::configureSaveButton()
        {
            auto wSize = sf::Vector2f(context::getWindowSize());

            auto inputBox = m_UIelements.get<ui::InputBox>("SaveModelInputBox");
            auto saveButton = m_UIelements.get<ui::Button>("SaveModelButton");

            sf::FloatRect inputBoxBounds = inputBox->getBounds();
            inputBox->setPosition({wSize.x / 2, wSize.y / 2});
            inputBox->setLabel("Save file to:");
            inputBox->getApplyButton()->setCallback([this, inputBox]() {
                if (inputBox->getInput().empty())
                    return;
                try {
                    m_entity->saveToJson(inputBox->getInput());
                    logger::log("Model: " + inputBox->getInput() + " saved successfully");
                    m_UIelements.disable("SaveModelInputBox");
                    auto loadNotification = m_UIelements.get<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage("Model saved successfully", sf::Color::Green);
                    inputBox->reset();
                } catch (std::exception &e) {
                    auto loadNotification = m_UIelements.get<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage(e.what());
                    logger::error(e.what());
                }
            });
            inputBox->getCancelButton()->setCallback([this, inputBox]() {
                inputBox->setActive(false);
                inputBox->reset();
                m_UIelements.disable("SaveModelInputBox");
            });

            saveButton->setLabel("Save to json");
            sf::FloatRect bounds =  saveButton->getBounds();
            saveButton->setPosition({wSize.x - bounds.width / 1.9f, bounds.height * 1.6f});
            saveButton->setCallback([this]() {
                if (m_UIelements.isEnabled("LoadModelInputBox"))
                    m_UIelements.disable("LoadModelInputBox");
                m_UIelements.toggle("SaveModelInputBox");
                if (m_UIelements.isEnabled("SaveModelInputBox"))
                    m_UIelements.get<ui::InputBox>("SaveModelInputBox")->setActive(true);
            });
        }

        void ModelEditor::configureLoadButton()
        {
            auto wSize = sf::Vector2f(context::getWindowSize());

            auto inputBox = m_UIelements.get<ui::InputBox>("LoadModelInputBox");
            sf::FloatRect inputBoxBounds = inputBox->getBounds();
            inputBox->setPosition({wSize.x / 2, wSize.y / 2});
            inputBox->setLabel("Load file from:");
            inputBox->getApplyButton()->setCallback([this, inputBox]() {
                if (inputBox->getInput().empty())
                    return;
                try {
                    m_selectedPart = nullptr;
                    if (m_entity == nullptr)
                        m_entity = std::make_shared<gameObj::PartEntity>();
                    m_entity->loadFromJson(inputBox->getInput());
                    logger::log("Model: " + inputBox->getInput() + " loaded successfully");
                    sf::Vector2f pos = sf::Vector2f(context::getWindowSize());
                    m_entity->setPosition({pos.x / 2, pos.y / 2});
                    m_UIelements.disable("LoadModelInputBox");
                    auto loadNotification = m_UIelements.get<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage("Model loaded successfully", sf::Color::Green);
                    inputBox->setActive(false);
                    inputBox->reset();
                    auto scrollBox = m_UIelements.get<ui::ScrollBox<ui::Text>>("PartScrollBox");
                    scrollBox->clear();
                    scrollBox->addElement(std::make_shared<ui::Text>("No part selected", 20));
                    for (auto &part : m_entity->getSortedZParts()) {
                        scrollBox->addElement(std::make_shared<ui::Text>(part->getName(), 20));
                    }
                } catch (std::exception &e) {
                    auto loadNotification = m_UIelements.get<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage(e.what());
                    logger::error(e.what());
                }
            });
            inputBox->getCancelButton()->setCallback([this, inputBox]() {
                inputBox->setActive(false);
                inputBox->reset();
                m_UIelements.disable("LoadModelInputBox");
            });

            auto loadModelButton = m_UIelements.get<ui::Button>("LoadModelButton");
            sf::FloatRect bounds = loadModelButton->getBounds();
            loadModelButton->setLabel("Load from json");
            loadModelButton->setPosition({wSize.x - bounds.width / 1.9f, bounds.height / 2});
            loadModelButton->setCallback([this]() {
                if (m_UIelements.isEnabled("SaveModelInputBox"))
                    m_UIelements.disable("SaveModelInputBox");
                m_UIelements.toggle("LoadModelInputBox");
                if (m_UIelements.isEnabled("LoadModelInputBox"))
                    m_UIelements.get<ui::InputBox>("LoadModelInputBox")->setActive(true);
            });
        }

        void ModelEditor::resetPartInfo()
        {
            m_UIelements.get<ui::EditableText>("PartName")->setPreInpSufx("No part selected");
            m_UIelements.get<ui::EditableTextList>("PartPosition")->getText(0)->setPreInpSufx("0");
            m_UIelements.get<ui::EditableTextList>("PartPosition")->getText(1)->setPreInpSufx("0");
            m_UIelements.get<ui::EditableTextList>("PartSize")->getText(0)->setPreInpSufx("0");
            m_UIelements.get<ui::EditableTextList>("PartSize")->getText(1)->setPreInpSufx("0");
            m_UIelements.get<ui::EditableTextList>("PartPivot")->getText(0)->setPreInpSufx("0");
            m_UIelements.get<ui::EditableTextList>("PartPivot")->getText(1)->setPreInpSufx("0");
            m_UIelements.get<ui::EditableText>("PartParent")->setPreInpSufx("No parent");
            m_UIelements.get<ui::EditableText>("PartZIndex")->setPreInpSufx("0");
        }

        void ModelEditor::setPartInfo()
        {
            if (m_selectedPart == nullptr) {
                resetPartInfo();
                return;
            }

            m_UIelements.get<ui::EditableText>("PartName")->setPreInpSufx(m_selectedPart->getName());

            auto posList = m_UIelements.get<ui::EditableTextList>("PartPosition");
            sf::Vector2f position = m_selectedPart->getPosition();
            posList->getText(0)->setPreInpSufx(parsing::floatToString(position.x - m_entity->getPosition().x));
            posList->getText(1)->setPreInpSufx(parsing::floatToString(position.y - m_entity->getPosition().y));

            auto sizeList = m_UIelements.get<ui::EditableTextList>("PartSize");
            sizeList->getText(0)->setPreInpSufx(parsing::floatToString(m_selectedPart->getSize().x));
            sizeList->getText(1)->setPreInpSufx(parsing::floatToString(m_selectedPart->getSize().y));

            auto pivotList = m_UIelements.get<ui::EditableTextList>("PartPivot");
            pivotList->getText(0)->setPreInpSufx(parsing::floatToString(m_selectedPart->getOrigin().x));
            pivotList->getText(1)->setPreInpSufx(parsing::floatToString(m_selectedPart->getOrigin().y));

            auto partParent = m_UIelements.get<ui::EditableText>("PartParent");
            auto parent = m_selectedPart->getParent();
            if (parent)
                partParent->setPreInpSufx(parent->getName());
            else
                partParent->setPreInpSufx("None");

            m_UIelements.get<ui::EditableText>("PartZIndex")->setPreInpSufx(std::to_string(m_selectedPart->getZIndex()));
        }

        void ModelEditor::handleEvent(sf::Event &event, sf::RenderWindow &window)
        {
            auto scrollBox = m_UIelements.get<ui::ScrollBox<ui::Text>>("PartScrollBox");

            if (m_entity != nullptr) {
                auto& parts = m_entity->getSortedZParts();
                std::shared_ptr<gameObj::IMultPartEntity> lastFound = nullptr;
                for (auto& part : parts) {
                    if (part != m_selectedPart)
                        part->setTint(sf::Color::White);
                    if (part->isHovered()) {
                        lastFound = part;
                        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                            m_selectedPart = part;
                            auto scrollBoxElems = scrollBox->getElements();
                            for (auto& elem : scrollBoxElems) {
                                if (elem->getString() == part->getName()) {
                                    scrollBox->setSelectedElement(elem);
                                    break;
                                }
                            }
                            setPartInfo();
                        }
                    }
                }
                if (lastFound)
                    lastFound->setTint(sf::Color::Green);
                if (m_selectedPart)
                    m_selectedPart->setTint(sf::Color::Yellow);
            }

            if (m_entity) {
                auto& parts = m_entity->getSortedZParts();
                for (int i = 0; i < parts.size(); i++) {
                    if (parts[i]->getName() == scrollBox->getSelectedElement()->getString() && parts[i] != m_selectedPart) {
                        if (m_selectedPart)
                            m_selectedPart->setTint(sf::Color::White);
                        m_selectedPart = parts[i];
                        m_selectedPart->setTint(sf::Color::Yellow);
                        setPartInfo();
                        break;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && m_selectedPart) {
                sf::Vector2f pos = sf::Vector2f(std::atof(m_UIelements.get<ui::EditableTextList>("PartPosition")->getText(0)->getInput().c_str()),
                std::atof(m_UIelements.get<ui::EditableTextList>("PartPosition")->getText(1)->getInput().c_str()));
                sf::Vector2f size = sf::Vector2f(std::atof(m_UIelements.get<ui::EditableTextList>("PartSize")->getText(0)->getInput().c_str()),
                std::atof(m_UIelements.get<ui::EditableTextList>("PartSize")->getText(1)->getInput().c_str()));
                sf::Vector2f pivot = sf::Vector2f(std::atof(m_UIelements.get<ui::EditableTextList>("PartPivot")->getText(0)->getInput().c_str()),
                std::atof(m_UIelements.get<ui::EditableTextList>("PartPivot")->getText(1)->getInput().c_str()));
                int zIndex = std::atoi(m_UIelements.get<ui::EditableText>("PartZIndex")->getInput().c_str());

                m_selectedPart->setPosition(pos + m_entity->getPosition());
                m_selectedPart->setSize(size);
                m_selectedPart->setOrigin(pivot);
                m_selectedPart->setZIndex(zIndex);
                m_entity->sortZIndex();
            }
        }

        void ModelEditor::update(float dt)
        {
        }

        void ModelEditor::render(sf::RenderTarget &target)
        {
            target.draw(m_editorBackground);
            target.draw(m_partInfoBackground);

            if (m_entity)
                m_entity->render(target);
        }
}