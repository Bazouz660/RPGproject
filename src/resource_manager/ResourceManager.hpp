/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-06 22:23:37
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-09 02:38:30
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
            void loadTexture(const std::string &filePath);

            void loadFont(const std::string& name, const std::string& filePath);
            void loadSoundBuffer(const std::string& name, const std::string& filePath);

            void loadTexturesFromFolder(const std::string& folderPath, bool recursive = false);

            sf::Texture& getTexture(const std::string& location, const std::string &name);
            sf::Font& getFont(const std::string& name);
            sf::SoundBuffer& getSoundBuffer(const std::string& name);
            sf::Image& getTextureImage(const std::string& location, const std::string& name);

        private:
            ResourceManager();
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            template<typename T>
            void assertResourceExist(const std::string& location, const std::string& name, const std::map<std::string, std::shared_ptr<T>>& map)
            {
                if (map.find(location) == map.end()) {
                    // check if the requested texture is in another ImageMap
                    for (auto& [location, imageMap] : m_images) {
                        if (imageMap->find(name) != imageMap->end()) {
                            throw std::runtime_error("Texture not found: [" + name + "] in [" + location + "] but found in [" + location + "]");
                        }
                    }
                    throw std::runtime_error("Texture not found: [" + name + "] in [" + location + "]");
                }
                if (map.at(location)->find(name) == map.at(location)->end()) {
                    // check if the requested texture is in another ImageMap
                    for (auto& [location, imageMap] : m_images) {
                        if (imageMap->find(name) != imageMap->end()) {
                            throw std::runtime_error("Texture not found: [" + name + "] in [" + location + "] but found in [" + location + "]");
                        }
                    }
                    throw std::runtime_error("Texture not found: [" + name + "] in [" + location + "]");
                }
            }

        private:
            typedef std::map<std::string, std::shared_ptr<sf::Texture>> TextureMap;
            typedef std::map<std::string, std::shared_ptr<sf::Font>> FontMap;
            typedef std::map<std::string, std::shared_ptr<sf::SoundBuffer>> SoundBufferMap;
            typedef std::map<std::string, std::shared_ptr<sf::Image>> ImageMap;

            bool m_loaded = false;
            std::thread m_loadingThread;

            std::map<std::string, std::shared_ptr<TextureMap>>  m_textures;
            std::map<std::string, std::shared_ptr<sf::Font>> m_fonts;
            std::map<std::string, std::shared_ptr<sf::SoundBuffer>> m_soundBuffers;
            std::map<std::string, std::shared_ptr<ImageMap>> m_images;
    };
}
