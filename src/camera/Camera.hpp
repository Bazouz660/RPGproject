/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-03 18:50:24
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-06 21:37:47
 *  Description:
 */

#pragma once

#include "common.hpp"

namespace bya {

class Camera {
    public:
        Camera();
        ~Camera();
        void activate();
        void update(float dt);
        void setLetterbox(int width, int height);
        void setRect(sf::IntRect rect);
        void setCenter(sf::Vector2f center);
        void setCenter(float x, float y);
        void setZoom(float zoom);
        void setRotation(float rotation);
        void move(sf::Vector2f offset);
        void move(float x, float y);
        void zoom(float zoom);
        void rotate(float rotation);
        void reset();
        void shake(float intensity);
        void setSpeed(float speed);
        float getSpeed() const;
        sf::Vector2f getCenter() const;
        float getZoom() const;
        float getRotation() const;
        sf::View getView() const;
        bool isActive() const;
    private:
        sf::View m_view;
        sf::Vector2f m_baseSize;
        sf::Vector2f m_acceleration;
        float m_speed;
        sf::Vector2f m_maxZoom;
        float m_zoom;
};

}