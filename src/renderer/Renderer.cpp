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
        m_resolution = size;
        m_window.create(sf::VideoMode(size.x, size.y), title, style, settings);
        m_window.setPosition(sf::Vector2i(0, 0));
        m_staticView = m_window.getDefaultView();
        context::setStaticView(m_staticView);
        context::setContext(m_window, size);
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