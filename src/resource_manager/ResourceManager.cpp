/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-06 22:23:37
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-10 22:54:41
 *  Description:
 */

#ifdef _WIN32
    #include <experimental/filesystem>
    #define OS "Windows"
    namespace std {
        namespace filesystem = experimental::filesystem;
    }
#else
    #include <filesystem>
    #define OS "Linux"
#endif

#include "ResourceManager.hpp"
#include "parsing.hpp"
#include "logger.hpp"

namespace bya {
    ResourceManager::ResourceManager()
    {
    }

    bool ResourceManager::isLoaded()
    {
        return m_loaded;
    }

    void ResourceManager::init()
    {
        m_loadingThread = std::thread(&ResourceManager::loadAssets, this);
        m_loadingThread.detach();
    }

    void ResourceManager::loadAssets()
    {
        // load game fonts
        loadFont("defaultFont", "asset/font/default/debug_font.ttf");
        loadFont("gameFont", "asset/font/game_font.ttf");

        loadTexturesFromFolder("asset/texture", true);
        m_loaded = true;
    }

    ResourceManager& ResourceManager::getInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    void ResourceManager::loadTexture(const std::string &filePath)
    {
        std::filesystem::path path(filePath);
        std::string fileName = parsing::removeExtension(path.filename().string());
        std::string directory = path.parent_path().string();
        std::string directoryName = path.parent_path().filename().string();

        // Create a new texture and load it from the specified file.
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        texture->loadFromFile(filePath);

        // try to find a texture map for the directory
        if (m_textures.find(directoryName) == m_textures.end()) {
            // if not found, create a new one
            m_textures[directoryName] = std::make_shared<TextureMap>();
        }

        // add the texture to the map if it doesn't already exist
        if (m_textures.at(directoryName)->find(fileName) == m_textures.at(directoryName)->end()) {
            m_textures[directoryName]->insert({fileName, texture});
        } else
            return;

        logger::log("Loaded texture as \"" + fileName + "\" from " + "\"" + filePath + "\"");
    }

    sf::Texture& ResourceManager::getTexture(const std::string& location, const std::string &name)
    {
        assertResourceExist(location, name, m_textures);
        return *m_textures.at(location)->at(name);
    }

    sf::Image& ResourceManager::getTextureImage(const std::string& location, const std::string &name)
    {
        auto& texture = getTexture(location, name);
        std::shared_ptr<sf::Image> image = std::make_shared<sf::Image>(m_textures.at(location)->at(name)->copyToImage());
        // add image to the map of ImageMap
        if (m_images.find(location) == m_images.end()) {
            // if not found, create a new one
            m_images[location] = std::make_shared<ImageMap>();
        }
        m_images[location]->insert({name, image});
        return *m_images.at(location)->at(name);
    }

    void ResourceManager::loadTexturesFromFolder(const std::string& directory, bool recursive)
    {
        std::filesystem::path path(directory);
        std::string directoryName = path.filename().string();

        // iterate over the directory
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            // if the entry is a directory and recursive is true, load textures from it

            if (std::filesystem::is_directory(entry) && recursive) {
                loadTexturesFromFolder(entry.path().string(), recursive);
            } else {
                // if the entry is a file, load it as a texture
                loadTexture(entry.path().string());
            }
        }
    }

    void ResourceManager::loadFont(const std::string& name,
    const std::string& filePath)
    {
        std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
        if(!font->loadFromFile(filePath))
            throw std::runtime_error("Failed to load font: " + filePath);
        m_fonts[name] = font;
        logger::log("Loaded font as \"" + name + "\" from " + "\"" + filePath + "\"");
    }

    sf::Font& ResourceManager::getFont(const std::string& fontName)
    {
        if (m_fonts.find(fontName) == m_fonts.end())
            throw std::runtime_error("Font not found: " + fontName);
        return *m_fonts.at(fontName);
    }

    void ResourceManager::loadSoundBuffer(const std::string& name,
    const std::string& fileName)
    {
        std::shared_ptr<sf::SoundBuffer> soundBuffer = std::make_shared<sf::SoundBuffer>();
        if (!soundBuffer->loadFromFile(fileName))
            throw std::runtime_error("Failed to load sound buffer: " + fileName);
        m_soundBuffers[name] = soundBuffer;
        logger::log("Loaded sound as \"" + name + "\" from " + "\"" + fileName + "\"");
    }

    sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& name) {
        auto it = m_soundBuffers.find(name);
        if (it == m_soundBuffers.end())
            throw std::runtime_error("Sound buffer not found: " + name);
        return *m_soundBuffers.at(name);
    }
}
