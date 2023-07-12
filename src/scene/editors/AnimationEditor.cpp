/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** AnimationEditor
*/

#include "AnimationEditor.hpp"

#include "Button.hpp"
#include "GrabBoxOrbital.hpp"
#include "InputBox.hpp"
#include "PushNotification.hpp"
#include "EditableText.hpp"
#include "EditableTextList.hpp"

#include "ResourceManager.hpp"

#include "context.hpp"
#include "logger.hpp"
#include "parsing.hpp"

namespace bya {

        void AnimationEditor::init()
        {
            sf::Vector2f wSize = sf::Vector2f(context::getWindowSize());

            addUIelement("LoadModelInputBox", std::make_shared<ui::InputBox>());
            addUIelement("LoadModelButton", std::make_shared<ui::Button>());
            addUIelement("SaveModelInputBox", std::make_shared<ui::InputBox>());
            addUIelement("SaveModelButton", std::make_shared<ui::Button>());
            addUIelement("LoadNotification", std::make_shared<ui::PushNotification>());

            addUIelement("PartName", std::make_shared<ui::EditableText>("", 20));
            addUIelement("PartPosition", std::make_shared<ui::EditableTextList>());
            addUIelement("PartSize", std::make_shared<ui::EditableTextList>());
            addUIelement("PartRotation", std::make_shared<ui::EditableText>("", 20));
            addUIelement("PartPivot", std::make_shared<ui::EditableTextList>());
            addUIelement("PartParent", std::make_shared<ui::EditableText>("", 20));
            addUIelement("PartZIndex", std::make_shared<ui::EditableText>("", 20));

            addUIelement("RotationGrab", std::make_shared<ui::GrabBoxOrbital>());
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setSize(sf::Vector2f(70, 20));
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setOrigin(sf::Vector2f(35, 10));
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setRadius(100);
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setCenter(sf::Vector2f(wSize.x / 2, wSize.y / 2));
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setPosition(sf::Vector2f(wSize.x / 2, wSize.y / 2));
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setTexture(getResource().getTexture("model_editor", "rotation_hint"));
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setEnabled(false);

            {
                auto posList = getUIelement<ui::EditableTextList>("PartPosition");
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

                auto sizeList = getUIelement<ui::EditableTextList>("PartSize");
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

                auto pivotList = getUIelement<ui::EditableTextList>("PartPivot");
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
                getUIelement<ui::EditableText>("PartName")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableTextList>("PartPosition")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableTextList>("PartSize")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableText>("PartRotation")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableTextList>("PartPivot")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableText>("PartParent")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});
                getUIelement<ui::EditableText>("PartZIndex")->setPosition({wSize.x * 0.85f, wSize.y * (offset += 0.05f)});

                // add prefix
                getUIelement<ui::EditableText>("PartName")->setPrefix("Name: [");
                getUIelement<ui::EditableText>("PartRotation")->setPrefix("Rotation: [");
                getUIelement<ui::EditableText>("PartParent")->setPrefix("Parent: [");
                getUIelement<ui::EditableText>("PartZIndex")->setPrefix("Z-index: [");

                // add suffix
                getUIelement<ui::EditableText>("PartName")->setSuffix("]");
                getUIelement<ui::EditableText>("PartRotation")->setSuffix("]");
                getUIelement<ui::EditableText>("PartParent")->setSuffix("]");
                getUIelement<ui::EditableText>("PartZIndex")->setSuffix("]");

                getUIelement<ui::EditableText>("PartRotation")->onlyNumbers(true);
                getUIelement<ui::EditableText>("PartZIndex")->onlyNumbers(true);

