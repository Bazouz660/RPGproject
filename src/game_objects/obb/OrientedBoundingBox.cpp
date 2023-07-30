/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** OrientedBoundingBox
*/

#include "OrientedBoundingBox.hpp"
#include "math.hpp"

namespace bya::gameObj
{

    OrientedBoundingBox::OrientedBoundingBox()
    {
        m_vertexBuffer.create(5);
        m_vertexBuffer.setPrimitiveType(sf::PrimitiveType::Quads);
        m_vertexBuffer.setUsage(sf::VertexBuffer::Usage::Dynamic);
        m_originShape.setRadius(2);
        m_originShape.setFillColor(sf::Color::Blue);
        m_originShape.setOrigin(0.5f, 0.5f);
        m_pivotShape = m_originShape;
        m_pivotShape.setFillColor(sf::Color::Cyan);
    }

    OrientedBoundingBox::OrientedBoundingBox(
        const sf::Vector2f& position, const sf::Vector2f& size, float rotation
    )
    {
        OrientedBoundingBox();
        m_corners[0] = {0, 0};
        m_corners[1] = {m_size.x, 0};
        m_corners[2] = {m_size.x, m_size.y};
        m_corners[3] = {0, m_size.y};
        setSize(size);
        setPosition(position);
        setRotation(rotation);
    }

    bool OrientedBoundingBox::intersects(const OrientedBoundingBox &other) const
    {
        auto corners = getGlobalCorners();
        auto otherCorners = other.getGlobalCorners();

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

    void OrientedBoundingBox::updateTransform()
    {
        sf::Transform transform = sf::Transform::Identity;

        transform.rotate(getRotation(), getOrigin());

        for (int i = 0; i < 4; i++)
            m_transformedCorners[i] = transform.transformPoint(m_corners[i]);

        transform = sf::Transform::Identity;
        transform.translate(getOrigin());
        transform.scale(getScale());
        transform.translate(-getOrigin());
        for (int i = 0; i < 4; i++)
            m_transformedCorners[i] = transform.transformPoint(m_transformedCorners[i]);

        transform = sf::Transform::Identity;
        transform.translate(getPosition() - getOrigin());
        for (int i = 0; i < 4; i++)
            m_transformedCorners[i] = transform.transformPoint(m_transformedCorners[i]);
    }

    bool OrientedBoundingBox::intersects(const sf::FloatRect &other) const
    {
        auto corners = getGlobalCorners();
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
        auto corners = getGlobalCorners();
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

    void OrientedBoundingBox::setSize(const sf::Vector2f& size)
    {
        m_size = size;
        m_corners[0] = {0, 0};
        m_corners[1] = {m_size.x, 0};
        m_corners[2] = {m_size.x, m_size.y};
        m_corners[3] = {0, m_size.y};
        updateTransform();
    }

    sf::Vector2f OrientedBoundingBox::getGlobalCenter() const
    {
        auto corners = getGlobalCorners();
        return (corners[0] + corners[2]) / 2.f;
    }

    sf::Vector2f OrientedBoundingBox::getLocalCenter() const
    {
        return m_size / 2.f;
    }

    void OrientedBoundingBox::render(sf::RenderTarget &target)
    {
        auto corners = getGlobalCorners();

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
        target.draw(m_vertexBuffer, m_renderStates);
        m_originShape.setPosition(getGlobalCenter());
        m_pivotShape.setPosition(getPosition());
        target.draw(m_originShape);
        target.draw(m_pivotShape);

        if (!m_showOutline)
            return;
        sf::VertexArray outline(sf::PrimitiveType::LinesStrip, 5);
        outline[0].position = corners[0];
        outline[1].position = corners[1];
        outline[2].position = corners[2];
        outline[3].position = corners[3];
        outline[4].position = corners[0];
        outline[0].color = m_outlineColor;
        outline[1].color = m_outlineColor;
        outline[2].color = m_outlineColor;
        outline[3].color = m_outlineColor;
        outline[4].color = m_outlineColor;
        target.draw(outline);
    }

    void OrientedBoundingBox::updateTexCoords()
    {
        sf::Vector2f size(m_textureRect.width, m_textureRect.height);
        sf::Vector2f offset(m_textureRect.left, m_textureRect.top);

        m_vertices[0].texCoords = offset;
        m_vertices[1].texCoords = offset + sf::Vector2f(size.x, 0);
        m_vertices[2].texCoords = offset + size;
        m_vertices[3].texCoords = offset + sf::Vector2f(0, size.y);
        m_vertices[4].texCoords = offset;
    }

    void OrientedBoundingBox::setTexture(sf::Texture &texture)
    {
        m_texture = &texture;
        m_textureRect = {0, 0, (int)m_texture->getSize().x, (int)m_texture->getSize().y};
        m_renderStates.texture = m_texture;
        updateTexCoords();
    }

    void OrientedBoundingBox::setTextureRect(const sf::IntRect& textureRect)
    {
        m_textureRect = textureRect;
        updateTexCoords();
    }

    sf::FloatRect OrientedBoundingBox::getBounds() const
    {
        auto corners = getGlobalCorners();
        float left = corners[0].x;
        float top = corners[0].y;
        float right = corners[0].x;
        float bottom = corners[0].y;
        for (int i = 1; i < 4; i++) {
            if (corners[i].x < left) {
                left = corners[i].x;
            }
            if (corners[i].x > right) {
                right = corners[i].x;
            }
            if (corners[i].y < top) {
                top = corners[i].y;
            }
            if (corners[i].y > bottom) {
                bottom = corners[i].y;
            }
        }
        return {left, top, right - left, bottom - top};
    }

    void OrientedBoundingBox::setOrigin(const sf::Vector2f& origin)
    {
        sf::Transformable::setOrigin(origin);
        updateTransform();
    }

    void OrientedBoundingBox::setPosition(const sf::Vector2f& position)
    {
        sf::Transformable::setPosition(position);
        updateTransform();
    }

    void OrientedBoundingBox::setRotation(float rotation)
    {
        sf::Transformable::setRotation(rotation);
        updateTransform();
    }

    void OrientedBoundingBox::setScale(const sf::Vector2f& scale)
    {
        sf::Transformable::setScale(scale);
        updateTransform();
    }

    sf::Vector2f OrientedBoundingBox::transformPoint(const sf::Vector2f& point) const
    {
        sf::Transform transform = sf::Transform::Identity;
        sf::Vector2f transformedPoint = point;

        transform.rotate(getRotation(), getOrigin());

        transformedPoint = transform.transformPoint(transformedPoint);

        transform = sf::Transform::Identity;
        transform.translate(getOrigin());
        transform.scale(getScale());
        transform.translate(-getOrigin());

        transformedPoint = transform.transformPoint(transformedPoint);

        transform = sf::Transform::Identity;
        transform.translate(getPosition() - getOrigin());

        transformedPoint = transform.transformPoint(transformedPoint);
        return transformedPoint;
    }
}