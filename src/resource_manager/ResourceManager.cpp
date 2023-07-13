/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-06 22:23:37
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-10 22:54:41
 *  Description:
 */

#include "ResourceManager.hpp"

namespace bya {

    ResourceManager& ResourceManager::getInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    void ResourceManager::init()
    {
        m_loadingThread = std::thread(&ResourceManager::loadAssets, this);
        m_loadingThread.detach();
    }

    void ResourceManager::loadAssets()
    {
        // load game fonts
        loadResource<sf::Font>("asset/font/default/debug_font.ttf");
        loadResource<sf::Font>("asset/font/game_font.ttf");

        loadFromFolder<sf::Texture>("asset/texture", true);
        m_loaded = true;
    }

    sf::Image& ResourceManager::getTextureImage(const std::string& location, const std::string &name)
    {
        auto& texture = getTexture(location, name);
        std::shared_ptr<sf::Image> image = std::make_shared<sf::Image>(m_textures.at(location)->at(name)->copyToImage());
        if (m_images.find(location) == m_images.end())
            m_images[location] = std::make_shared<ResourceMap<sf::Image>>();
        m_images[location]->insert({name, image});
        return *m_images.at(location)->at(name);
    }




    sf::Texture& ResourceManager::getTexture(const std::string& location, const std::string &name)
    {
        return getResourceInternal<sf::Texture>(location, name);
    }

    sf::Font& ResourceManager::getFont(const std::string& location, const std::string& fontName)
    {
        return getResourceInternal<sf::Font>(location, fontName);
    }

    sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& location, const std::string& name)
    {
        return getResourceInternal<sf::SoundBuffer>(location, name);
    }
}
