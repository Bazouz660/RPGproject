/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** OrientedBoundingBox
*/

#include "OrientedBoundingBox.hpp"
#include "math.hpp"

static const float NORMAL_TOLERANCE = 0.0001f;

namespace bya::gameObj
{

    OrientedBoundingBox::OrientedBoundingBox()
    {
        m_vertexBuffer.create(5);
        m_vertexBuffer.setPrimitiveType(sf::PrimitiveType::LineStrip);
        m_vertexBuffer.setUsage(sf::VertexBuffer::Usage::Dynamic);
        m_originShape.setRadius(2);
        m_originShape.setFillColor(sf::Color::Blue);
        m_originShape.setOrigin(0.5f, 0.5f);
        m_pivotShape = m_originShape;
        m_pivotShape.setFillColor(sf::Color::Cyan);
    }

    OrientedBoundingBox::OrientedBoundingBox(
        sf::Vector2f position, sf::Vector2f size, float rotation
    ) : m_position(position), m_size(size), m_rotation(rotation)
    {
        OrientedBoundingBox();
        m_corners[0] = {0, 0};
        m_corners[1] = {m_size.x, 0};
        m_corners[2] = {m_size.x, m_size.y};
        m_corners[3] = {0, m_size.y};
    }

    void OrientedBoundingBox::setOrigin(sf::Vector2f origin)
    {
        m_origin = origin;
    }

    bool OrientedBoundingBox::intersects(OrientedBoundingBox &other) const
    {
        auto corners = getCorners();
        auto otherCorners = other.getCorners();

        for (auto &corner : corners) {
            if (other.contains(corner)) {
                return true;
            }
        }
        for (auto &corner : otherCorners) {
            if (contains(corner)) {
                return true;
            }
        }
        return false;
    }

    std::array<sf::Vector2f, 4> OrientedBoundingBox::getCorners() const
    {
        sf::Transform transform = sf::Transform::Identity;
        std::array<sf::Vector2f, 4> corners = {};
        // first rotate around the origin, then scale, then translate
        // translate to origin

        transform.rotate(m_rotation, m_origin);
        for (int i = 0; i < 4; i++)
            corners[i] = transform.transformPoint(m_corners[i]);

        transform = sf::Transform::Identity;
        transform.translate(m_origin);
        transform.scale(m_scale);
        transform.translate(-m_origin);
        for (int i = 0; i < 4; i++)
            corners[i] = transform.transformPoint(corners[i]);

        transform = sf::Transform::Identity;
        transform.translate(m_position - m_origin);
        for (int i = 0; i < 4; i++)
            corners[i] = transform.transformPoint(corners[i]);

        return corners;
    }

    bool OrientedBoundingBox::intersects(sf::FloatRect &other) const
    {
        auto corners = getCorners();
        sf::Vector2f topLeft = {other.left, other.top};
        sf::Vector2f topRight = {other.left + other.width, other.top};
        sf::Vector2f bottomLeft = {other.left, other.top + other.height};
        sf::Vector2f bottomRight = {other.left + other.width,
            other.top + other.height};
        if (contains(topLeft) || contains(topRight) || contains(bottomLeft) ||
            contains(bottomRight)) {
            return true;
        }
        if (other.contains(corners[0]) || other.contains(corners[1]) ||
            other.contains(corners[2]) || other.contains(corners[3])) {
            return true;
        }
        return false;
    }

    bool OrientedBoundingBox::contains(const sf::Vector2f& point) const
    {
        auto corners = getCorners();
        auto v1 = corners[0] - point;
        auto v2 = corners[1] - point;
        auto v3 = corners[2] - point;
        auto v4 = corners[3] - point;
        auto cross1 = math::cross(v1, v2);
        auto cross2 = math::cross(v2, v3);
        auto cross3 = math::cross(v3, v4);
        auto cross4 = math::cross(v4, v1);
        return (cross1 > 0 && cross2 > 0 && cross3 > 0 && cross4 > 0) ||
            (cross1 < 0 && cross2 < 0 && cross3 < 0 && cross4 < 0);
    }

    void OrientedBoundingBox::setSize(sf::Vector2f size)
    {
        m_size = size;
        m_corners[0] = {0, 0};
        m_corners[1] = {m_size.x, 0};
        m_corners[2] = {m_size.x, m_size.y};
        m_corners[3] = {0, m_size.y};
    }

    sf::Vector2f OrientedBoundingBox::getCenter() const
    {
        auto corners = getCorners();
        return (corners[0] + corners[2]) / 2.f;
    }

    void OrientedBoundingBox::render(sf::RenderTarget &target)
    {
        auto corners = getCorners();

        m_vertices[0].position = corners[0];
        m_vertices[1].position = corners[1];
        m_vertices[2].position = corners[2];
        m_vertices[3].position = corners[3];
        m_vertices[4].position = corners[0];

        m_vertices[0].color = m_color;
        m_vertices[1].color = m_color;
        m_vertices[2].color = m_color;
        m_vertices[3].color = m_color;
        m_vertices[4].color = m_color;

        m_vertexBuffer.update(m_vertices, 5, 0);
        target.draw(m_vertexBuffer);
        m_originShape.setPosition(getCenter());
        m_pivotShape.setPosition(m_position);
        target.draw(m_originShape);
        target.draw(m_pivotShape);
    }
}