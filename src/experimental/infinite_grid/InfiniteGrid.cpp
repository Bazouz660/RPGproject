/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** InfiniteGrid
*/

#include "InfiniteGrid.hpp"

namespace bya {

    InfiniteGrid::InfiniteGrid(const sf::Vector2u& cellSize)
    {
        m_cellSize = cellSize;
        m_vertices.setPrimitiveType(sf::Lines);
        m_vertices.resize(0);
        sf::Vector2f viewSize = info::getWindowInstance()->getView().getSize();
        sf::Vector2f viewCenter = info::getWindowInstance()->getView().getCenter();

        for (float x = viewCenter.x - viewSize.x / 2; x < viewCenter.x + viewSize.x / 2; x += m_cellSize.x) {
            m_vertices.append(sf::Vertex(sf::Vector2f(x, viewCenter.y - viewSize.y / 2), sf::Color::White));
            m_vertices.append(sf::Vertex(sf::Vector2f(x, viewCenter.y + viewSize.y / 2), sf::Color::White));
        }

        for (float y = viewCenter.y - viewSize.y / 2; y < viewCenter.y + viewSize.y / 2; y += m_cellSize.y) {
            m_vertices.append(sf::Vertex(sf::Vector2f(viewCenter.x - viewSize.x / 2, y), sf::Color::White));
            m_vertices.append(sf::Vertex(sf::Vector2f(viewCenter.x + viewSize.x / 2, y), sf::Color::White));
        }
    }

    InfiniteGrid::~InfiniteGrid()
    {
    }

    void InfiniteGrid::update(float dt)
    {
        static bool first = true;

        m_vertices.clear();
        sf::Vector2f viewSize = info::getWindowInstance()->getView().getSize();
        sf::Vector2f viewCenter = info::getWindowInstance()->getView().getCenter();
        if (first) {
            m_lastViewCenter = viewCenter;
            m_lastViewSize = viewSize;
            first = false;
        }

        // find the offset between the last view center and the current one to apply an illusion of movement
        sf::Vector2f viewCenterOffset = m_lastViewCenter - viewCenter;
        sf::Vector2f viewSizeOffset = m_lastViewSize - viewSize;

        m_positionOffset += viewCenterOffset;
        m_positionOffset -= viewSizeOffset / 2.f;

        // loop the position offset
        if (m_positionOffset.x > m_cellSize.x)
            m_positionOffset.x -= m_cellSize.x;
        else if (m_positionOffset.x < 0)
            if (m_positionOffset.x < -m_cellSize.x)
                m_positionOffset.x += m_cellSize.x;
        if (m_positionOffset.y > m_cellSize.y)
            m_positionOffset.y -= m_cellSize.y;
        else if (m_positionOffset.y < 0)
            if (m_positionOffset.y < -m_cellSize.y)
                m_positionOffset.y += m_cellSize.y;


        // append the new vertices (with 1 more cell on each side to avoid flickering), the center of the view is the origin
        for (float x = viewCenter.x - viewSize.x / 2 - m_cellSize.x; x < viewCenter.x + viewSize.x / 2 + m_cellSize.x; x += m_cellSize.x) {
            m_vertices.append(sf::Vertex(sf::Vector2f(x, viewCenter.y - viewSize.y / 2 - m_cellSize.y) + m_positionOffset, sf::Color::White));
            m_vertices.append(sf::Vertex(sf::Vector2f(x, viewCenter.y + viewSize.y / 2 + m_cellSize.y) + m_positionOffset, sf::Color::White));
        }

        for (float y = viewCenter.y - viewSize.y / 2 - m_cellSize.y; y < viewCenter.y + viewSize.y / 2 + m_cellSize.y; y += m_cellSize.y) {
            m_vertices.append(sf::Vertex(sf::Vector2f(viewCenter.x - viewSize.x / 2 - m_cellSize.x, y) + m_positionOffset, sf::Color::White));
            m_vertices.append(sf::Vertex(sf::Vector2f(viewCenter.x + viewSize.x / 2 + m_cellSize.x, y) + m_positionOffset, sf::Color::White));
        }

        m_lastViewCenter = viewCenter;
        m_lastViewSize = viewSize;
    }

    void InfiniteGrid::render(sf::RenderTarget& target) const
    {
        target.draw(m_vertices);
    }

    bool InfiniteGrid::isCellVisible(const sf::Vector2f& cellPos) const
    {
        sf::Vector2f viewSize = info::getWindowInstance()->getView().getSize();
        sf::Vector2f viewCenter = info::getWindowInstance()->getView().getCenter();

        if (cellPos.x < viewCenter.x - viewSize.x / 2 - m_cellSize.x || cellPos.x > viewCenter.x + viewSize.x / 2 + m_cellSize.x)
            return false;
        if (cellPos.y < viewCenter.y - viewSize.y / 2 - m_cellSize.y || cellPos.y > viewCenter.y + viewSize.y / 2 + m_cellSize.y)
            return false;
        return true;
    }