                getUIelement<ui::EditableText>("PartName")->setMaxLength(12);
                getUIelement<ui::EditableText>("PartRotation")->setMaxLength(4);
                getUIelement<ui::EditableText>("PartParent")->setMaxLength(12);
                getUIelement<ui::EditableText>("PartZIndex")->setMaxLength(2);
            }

            configureLoadButton();
            configureSaveButton();

            auto loadNotification = getUIelement<ui::PushNotification>("LoadNotification");
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

            auto inputBox = getUIelement<ui::InputBox>("SaveModelInputBox");
            auto saveButton = getUIelement<ui::Button>("SaveModelButton");

            sf::FloatRect inputBoxBounds = inputBox->getBounds();
            inputBox->setPosition({wSize.x / 2, wSize.y / 2});
            inputBox->setLabel("Save file to:");
            inputBox->getApplyButton()->setCallback([this, inputBox]() {
                if (inputBox->getInput().empty())
                    return;
                try {
                    m_entity->saveToJson(inputBox->getInput());
                    logger::log("Model: " + inputBox->getInput() + " saved successfully");
                    auto inputBox = getUIelement<ui::InputBox>("SaveModelInputBox");
                    inputBox->setOpen(false);
                    auto loadNotification = getUIelement<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage("Model saved successfully", sf::Color::Green);
                } catch (std::exception &e) {
                    auto loadNotification = getUIelement<ui::PushNotification>("LoadNotification");
                    loadNotification->pushMessage(e.what());
                    logger::error(e.what());
                }
            });

            saveButton->setLabel("Save to json");
            sf::FloatRect bounds =  saveButton->getBounds();
            saveButton->setPosition({wSize.x - bounds.width / 1.9f, bounds.height * 1.6f});
            saveButton->setCallback([this]() {
                if (getUIelement<ui::InputBox>("LoadModelInputBox")->isOpen())
                    getUIelement<ui::InputBox>("LoadModelInputBox")->setOpen(false);
                auto saveModelInputBox = getUIelement<ui::InputBox>("SaveModelInputBox");
                saveModelInputBox->setOpen(!saveModelInputBox->isOpen());
                if (saveModelInputBox->isOpen())
                    saveModelInputBox->setActive(true);
            });
        }

        void AnimationEditor::configureLoadButton()
        {
            auto wSize = sf::Vector2f(context::getWindowSize());

            auto inputBox = getUIelement<ui::InputBox>("LoadModelInputBox");
            sf::FloatRect inputBoxBounds = inputBox->getBounds();
            inputBox->setPosition({wSize.x / 2, wSize.y / 2});
            inputBox->setLabel("Load file from:");
            inputBox->getApplyButton()->setCallback([this, inputBox]() {
                if (inputBox->getInput().empty())
                    return;
                try {
                    m_selectedPart = nullptr;
                    getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setEnabled(false);
                    if (m_entity == nullptr)
                        m_entity = std::make_shared<gameObj::PartEntity>();
                    m_entity->loadFromJson(inputBox->getInput());
                    logger::log("Model: " + inputBox->getInput() + " loaded successfully");
                    sf::Vector2f pos = sf::Vector2f(context::getWindowSize());
                    m_entity->setPosition({pos.x / 2, pos.y / 2});
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
            sf::FloatRect bounds = loadModelButton->getBounds();
            loadModelButton->setLabel("Load from json");
            loadModelButton->setPosition({wSize.x - bounds.width / 1.9f, bounds.height / 2});
            loadModelButton->setCallback([this]() {
                if (getUIelement<ui::InputBox>("SaveModelInputBox")->isOpen())
                    getUIelement<ui::InputBox>("SaveModelInputBox")->setOpen(false);
                auto loadModelInputBox = getUIelement<ui::InputBox>("LoadModelInputBox");
                loadModelInputBox->setOpen(!loadModelInputBox->isOpen());
                if (loadModelInputBox->isOpen())
                    loadModelInputBox->setActive(true);
            });
        }

        bool AnimationEditor::isHoveringUI()
        {
            sf::Vector2f mousePos = context::getMousePosition();

            for (auto &element : m_UIelements) {
                if (element.second->getBounds().contains(mousePos))
                    return true;
            }
            return false;
        }

        void AnimationEditor::setPartInfo()
        {
            getUIelement<ui::EditableText>("PartName")->setString(m_selectedPart->getName());

            float rotation = m_selectedPart->getOwnRotation();
            getUIelement<ui::EditableText>("PartRotation")->setString(parsing::floatToString(rotation));

            auto posList = getUIelement<ui::EditableTextList>("PartPosition");
            sf::Vector2f position = m_selectedPart->getPosition();
            posList->getText(0)->setString(parsing::floatToString(position.x - m_entity->getPosition().x));
            posList->getText(1)->setString(parsing::floatToString(position.y - m_entity->getPosition().y));

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

            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setEnabled(true);
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setCenter(position);
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->setAngle(rotation);
            getUIelement<ui::GrabBoxOrbital>("RotationGrab")->applyTransform(rotation);
        }

        void AnimationEditor::handleEvent(sf::Event &event, sf::RenderWindow &window)
        {
            auto rotationGrabBox = getUIelement<ui::GrabBoxOrbital>("RotationGrab");

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
                m_selectedPart->setRotation(rotation);
                m_selectedPart->setZIndex(zIndex);
                m_entity->sortZIndex();
            }
        }

        void AnimationEditor::update(float dt)
        {
            auto rotationGrabBox = getUIelement<ui::GrabBoxOrbital>("RotationGrab");

            if (m_entity && rotationGrabBox->isGrabbed()) {
                float angle = rotationGrabBox->getAngle();
                m_selectedPart->setRotation(angle);
                getUIelement<ui::EditableText>("PartRotation")->setString(parsing::floatToString(angle));
                // FIX ROTATION
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