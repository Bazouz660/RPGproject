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
        m_window.create(sf::VideoMode(size.x, size.y), title, style, settings);
        m_window.setPosition(sf::Vector2i(0, 0));
        m_staticView = m_window.getDefaultView();

        logger::debug("size = x: " + std::to_string(size.x) + ", y: " + std::to_string(size.y));
        logger::debug("window size = x: " + std::to_string(m_window.getSize().x) + ", y: " + std::to_string(m_window.getSize().y));

        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Resized) {
                logger::debug("window resized");
                logger::debug("window size = x: " + std::to_string(m_window.getSize().x) + ", y: " + std::to_string(m_window.getSize().y));
                m_window.setSize(sf::Vector2u(size.x, size.y));
                m_staticView.setSize(size.x, size.y);
                m_window.setView(m_staticView);
                logger::debug("window size reset");
                logger::debug("window size = x: " + std::to_string(m_window.getSize().x) + ", y: " + std::to_string(m_window.getSize().y));
            }
        }

        float titleBarHeight = size.y - m_window.getSize().y;
        if (titleBarHeight > 0) {
            logger::debug("title bar height = " + std::to_string(titleBarHeight));
        }

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