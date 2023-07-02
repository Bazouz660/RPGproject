/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
    #define ENGINE_HPP_

    #include "common.hpp"
    #include "SceneManager.hpp"
    #include "Renderer.hpp"

    namespace bya {
        class Engine {
            public:
                Engine();
                ~Engine();
                void init();
                void run();

            private:
                sf::Event m_event;
                Renderer m_renderer;
                SceneManager& m_sceneManager;
                sf::Text m_fpsHint;

            private:
                void handleEvents();
                void render();
                void update();
                void updateFpsHint();
        };
    }

#endif /* !ENGINE_HPP_ */
