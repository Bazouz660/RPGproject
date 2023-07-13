/*
** EPITECH PROJECT, 2023
** RPGproject
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-14 01:35:52
*/

#include "AnimationEditor.hpp"

#include "Button.hpp"
#include "GrabBoxOrbital.hpp"
#include "InputBox.hpp"
#include "PushNotification.hpp"
#include "EditableText.hpp"
#include "EditableTextList.hpp"
#include "Timeline.hpp"

#include "ResourceManager.hpp"

#include "context.hpp"
#include "logger.hpp"
#include "parsing.hpp"

namespace bya {

        void AnimationEditor::init()
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
            m_UIelements.add("PartRotation", std::make_shared<ui::EditableText>("", 20));
            m_UIelements.add("PartPivot", std::make_shared<ui::EditableTextList>());
            m_UIelements.add("PartParent", std::make_shared<ui::EditableText>("", 20));
            m_UIelements.add("PartZIndex", std::make_shared<ui::EditableText>("", 20));

            m_UIelements.add("Timeline", std::make_shared<ui::Timeline>());
            m_UIelements.get<ui::Timeline>("Timeline")->setPosition(sf::Vector2f(wSize.x * 0.5, wSize.y * 0.85));
            m_UIelements.get<ui::Timeline>("Timeline")->setSize(sf::Vector2f(wSize.x * 0.4, 20));

            m_UIelements.add("RotationGrab", std::make_shared<ui::GrabBoxOrbital>());
            m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab")->setSize(sf::Vector2f(70, 20));
            m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab")->setOrigin(sf::Vector2f(35, 10));
            m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab")->setRadius(100);
            m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab")->setCenter(sf::Vector2f(wSize.x / 2, wSize.y / 2));
            m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab")->setPosition(sf::Vector2f(wSize.x / 2, wSize.y / 2));
            m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab")->setTexture(RESOURCE().getTexture("model_editor", "rotation_hint"));

            m_UIelements.disable("RotationGrab");
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
                posList->getText(0)->onlyNumbers(true);
                posList->getText(1)->onlyNumbers(true);
                posList->getText(0)->setMaxLength(4);
                posList->getText(1)->setMaxLength(4);

                auto sizeList = m_UIelements.get<ui::EditableTextList>("PartSize");
                sizeList->addText(std::make_shared<ui::EditableText>("0", 20));
                sizeList->addText(std::make_shared<ui::EditableText>("0", 20));
                sizeList->getText(0)->setPrefix("Size: x[");
                sizeList->getText(0)->setSuffix("]");
                sizeList->getText(1)->setPrefix(" y[");
                sizeList->getText(1)->setSuffix("]");
                sizeList->getText(0)->onlyNumbers(true);
                sizeList->getText(1)->onlyNumbers(true);
                sizeList->getText(0)->setMaxLength(4);
                sizeList->getText(1)->setMaxLength(4);

                auto pivotList = m_UIelements.get<ui::EditableTextList>("PartPivot");
                pivotList->addText(std::make_shared<ui::EditableText>("0", 20));
                pivotList->addText(std::make_shared<ui::EditableText>("0", 20));
                pivotList->getText(0)->setPrefix("Pivot: x[");
                pivotList->getText(0)->setSuffix("]");
                pivotList->getText(1)->setPrefix(" y[");
                pivotList->getText(1)->setSuffix("]");
                pivotList->getText(0)->onlyNumbers(true);
                pivotList->getText(1)->onlyNumbers(true);
                pivotList->getText(0)->setMaxLength(4);
                pivotList->getText(1)->setMaxLength(4);

