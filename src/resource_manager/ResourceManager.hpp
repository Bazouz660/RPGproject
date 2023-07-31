/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-06 22:23:37
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-15 03:01:33
 *  Description:
 */

#pragma once

#include <filesystem>

#include <thread>
#include <mutex>

#include "common.hpp"
#include "MusicManager.hpp"
#include "parsing.hpp"
#include "logger.hpp"

#define RESOURCE() ResourceManager::getInstance()

namespace bya {

    class ResourceManager {
        public:
            static ResourceManager& getInstance();
            void init();
            void loadAssets();
            bool isLoaded() const { return m_loaded; }

            sf::Texture& getTexture(const std::string& location, const std::string &name);
            sf::Font& getFont(const std::string& location, const std::string& name);
            sf::SoundBuffer& getSoundBuffer(const std::string& location, const std::string& name);
            sf::Image& getTextureImage(const std::string& location, const std::string& name);

            template<typename T>
            void loadFromFolder(const std::string& folderPath, bool recursive = false)
            {
                auto& map = getMap<T>();
                std::filesystem::path path(folderPath);
                std::string directoryName = path.filename().string();

                // iterate over the directory
                for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
                    // if the entry is a directory and recursive is true, load textures from it

                    if (std::filesystem::is_directory(entry) && recursive) {
                        loadFromFolder<T>(entry.path().string(), recursive);
                    } else {
                        // if the entry is a file, load it as a texture
                        loadResource<T>(entry.path().string());
                    }
                }
            }

            template<typename T>
            bool loadResource(const std::string& filePath)
            {
                std::lock_guard<std::mutex> lock(m_loadMutex);
                auto& map = getMap<T>();
                std::filesystem::path path(filePath);
                std::string fileName = parsing::removeExtension(path.filename().string());
                std::string directory = path.parent_path().string();
                std::string directoryName = path.parent_path().filename().string();

                int status = 0;
                std::shared_ptr<T> resource = std::make_shared<T>();
                if constexpr (std::is_same_v<T, sf::Music>) {
                    // check if the music is already loaded
                    if (MusicManager::getInstance().isLoaded(fileName))
                        return false;
                    status = resource->openFromFile(filePath);
                    resource->setVolume(MusicManager::getInstance().getMusicVolume());
                    MusicManager::getInstance().addTrack(fileName, resource.get());
                } else
                    status = resource->loadFromFile(filePath);
                if (status == -1)
                    THROW("Failed to load resource: " + filePath);

                if (map.find(directoryName) == map.end())
                    map[directoryName] = std::make_shared<ResourceMap<T>>();
                if (map.at(directoryName)->find(fileName) == map.at(directoryName)->end()) {
                    map[directoryName]->insert({fileName, resource});
                } else
                    return false;
                return true;
            }

        private:
            ResourceManager() = default;
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            template<typename T>
            using ResourceMap = std::map<std::string, std::shared_ptr<T>>;
            template<typename T>
            using ResourceMultimap = std::map<std::string, std::shared_ptr<ResourceMap<T>>>;

            // generic get resource function
            template<typename T>
            T& getResourceInternal(const std::string& location, const std::string& name)
            {
                auto& map = getMap<T>();
                assertResourceExist<T>(location, name);
                return *map.at(location)->at(name);
            }

            template<typename ResourceType>
            ResourceMultimap<ResourceType>& getMap()
            {
                if constexpr (std::is_same_v<ResourceType, sf::Texture>) {
                    return m_textures;
                } else if constexpr (std::is_same_v<ResourceType, sf::Font>) {
                    return m_fonts;
                } else if constexpr (std::is_same_v<ResourceType, sf::SoundBuffer>) {
                    return m_soundBuffers;
                } else if constexpr (std::is_same_v<ResourceType, sf::Image>) {
                    return m_images;
                } else if constexpr (std::is_same_v<ResourceType, sf::Music>) {
                    return m_musics;
                } else {
                    THROW("Unknown resource type");
                }
            }

            template<typename T>
            void assertResourceExist(const std::string& location, const std::string& name)
            {
                auto& map = getMap<T>();
                if (map.find(location) == map.end()) {
                    // check if the requested texture is in another ImageMap
                    for (auto& [location, imageMap] : m_images) {
                        if (imageMap->find(name) != imageMap->end()) {
                            THROW("Texture not found: [" + name + "] in [" + location + "] but found in [" + location + "]");
                        }
                    }
                    THROW("Texture not found: [" + name + "] in [" + location + "]");
                }
                if (map.at(location)->find(name) == map.at(location)->end()) {
                    // check if the requested texture is in another ImageMap
                    for (auto& [location, imageMap] : m_images) {
                        if (imageMap->find(name) != imageMap->end()) {
                            THROW("Texture not found: [" + name + "] in [" + location + "] but found in [" + location + "]");
                        }
                    }
                    THROW("Texture not found: [" + name + "] in [" + location + "]");
                }
            }

        private:
            bool m_loaded = false;
            std::thread m_loadingThread;
            std::mutex m_loadMutex;

            ResourceMultimap<sf::Texture> m_textures;
            ResourceMultimap<sf::Font> m_fonts;
            ResourceMultimap<sf::SoundBuffer> m_soundBuffers;
            ResourceMultimap<sf::Image> m_images;
            ResourceMultimap<sf::Music> m_musics;
    };
}