    void InfiniteGrid::setCellSize(const sf::Vector2u& cellSize)
    {
        m_cellSize = cellSize;
    }

    sf::Vector2u InfiniteGrid::getCellSize() const
    {
        return m_cellSize;
    }

    void InfiniteGrid::setCellColor(const sf::Vector2i& cellIndex, const sf::Color& color)
    {
        sf::Vector2f viewSize = info::getWindowInstance()->getView().getSize();
        sf::Vector2f viewCenter = info::getWindowInstance()->getView().getCenter();

        sf::Vector2f cellPos = sf::Vector2f(cellIndex.x * (int)m_cellSize.x, cellIndex.y * (int)m_cellSize.y) + m_positionOffset;
        cellPos += viewCenter - viewSize / 2.f;

        m_vertices.append(sf::Vertex(cellPos, color));
        m_vertices.append(sf::Vertex(cellPos + sf::Vector2f(m_cellSize.x, 0), color));
        m_vertices.append(sf::Vertex(cellPos + sf::Vector2f(m_cellSize.x, 0), color));
        m_vertices.append(sf::Vertex(cellPos + sf::Vector2f(m_cellSize.x, m_cellSize.y), color));
        m_vertices.append(sf::Vertex(cellPos + sf::Vector2f(m_cellSize.x, m_cellSize.y), color));
        m_vertices.append(sf::Vertex(cellPos + sf::Vector2f(0, m_cellSize.y), color));
        m_vertices.append(sf::Vertex(cellPos + sf::Vector2f(0, m_cellSize.y), color));
        m_vertices.append(sf::Vertex(cellPos, color));
    }

    sf::Vector2i InfiniteGrid::getCellFromPos(const sf::Vector2f& position) const
    {
        sf::Vector2f viewSize = info::getWindowInstance()->getView().getSize();
        sf::Vector2f viewCenter = info::getWindowInstance()->getView().getCenter();

        sf::Vector2f cellPos = position - viewCenter + viewSize / 2.f;
        cellPos -= m_positionOffset;

        sf::Vector2i cellIndex = sf::Vector2i(cellPos.x / m_cellSize.x, cellPos.y / m_cellSize.y);

        // if the position is negative, we need to subtract 1 to get the correct cell index
        if (cellPos.x < 0)
            cellIndex.x--;
        if (cellPos.y < 0)
            cellIndex.y--;

        return sf::Vector2i(cellIndex.x, cellIndex.y);
    }

    bool InfiniteGrid::isCellVisible(const sf::Vector2i& cellIndex) const
    {
        sf::Vector2f viewSize = info::getWindowInstance()->getView().getSize();
        sf::Vector2f viewCenter = info::getWindowInstance()->getView().getCenter();

        sf::Vector2f cellPos = sf::Vector2f(cellIndex.x * (int)m_cellSize.x, cellIndex.y * (int)m_cellSize.y) + m_positionOffset;
        cellPos += viewCenter - viewSize / 2.f;

        if (cellPos.x < viewCenter.x - viewSize.x / 2 - m_cellSize.x || cellPos.x > viewCenter.x + viewSize.x / 2 + m_cellSize.x)
            return false;
        if (cellPos.y < viewCenter.y - viewSize.y / 2 - m_cellSize.y || cellPos.y > viewCenter.y + viewSize.y / 2 + m_cellSize.y)
            return false;
        return true;
    }

    sf::Vector2u InfiniteGrid::getSize() const
    {
        sf::Vector2f viewSize = info::getWindowInstance()->getView().getSize();
        sf::Vector2f viewCenter = info::getWindowInstance()->getView().getCenter();

        sf::Vector2f cellPos = sf::Vector2f(0, 0) + m_positionOffset;
        cellPos += viewCenter - viewSize / 2.f;

        sf::Vector2u size = sf::Vector2u(0, 0);

        while (cellPos.x < viewCenter.x + viewSize.x / 2 + m_cellSize.x) {
            size.x++;
            cellPos.x += m_cellSize.x;
        }

        while (cellPos.y < viewCenter.y + viewSize.y / 2 + m_cellSize.y) {
            size.y++;
            cellPos.y += m_cellSize.y;
        }

        return size;
    }

    sf::Vector2f InfiniteGrid::getPosFromCell(const sf::Vector2i& cellIndex) const
    {
        sf::Vector2f viewSize = info::getWindowInstance()->getView().getSize();
        sf::Vector2f viewCenter = info::getWindowInstance()->getView().getCenter();

        sf::Vector2f cellPos = sf::Vector2f(cellIndex.x * (int)m_cellSize.x, cellIndex.y * (int)m_cellSize.y) + m_positionOffset;
        cellPos += viewCenter - viewSize / 2.f;

        return cellPos;
    }

}