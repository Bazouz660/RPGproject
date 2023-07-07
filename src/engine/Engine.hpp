/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-03 18:50:24
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-07 02:29:41
 *  Description:
 */

#ifndef ENGINE_HPP_
    #define ENGINE_HPP_

    #include "common.hpp"
    #include "SceneManager.hpp"
    #include "Renderer.hpp"

    namespace bya {
        class Engine {
            public:
                ~Engine();
                static Engine& getInstance();
                void preProcessor();
                void init();
                void run();
                void setIcon(const std::string& name);

            private:
                sf::Event m_event;
                Renderer m_renderer;
                SceneManager& m_sceneManager;
                sf::Text m_fpsHint;

            private:
                Engine();
                void handleEvents();
                void render();
                void update();
                void updateFpsHint();
        };
    }

#endif /* !ENGINE_HPP_ */
