/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** TilemapScene
*/

#ifndef TESTSCENE_HPP_
    #define TESTSCENE_HPP_

    #include "IScene.hpp"
    #include "Tilemap.hpp"
    #include "Camera.hpp"

    namespace bya {

    class TilemapScene : public IScene {
        public:
            TilemapScene();
            virtual ~TilemapScene() override;
            virtual void init() override;
            virtual void close() override;
            virtual void reset() override;
            virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
            virtual void update(float dt) override;
            virtual void render(sf::RenderTarget& target) override;
        private:
            Tilemap m_tilemap;
            Camera m_camera;
    };

    }

#endif /* !TESTSCENE_HPP_ */
