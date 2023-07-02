/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "info.hpp"

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

    void Renderer::init(sf::Vector2u size, const std::string &title, sf::Uint32 style)
    {
        m_window.create(sf::VideoMode(size.x, size.y), title, style);
        m_staticView = m_window.getDefaultView();
        info::setStaticView(m_staticView);
        info::setContext(m_window);
    }

    void Renderer::init(int width, int height, const std::string &title, sf::Uint32 style)
    {
        m_window.create(sf::VideoMode(width, height), title, style);
        m_staticView = m_window.getDefaultView();
        info::setContext(m_window);
    }

    void Renderer::close()
    {
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