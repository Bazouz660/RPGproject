/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

    #include "common.hpp"

    namespace bya {

    class IScene {
        public:
            virtual ~IScene() = default;
            virtual void load() = 0;
            virtual void close() = 0;
            virtual void reset() = 0;
            virtual void handleUIEvent(sf::Event& event, sf::RenderWindow& window) = 0;
            virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;
            virtual void updateUI(float dt) = 0;
            virtual void update(float dt) = 0;
            virtual void render(sf::RenderTarget& target) = 0;
            virtual void renderUi(sf::RenderTarget &target) = 0;
    };

    }

#endif /* !ISCENE_HPP_ */
