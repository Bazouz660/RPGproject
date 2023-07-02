/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Camera
*/

#include "Camera.hpp"
#include "effects.hpp"
#include "info.hpp"

namespace bya {

    Camera::Camera()
    {
        sf::Vector2u wSize = info::getWindowSize();
        m_view = sf::View(sf::FloatRect(0, 0, wSize.x, wSize.y));
        setLetterbox(wSize.x, wSize.y);
        m_baseSize.x = wSize.x;
        m_baseSize.y = wSize.y;
        m_zoom = 0.99;
        m_maxZoom = {0.2, 3};
        m_speed = 100;
    }

    Camera::~Camera()
    {
    }

    void Camera::activate()
    {
        info::getWindowInstance()->setView(m_view);
    }

    bool Camera::isActive() const
    {
        return &info::getWindowInstance()->getView() == &m_view;
    }

    void Camera::setRect(sf::IntRect rect)
    {
        m_view.reset(sf::FloatRect(rect));
        m_baseSize.x = rect.width;
        m_baseSize.y = rect.height;
    }

    void Camera::setCenter(sf::Vector2f center)
    {
        m_view.setCenter(center);
    }

    void Camera::setCenter(float x, float y)
    {
        m_view.setCenter(x, y);
    }

    void Camera::setZoom(float zoom)
    {
        m_zoom = zoom;
        if (m_zoom < m_maxZoom.x)
            m_zoom = m_maxZoom.x;
        if (m_zoom > m_maxZoom.y)
            m_zoom = m_maxZoom.y;
    }

    void Camera::setRotation(float rotation)
    {
        m_view.setRotation(rotation);
    }

    void Camera::move(sf::Vector2f offset)
    {
        m_acceleration = offset;
    }

    void Camera::move(float x, float y)
    {
        m_acceleration = sf::Vector2f(x, y);
    }

    void Camera::zoom(float zoom)
    {
        m_zoom += zoom;
        if (m_zoom < m_maxZoom.x)
            m_zoom = m_maxZoom.x;
        if (m_zoom > m_maxZoom.y)
            m_zoom = m_maxZoom.y;
    }

    void Camera::rotate(float rotation)
    {
        m_view.rotate(rotation);
    }

    void Camera::reset()
    {
        sf::Vector2u wSize = info::getWindowSize();
        m_view.reset(sf::FloatRect(0, 0, wSize.x, wSize.y));
        m_baseSize.x = wSize.x;
        m_baseSize.y = wSize.y;
        m_zoom = 1;
        m_view.setRotation(0);
    }

    sf::Vector2f Camera::getCenter() const
    {
        return m_view.getCenter();
    }

    float Camera::getZoom() const
    {
        return m_zoom;
    }

    float Camera::getRotation() const
    {
        return m_view.getRotation();
    }

    sf::View Camera::getView() const
    {
        return m_view;
    }

    void Camera::setLetterbox(int width, int height)
    {
        m_view = effects::getLetterboxView(m_view, width, height);
        m_baseSize.x = width;
        m_baseSize.y = height;
    }

    void Camera::update(float dt)
    {
        m_view.setSize(m_baseSize.x * m_zoom, m_baseSize.y * m_zoom);
        m_view.move((m_acceleration * m_speed) * dt);
        m_acceleration = sf::Vector2f(0, 0);
        info::getWindowInstance()->setView(m_view);
    }

    void Camera::shake(float intensity)
    {
        m_view.setCenter(m_view.getCenter() + sf::Vector2f(rand() % (int)intensity - intensity / 2,
            rand() % (int)intensity - intensity / 2));
    }

    void Camera::setSpeed(float speed)
    {
        m_speed = speed;
    }

    float Camera::getSpeed() const
    {
        return m_speed;
    }
}