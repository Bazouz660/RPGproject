/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** ResourceManager
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

namespace bya {

ResourceManager::ResourceManager()
{
    loadAssets();
}

void ResourceManager::loadAssets()
{
    // load default fonts
    loadFont("defaultFont", "asset/font/default/debug_font.ttf");

    // load game fonts
    loadFont("gameFont", "asset/font/game_font.ttf");

    // load default textures
    loadTexture("defaultButton", "asset/texture/default/button.png");
    loadTexture("defaultSliderWagon", "asset/texture/default/wagon.png");
    loadTexture("defaultSliderRail", "asset/texture/default/rail.png");

    // load game textures
    loadTexture("tileset", "asset/texture/tileset/dirt.png");

    // load effects textures
    loadTexture("smoke", "asset/texture/effect/smoke.png");

    // load armor textures
    loadTexture("steel_helm", "asset/texture/armor/steel_helm.png");

    // load body textures
    loadTexture("human_head1", "asset/texture/body/human/head1.png");
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

    std::cout << "Loaded texture as \"" << name << "\" from " << "\"" + filename + "\"" << std::endl;

    // Insert the texture into the map using the name as the key.
    m_textures[name] = texture;
}

sf::Texture& ResourceManager::getTexture(const std::string &name) {
    return *m_textures.at(name);
}

sf::Image& ResourceManager::getTextureImage(const std::string &name)
{
    if (m_images.find(name) == m_images.end()) {
        sf::Image image = m_textures.at(name)->copyToImage();
        m_images[name] = std::make_shared<sf::Image>(image);
    }
    return *m_images.at(name);
}

void ResourceManager::loadTexturesFromFolder(const std::string& directory)
{
    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
        loadTexture(removeExtension(entry.path().filename().string()), entry.path().string());
    }
}

void ResourceManager::loadFont(const std::string& name,
const std::string& filePath)
{
    std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
    if(!font->loadFromFile(filePath))
        throw std::runtime_error("Failed to load font: " + filePath);
    m_fonts[name] = font;
    std::cout << "Loaded font as \"" << name << "\" from " << "\"" + filePath + "\"" << std::endl;
}

sf::Font& ResourceManager::getFont(const std::string& fontName)
{
    return *m_fonts.at(fontName);
}

void ResourceManager::loadSoundBuffer(const std::string& name,
const std::string& fileName)
{
    std::shared_ptr<sf::SoundBuffer> soundBuffer = std::make_shared<sf::SoundBuffer>();
    if (!soundBuffer->loadFromFile(fileName))
        throw std::runtime_error("Failed to load sound buffer: " + fileName);
    m_soundBuffers[name] = soundBuffer;
    std::cout << "Loaded font as \"" << name << "\" from " << "\"" + fileName + "\"" << std::endl;
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& name) {
    auto it = m_soundBuffers.find(name);
    if (it == m_soundBuffers.end())
        throw std::runtime_error("Sound buffer not found: " + name);
    return *m_soundBuffers.at(name);
}

}