                float offset = 0.615f;
                m_UIelements.get<ui::EditableText>("PartName")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableTextList>("PartPosition")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableTextList>("PartSize")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableText>("PartRotation")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableTextList>("PartPivot")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableText>("PartParent")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                m_UIelements.get<ui::EditableText>("PartZIndex")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});

                // add prefix
                m_UIelements.get<ui::EditableText>("PartName")->setPrefix("Name: [");
                m_UIelements.get<ui::EditableText>("PartRotation")->setPrefix("Rotation: [");
                m_UIelements.get<ui::EditableText>("PartParent")->setPrefix("Parent: [");
                m_UIelements.get<ui::EditableText>("PartZIndex")->setPrefix("Z-index: [");

                // add suffix
                m_UIelements.get<ui::EditableText>("PartName")->setSuffix("]");
                m_UIelements.get<ui::EditableText>("PartRotation")->setSuffix("]");
                m_UIelements.get<ui::EditableText>("PartParent")->setSuffix("]");
                m_UIelements.get<ui::EditableText>("PartZIndex")->setSuffix("]");

                m_UIelements.get<ui::EditableText>("PartRotation")->onlyNumbers(true);
                m_UIelements.get<ui::EditableText>("PartZIndex")->onlyNumbers(true);

                m_UIelements.get<ui::EditableText>("PartName")->setMaxLength(12);
                m_UIelements.get<ui::EditableText>("PartRotation")->setMaxLength(4);
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

            m_editorBackground.setSize(sf::Vector2f(310, wSize.y));
            m_editorBackground.setOrigin(m_editorBackground.getSize() / 2.f);
            m_editorBackground.setPosition(wSize.x - m_editorBackground.getSize().x / 2.f, wSize.y / 2.f);
            m_editorBackground.setFillColor(sf::Color(50, 50, 50, 255));
            m_editorBackground.setOutlineColor(sf::Color::Black);
            m_editorBackground.setOutlineThickness(5);

            m_partInfoBackground.setSize(sf::Vector2f(290, 360));
            m_partInfoBackground.setOrigin(m_partInfoBackground.getSize() / 2.f);
            m_partInfoBackground.setPosition((wSize.x * 0.995) - m_partInfoBackground.getSize().x / 2.f, wSize.y - m_partInfoBackground.getSize().y / 1.9f);
            m_partInfoBackground.setFillColor(sf::Color(50, 50, 50, 255));
            m_partInfoBackground.setOutlineColor(sf::Color::Black);
            m_partInfoBackground.setOutlineThickness(5);
        }

        void AnimationEditor::configureSaveButton()
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
                } catch (std::exception &e) {
                    auto loadNotification = m_UIelements.get<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage(e.what());
                    logger::error(e.what());
                }
            });
            inputBox->getCancelButton()->setCallback([this]() {
                m_UIelements.get<ui::InputBox>("SaveModelInputBox")->setActive(false);
                m_UIelements.get<ui::InputBox>("SaveModelInputBox")->setLabel("");
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

        void AnimationEditor::configureLoadButton()
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
                    m_UIelements.disable("RotationGrab");
                    if (m_entity == nullptr)
                        m_entity = std::make_shared<gameObj::PartEntity>();
                    m_entity->loadFromJson(inputBox->getInput());
                    logger::log("Model: " + inputBox->getInput() + " loaded successfully");
                    sf::Vector2f pos = sf::Vector2f(context::getWindowSize());
                    m_entity->setPosition({pos.x / 2, pos.y / 2});
                    m_UIelements.disable("LoadModelInputBox");
                    auto loadNotification = m_UIelements.get<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage("Model loaded successfully", sf::Color::Green);
                } catch (std::exception &e) {
                    auto loadNotification = m_UIelements.get<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage(e.what());
                    logger::error(e.what());
                }
            });
            inputBox->getCancelButton()->setCallback([this]() {
                m_UIelements.get<ui::InputBox>("LoadModelInputBox")->setActive(false);
                m_UIelements.get<ui::InputBox>("LoadModelInputBox")->setLabel("");
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

        void AnimationEditor::setPartInfo()
        {
            m_UIelements.get<ui::EditableText>("PartName")->setString(m_selectedPart->getName());

            float rotation = m_selectedPart->getOwnRotation();
            m_UIelements.get<ui::EditableText>("PartRotation")->setString(parsing::floatToString(rotation));

            auto posList = m_UIelements.get<ui::EditableTextList>("PartPosition");
            sf::Vector2f position = m_selectedPart->getPosition();
            posList->getText(0)->setString(parsing::floatToString(position.x - m_entity->getPosition().x));
            posList->getText(1)->setString(parsing::floatToString(position.y - m_entity->getPosition().y));

            auto sizeList = m_UIelements.get<ui::EditableTextList>("PartSize");
            sizeList->getText(0)->setString(parsing::floatToString(m_selectedPart->getSize().x));
            sizeList->getText(1)->setString(parsing::floatToString(m_selectedPart->getSize().y));

            auto pivotList = m_UIelements.get<ui::EditableTextList>("PartPivot");
            pivotList->getText(0)->setString(parsing::floatToString(m_selectedPart->getPivotPoint().x));
            pivotList->getText(1)->setString(parsing::floatToString(m_selectedPart->getPivotPoint().y));

            auto partParent = m_UIelements.get<ui::EditableText>("PartParent");
            auto parent = m_selectedPart->getParent();
            if (parent)
                partParent->setString(parent->getName());
            else
                partParent->setString("None");

            m_UIelements.get<ui::EditableText>("PartZIndex")->setString(std::to_string(m_selectedPart->getZIndex()));

            m_UIelements.enable("RotationGrab");
            m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab")->setCenter(position);
            m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab")->setAngle(rotation);
            m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab")->applyTransform(rotation);
        }

        void AnimationEditor::handleEvent(sf::Event &event, sf::RenderWindow &window)
        {
            auto rotationGrabBox = m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab");

            if (m_entity != nullptr) {
                auto& parts = m_entity->getSortedZParts();
                gameObj::IMultPartEntity* lastFound = nullptr;
                for (auto& part : parts) {
                    if (part != m_selectedPart)
                        part->setTint(sf::Color::White);
                    if (part->isHovered()) {
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
                sf::Vector2f pos = sf::Vector2f(std::atof(m_UIelements.get<ui::EditableTextList>("PartPosition")->getText(0)->getInput().c_str()),
                                    std::atof(m_UIelements.get<ui::EditableTextList>("PartPosition")->getText(1)->getInput().c_str()));
                sf::Vector2f size = sf::Vector2f(std::atof(m_UIelements.get<ui::EditableTextList>("PartSize")->getText(0)->getInput().c_str()),
                                    std::atof(m_UIelements.get<ui::EditableTextList>("PartSize")->getText(1)->getInput().c_str()));
                sf::Vector2f pivot = sf::Vector2f(std::atof(m_UIelements.get<ui::EditableTextList>("PartPivot")->getText(0)->getInput().c_str()),
                                    std::atof(m_UIelements.get<ui::EditableTextList>("PartPivot")->getText(1)->getInput().c_str()));
                float rotation = std::atof(m_UIelements.get<ui::EditableText>("PartRotation")->getInput().c_str());
                int zIndex = std::atoi(m_UIelements.get<ui::EditableText>("PartZIndex")->getInput().c_str());

                m_selectedPart->setPosition(pos + m_entity->getPosition());
                m_selectedPart->setSize(size);
                m_selectedPart->setPivotPoint(pivot);
                m_selectedPart->setRotation(rotation);
                m_selectedPart->setZIndex(zIndex);
                m_entity->sortZIndex();
            }
        }

        void AnimationEditor::update(float dt)
        {
            auto rotationGrabBox = m_UIelements.get<ui::GrabBoxOrbital>("RotationGrab");

            if (m_entity && rotationGrabBox->isGrabbed()) {
                float angle = rotationGrabBox->getAngle();
                m_selectedPart->setRotation(angle);
                m_UIelements.get<ui::EditableText>("PartRotation")->setString(parsing::floatToString(angle));
            }
        }

        void AnimationEditor::render(sf::RenderTarget &target)
        {
            target.draw(m_editorBackground);
            target.draw(m_partInfoBackground);

            if (m_entity)
                m_entity->render(target, true);

            AScene::renderUi(target);
        }
}