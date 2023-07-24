/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "context.hpp"
#include "logger.hpp"
#include "parsing.hpp"
#include "effects.hpp"
#include "math.hpp"

namespace bya
{

    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
        if (m_window.isOpen())
            m_window.close();
    }

    void Renderer::init(sf::Vector2u size, const std::string &title, sf::Uint32 style, const sf::ContextSettings &settings)
    {
        m_window.create(sf::VideoMode(size.x, size.y), title, style, settings);
        m_window.setPosition(sf::Vector2i(0, 0));

        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Resized) {
                m_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
        }

        m_staticView = m_window.getView();
        context::setStaticView(m_staticView);
        context::setContext(m_window, m_window.getSize());
    }

    void Renderer::close()
    {
        logger::log("Stopping");
        m_window.close();
    }

    sf::RenderWindow &Renderer::getWindow()
    {
        return m_window;
    }

    sf::View &Renderer::getView()
    {
        return m_staticView;
    }

    bool Renderer::isOpen() const
    {
        return m_window.isOpen();
    }

}