/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** AnimationEditor
*/

#include "AnimationEditor.hpp"
#include "info.hpp"

namespace bya {

        void AnimationEditor::init()
        {
            m_entity.loadFromJson("humanoid.json");

            m_entity.setPosition(info::getMousePosition());
        }

        void AnimationEditor::update(float dt)
        {
        }

        void AnimationEditor::render(sf::RenderTarget &target)
        {
        }
}