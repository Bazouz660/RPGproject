/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-09 20:21:12
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-11 17:59:58
 *  Description:
 */

#include "MainMenu.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "context.hpp"

namespace bya
{
    MainMenu::MainMenu()
    {
    }

    MainMenu::~MainMenu()
    {
    }

    void MainMenu::init()
    {
        m_background.setFillColor(sf::Color(15, 15, 15, 255));
        m_gameLogo.setTexture(getResource().getTexture("main_menu", "logo"));
        m_gameLogo.setPosition(
                (context::getWindowSize().x - m_gameLogo.getGlobalBounds().width) / 2,
                (context::getWindowSize().y - m_gameLogo.getGlobalBounds().height) * 0.1f);
        addUIelement("ContinueButton", std::make_shared<ui::MenuButton>());
        addUIelement("LoadButton", std::make_shared<ui::MenuButton>());
        addUIelement("NewButton", std::make_shared<ui::MenuButton>());
        addUIelement("SettingsButton", std::make_shared<ui::MenuButton>());
        addUIelement("CreditsButton", std::make_shared<ui::MenuButton>());
        addUIelement("ExtraButton", std::make_shared<ui::MenuButton>());
        addUIelement("QuitButton", std::make_shared<ui::MenuButton>());

        auto playButton = getUIelement<ui::MenuButton>("ContinueButton");
        playButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.6));
        playButton->setLabel("Continue");
        playButton->setDisabled();
        playButton->setCallback([](){
            SceneManager::getInstance().setCurrentScene("AnimationEditor");
        });

        auto loadButton = getUIelement<ui::MenuButton>("LoadButton");
        loadButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.64));
        loadButton->setLabel("Load game");

        auto newButton = getUIelement<ui::MenuButton>("NewButton");
        newButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.68));
        newButton->setLabel("New game");

        auto settingsButton = getUIelement<ui::MenuButton>("SettingsButton");
        settingsButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.72));
        settingsButton->setLabel("Settings");

        auto creditsButton = getUIelement<ui::MenuButton>("CreditsButton");
        creditsButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.76));
        creditsButton->setLabel("Credits");

        auto extraButton = getUIelement<ui::MenuButton>("ExtraButton");
        extraButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.8));
        extraButton->setLabel("Extra");

        auto quitButton = getUIelement<ui::MenuButton>("QuitButton");
        quitButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.84));
        quitButton->setLabel("Quit");
        quitButton->setCallback([](){
            context::closeWindow();
        });
    }

    void MainMenu::handleEvent(sf::Event &event, sf::RenderWindow &window)
    {
    }

    void MainMenu::update(float dt)
    {
        AScene::updateUI(dt);
    }

    void MainMenu::render(sf::RenderTarget &target)
    {
        target.draw(m_background);
        target.draw(m_gameLogo);
        AScene::renderUi(target);
    }
}
