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
        MusicManager::getInstance().switchTrack("main_theme", 1.f, true, false);

        m_gameLogo.setTexture(RESOURCE().getTexture("main_menu", "logo"));
        m_gameLogo.setPosition(
                (context::getWindowSize().x - m_gameLogo.getGlobalBounds().width) / 2,
                (context::getWindowSize().y - m_gameLogo.getGlobalBounds().height) * 0.2f);
        m_UIelements.add("Continue", std::make_shared<ui::MenuButton>());
        m_UIelements.add("NewGame", std::make_shared<ui::MenuButton>());
        m_UIelements.add("Extra", std::make_shared<ui::MenuButton>());
        m_UIelements.add("Settings", std::make_shared<ui::MenuButton>());
        m_UIelements.add("Credits", std::make_shared<ui::MenuButton>());
        m_UIelements.add("Quit", std::make_shared<ui::MenuButton>());

        auto continueButton = m_UIelements.get<ui::MenuButton>("Continue");
        continueButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.6));
        continueButton->setLabel("Continue");
        continueButton->setDisabled();

        auto newGameButton = m_UIelements.get<ui::MenuButton>("NewGame");
        newGameButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.64));
        newGameButton->setLabel("New Game");

        auto extraButton = m_UIelements.get<ui::MenuButton>("Extra");
        extraButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.68));
        extraButton->setLabel("Extra");
        extraButton->setCallback([](){
            SceneManager::getInstance().setCurrentScene("AnimationEditor");
        });

        auto settingsButton = m_UIelements.get<ui::MenuButton>("Settings");
        settingsButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.72));
        settingsButton->setLabel("Settings");

        auto creditsButton = m_UIelements.get<ui::MenuButton>("Credits");
        creditsButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.76));
        creditsButton->setLabel("Credits");

        auto quitButton = m_UIelements.get<ui::MenuButton>("Quit");
        quitButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.8));
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
