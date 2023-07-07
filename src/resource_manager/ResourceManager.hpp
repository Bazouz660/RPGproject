/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-06 22:23:37
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-07 02:16:15
 *  Description:
 */

#pragma once

#include <thread>
#include "common.hpp"

#define getResource() ResourceManager::getInstance()

namespace bya {

    class ResourceManager {
        public:
            bool isLoaded();
            static ResourceManager& getInstance();
            void init();
            void loadAssets();
            sf::Texture& getTexture(const std::string &name);
            sf::Font& getFont(const std::string& name);
            sf::SoundBuffer& getSoundBuffer(const std::string& name);
            sf::Image& getTextureImage(const std::string& name);
        private:
            bool m_loaded = false;
            std::thread m_loadingThread;
            void loadTexture(const std::string &name, const std::string &filename);
            void loadTexturesFromFolder(const std::string &folder);
            void loadFont(const std::string& name, const std::string& filePath);
            void loadSoundBuffer(const std::string& name, const std::string& filePath);
            std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
            std::map<std::string, std::shared_ptr<sf::Font>> m_fonts;
            std::map<std::string, std::shared_ptr<sf::SoundBuffer>> m_soundBuffers;
            std::map<std::string, std::shared_ptr<sf::Image>> m_images;
            ResourceManager();
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;
    };
}
