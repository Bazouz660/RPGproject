/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-15 02:00:21
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-15 03:02:48
 * @ Description:
 */

#pragma once

#include "common.hpp"

#include "logger.hpp"
#include "parsing.hpp"

namespace bya {

    class MusicManager {
        public:
            static MusicManager& getInstance();

            void switchTrack(const std::string& name, float fadeTime, bool loop, bool restart = false);
            void pauseTrack(float fadeTime);

            std::string getCurrentTrackName();
            sf::Music& getCurrentTrack();

            bool isPlaying(const std::string& name);
            bool isPaused(const std::string& name);
            bool isStopped(const std::string& name);

            void addTrack(const std::string& name, sf::Music* track);

            void setMusicVolume(float volume);
            float getMusicVolume() { return m_musicVolume; }

            void update(float dt);

            bool isLoaded(const std::string& name);

        private:
            struct SwitchInfo {
                std::string newTrackName;
                float fadeTime;
                bool loop;
                bool restart;
            } m_switchInfo;

            MusicManager() = default;
            ~MusicManager() = default;

            void fadeIn(float fadeTime);
            void fadeOut(float fadeTime);

            float m_fadeTimer = 0.f;
            bool m_fadingOut = false;
            bool m_fadingIn = false;
            bool m_switching = false;

            float m_musicVolume = 100.0f;

            std::map<std::string, sf::Music*> m_musicMap;
            sf::Music* m_currentTrack;
    };

}