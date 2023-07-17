/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-15 02:09:27
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-15 16:15:54
 * @ Description:
 */

#include "MusicManager.hpp"
#include "Clock.hpp"

namespace bya {

    MusicManager& MusicManager::getInstance()
    {
        static MusicManager instance;
        instance.setMusicVolume(10.0f);
        return instance;
    }

    void MusicManager::fadeIn(float fadeTime)
    {
        m_fadeTimer += getClock().getFrameDt();

        float volume = m_fadeTimer / fadeTime * m_musicVolume;
        volume = std::clamp(volume, 0.0f, m_musicVolume);
        m_currentTrack->setVolume(volume);

        if (m_fadeTimer >= fadeTime) {
            m_fadingIn = false;
            m_fadeTimer = 0.0f;
        }
    }

    void MusicManager::fadeOut(float fadeTime)
    {
        m_fadeTimer += getClock().getFrameDt();

        float volume = m_fadeTimer / fadeTime * m_musicVolume;
        volume = std::clamp(volume, 0.0f, m_musicVolume);
        m_currentTrack->setVolume(m_musicVolume - volume);

        if (m_fadeTimer >= fadeTime) {
            m_fadingOut = false;
            m_fadeTimer = 0.0f;

            if (m_switchInfo.newTrackName == "") {
                m_currentTrack->pause();
                m_currentTrack = nullptr;
            }

            m_currentTrack->pause();
            m_currentTrack = m_musicMap[m_switchInfo.newTrackName];
            m_currentTrack->play();
            m_currentTrack->setLoop(m_switchInfo.loop);
            if (m_switchInfo.restart) {
                m_currentTrack->setPlayingOffset(sf::Time::Zero);
            }
        }
    }

    void MusicManager::update(float dt)
    {
        // update fading

        if (m_switching) {
            if (m_fadingOut)
                fadeOut(m_switchInfo.fadeTime);
            else if (m_fadingIn)
                fadeIn(m_switchInfo.fadeTime);
            else
                m_switching = false;
        }

    }

    void MusicManager::setMusicVolume(float volume)
    {
        m_musicVolume = volume;
        if (m_currentTrack != nullptr) {
            m_currentTrack->setVolume(volume);
        }
    }

    void MusicManager::pauseTrack(float fadeTime)
    {
        if (m_currentTrack == nullptr) {
            return;
        }

        m_switchInfo = { "", fadeTime, m_currentTrack->getLoop(), false };

        m_fadingOut = true;
        m_fadingIn = false;
        m_switching = true;
    }

    // switch track with fade in/out (gradually change volume)
    void MusicManager::switchTrack(const std::string& name, float fadeTime, bool loop, bool restart)
    {
        if (m_musicMap.find(name) == m_musicMap.end()) {
            logger::error("MusicManager::switchTrack: music not found: " + name);
            return;
        }

        m_switchInfo = { name, fadeTime, loop, restart };

        if (m_currentTrack == nullptr) {
            m_currentTrack = m_musicMap[name];
            m_currentTrack->play();
            m_currentTrack->setLoop(loop);
            return;
        }

        if (m_currentTrack == m_musicMap[name]) {
            if (restart) {
                m_currentTrack->setPlayingOffset(sf::Time::Zero);
                m_currentTrack->setLoop(loop);
            }
            return;
        }

        m_fadingOut = true;
        m_fadingIn = false;
        m_switching = true;
    }

    std::string MusicManager::getCurrentTrackName()
    {
        for (auto& [name, music] : m_musicMap) {
            if (m_currentTrack == music) {
                return name;
            }
        }

        return "";
    }

    sf::Music& MusicManager::getCurrentTrack()
    {
        return *m_currentTrack;
    }

    bool MusicManager::isPlaying(const std::string& name)
    {
        if (m_musicMap.find(name) == m_musicMap.end()) {
            logger::error("MusicManager::isPlaying: music not found: " + name);
            return false;
        }

        return m_musicMap[name]->getStatus() == sf::Music::Playing;
    }

    bool MusicManager::isPaused(const std::string& name)
    {
        if (m_musicMap.find(name) == m_musicMap.end()) {
            logger::error("MusicManager::isPaused: music not found: " + name);
            return false;
        }

        return m_musicMap[name]->getStatus() == sf::Music::Paused;
    }

    bool MusicManager::isStopped(const std::string& name)
    {
        if (m_musicMap.find(name) == m_musicMap.end()) {
            logger::error("MusicManager::isStopped: music not found: " + name);
            return false;
        }

        return m_musicMap[name]->getStatus() == sf::Music::Stopped;
    }

    void MusicManager::addTrack(const std::string& name, sf::Music* track)
    {
        if (m_musicMap.find(name) != m_musicMap.end()) {
            logger::error("MusicManager::addTrack: music already exists: " + name);
            return;
        }

        m_musicMap[name] = track;
    }

    bool MusicManager::isLoaded(const std::string& name)
    {
        return m_musicMap.find(name) != m_musicMap.end();
    }

}