/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-06 22:23:37
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-10 01:57:18
 *  Description:
 */

#ifdef _WIN32
    #include <experimental/filesystem>
    namespace std {
        namespace filesystem = experimental::filesystem;
    }
#else
    #include <filesystem>
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

        // load default textures
        loadTexture("defaultButton", "asset/texture/default/button.png");
        loadTexture("defaultSliderWagon", "asset/texture/default/wagon.png");
        loadTexture("defaultSliderRail", "asset/texture/default/rail.png");
        loadTexture("logo", "asset/texture/gui/main_menu/logo.png");

        // load game textures
        loadTexture("tileset", "asset/texture/tileset/dirt.png");

        // load gui textures
        loadTexture("editor_add_part", "asset/texture/gui/model_editor/add_part.png");

        // load effects textures
        loadTexture("smoke", "asset/texture/effect/smoke.png");

        // load armor textures
        loadTexture("steel_helm", "asset/texture/armor/steel_helm.png");

        // load body textures
        loadTexture("human_head1", "asset/texture/body/human/head1.png");
        m_loaded = true;
    }

    ResourceManager& ResourceManager::getInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    void ResourceManager::loadTexture(const std::string &name, const std::string &filename)
    {
        // Create a new texture and load it from the specified file.
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        texture->loadFromFile(filename);

        logger::log("Loaded texture as \"" + name + "\" from " + "\"" + filename + "\"");

        // Insert the texture into the map using the name as the key.
        m_textures[name] = texture;
    }

    sf::Texture& ResourceManager::getTexture(const std::string &name) {
        if (m_textures.find(name) == m_textures.end())
            throw std::runtime_error("Texture not found: " + name);
        return *m_textures.at(name);
    }

    sf::Image& ResourceManager::getTextureImage(const std::string &name)
    {
        if (m_images.find(name) == m_images.end()) {
            if (m_textures.find(name) == m_textures.end())
                throw std::runtime_error("Texture not found: " + name);
            sf::Image image = m_textures.at(name)->copyToImage();
            m_images[name] = std::make_shared<sf::Image>(image);
        }
        return *m_images.at(name);
    }

    void ResourceManager::loadTexturesFromFolder(const std::string& directory)
    {
        for (const auto &entry : std::filesystem::directory_iterator(directory)) {
            loadTexture(parsing::removeExtension(entry.path().filename().string()), entry.path().string());
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
