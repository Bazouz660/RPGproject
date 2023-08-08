/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-09 20:21:12
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-18 00:39:50
 *  Description:
 */

#include "MainMenu.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "MenuGraph.hpp"
#include "context.hpp"

namespace bya
{
    MainMenu::MainMenu()
    {
        m_gameLogo.setTexture(RESOURCE().getTexture("main_menu", "logo"));

        auto menuGraph = std::make_shared<ui::MenuGraph>();
        auto mainMenu = std::make_shared<ui::Menu>();
        auto settingsMenu = std::make_shared<ui::Menu>();
        menuGraph->add("mainMenu", mainMenu);
        menuGraph->add("settingsMenu", settingsMenu);

        m_UIelements.add("menuGraph", menuGraph);

        configureMainMenu();
        configureSettingsMenu();
    }

    void MainMenu::configureMainMenu()
    {
        auto menuGraph = m_UIelements.get<ui::MenuGraph>("menuGraph");
        auto mainMenu = menuGraph->get("mainMenu");

        mainMenu->add("Continue", std::make_shared<ui::MenuButton>());
        mainMenu->add("NewGame", std::make_shared<ui::MenuButton>());
        mainMenu->add("Extra", std::make_shared<ui::MenuButton>());
        mainMenu->add("Settings", std::make_shared<ui::MenuButton>());
        mainMenu->add("Credits", std::make_shared<ui::MenuButton>());
        mainMenu->add("Quit", std::make_shared<ui::MenuButton>());

        auto continueButton = mainMenu->get<ui::MenuButton>("Continue");
        continueButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.6));
        continueButton->setLabel("Continue");
        continueButton->setDisabled();

        auto newGameButton = mainMenu->get<ui::MenuButton>("NewGame");
        newGameButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.64));
        newGameButton->setLabel("New Game");

        auto extraButton = mainMenu->get<ui::MenuButton>("Extra");
        extraButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.68));
        extraButton->setLabel("Extra");
        extraButton->setCallback([](){
            SceneManager::getInstance().setCurrentScene("AnimationEditor");
        });

        auto settingsButton = mainMenu->get<ui::MenuButton>("Settings");
        settingsButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.72));
        settingsButton->setLabel("Settings");
        settingsButton->setCallback([menuGraph](){
            menuGraph->setCurrent("settingsMenu");
        });

        auto creditsButton = mainMenu->get<ui::MenuButton>("Credits");
        creditsButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.76));
        creditsButton->setLabel("Credits");

        auto quitButton = mainMenu->get<ui::MenuButton>("Quit");
        quitButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.8));
        quitButton->setLabel("Quit");
        quitButton->setCallback([](){
            context::closeWindow();
        });
    }

    void MainMenu::configureSettingsMenu()
    {
        auto menuGraph = m_UIelements.get<ui::MenuGraph>("menuGraph");
        auto settingsMenu = menuGraph->get("settingsMenu");

        settingsMenu->add("Back", std::make_shared<ui::MenuButton>());
        settingsMenu->add("Fullscreen", std::make_shared<ui::MenuButton>());
        settingsMenu->add("Resolution", std::make_shared<ui::MenuButton>());
        settingsMenu->add("Volume", std::make_shared<ui::MenuButton>());

        auto backButton = settingsMenu->get<ui::MenuButton>("Back");
        backButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.8));
        backButton->setLabel("Back");
        backButton->setCallback([menuGraph](){
            menuGraph->setCurrent("mainMenu");
        });

        auto fullscreenButton = settingsMenu->get<ui::MenuButton>("Fullscreen");
        fullscreenButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.6));
        fullscreenButton->setLabel("Fullscreen");
        fullscreenButton->setCallback([](){
            //context::toggleFullscreen();
        });

        auto resolutionButton = settingsMenu->get<ui::MenuButton>("Resolution");
        resolutionButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.64));
        resolutionButton->setLabel("Resolution");

        auto volumeButton = settingsMenu->get<ui::MenuButton>("Volume");
        volumeButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.68));
        volumeButton->setLabel("Volume");
    }

    void MainMenu::load()
    {
        MusicManager::getInstance().switchTrack("main_theme", 1.f, true, false);

        m_gameLogo.setPosition(
                (context::getWindowSize().x - m_gameLogo.getGlobalBounds().width) / 2,
                (context::getWindowSize().y - m_gameLogo.getGlobalBounds().height) * 0.2f);
    }

    void MainMenu::handleEvent(sf::Event &event, sf::RenderWindow &window)
    {
    }

    void MainMenu::update(float dt)
    {
    }

    void MainMenu::render(sf::RenderTarget &target)
    {
        target.draw(m_background);
        target.draw(m_gameLogo);
    }
}
