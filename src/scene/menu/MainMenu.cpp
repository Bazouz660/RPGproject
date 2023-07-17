/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-09 20:21:12
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-18 00:25:33
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

        m_background.setFillColor(sf::Color(15, 15, 15, 255));
        m_gameLogo.setTexture(RESOURCE().getTexture("main_menu", "logo"));
        m_gameLogo.setPosition(
                (context::getWindowSize().x - m_gameLogo.getGlobalBounds().width) / 2,
                (context::getWindowSize().y - m_gameLogo.getGlobalBounds().height) * 0.2f);
        m_UIelements.add("PlayButton", std::make_shared<ui::MenuButton>());
        m_UIelements.add("QuitButton", std::make_shared<ui::MenuButton>());
        auto playButton = m_UIelements.get<ui::MenuButton>("PlayButton");
        playButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.7));
        playButton->setLabel("Play");
        playButton->setCallback([](){
            SceneManager::getInstance().setCurrentScene("AnimationEditor");
        });
        auto quitButton = m_UIelements.get<ui::MenuButton>("QuitButton");
        quitButton->setPosition(sf::Vector2f(context::getWindowSize().x / 2, context::getWindowSize().y * 0.75));
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
