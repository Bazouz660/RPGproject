/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

namespace bya {

    SceneManager::SceneManager()
    {
        m_currentScene = nullptr;
    }

    SceneManager& SceneManager::getInstance()
    {
        static SceneManager instance;
        return instance;
    }

    std::shared_ptr<IScene> SceneManager::at(const std::string& identifier)
    {
        return m_scenes.at(identifier);
    }

    void SceneManager::addScene(const std::string& identifier, std::shared_ptr<IScene> scene)
    {
        m_scenes.insert(std::make_pair(identifier, scene));
    }

    void SceneManager::setCurrentScene(const std::string& identifier)
    {
        if (m_currentScene)
            m_currentScene->close();
        m_currentScene = m_scenes.at(identifier);
        m_currentScene->init();
    }

    std::shared_ptr<IScene> SceneManager::getCurrentScene()
    {
        return m_currentScene;
    }

}
