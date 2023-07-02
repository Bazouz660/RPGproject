/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Quadtree
*/

#pragma once

#include "common.hpp"
#include "IObject.hpp"

#include <cassert>
#include <algorithm>
#include <array>
#include <memory>
#include <type_traits>
#include <vector>

namespace bya
{
    namespace spacePart
    {

        template <typename T, typename GetBox, typename Equal = std::equal_to<T>, typename Float = float>
        class Quadtree
        {
            static_assert(std::is_convertible_v<std::invoke_result_t<GetBox, const T &>, sf::FloatRect>,
                          "GetBox must be a callable of signature sf::FloatRect(const T&)");
            static_assert(std::is_convertible_v<std::invoke_result_t<Equal, const T &, const T &>, bool>,
                          "Equal must be a callable of signature bool(const T&, const T&)");
            static_assert(std::is_arithmetic_v<Float>);

        public:
            Quadtree(const sf::FloatRect &box, const GetBox &getBox = GetBox(),
                     const Equal &equal = Equal()) : mBox(box), mRoot(std::make_unique<Node>()), mGetBox(getBox), mEqual(equal)
            {
                mRoot.get()->box = box;
                mRoot.get()->shape.setFillColor(sf::Color::Transparent);
                mRoot.get()->shape.setOutlineColor(sf::Color::White);
                mRoot.get()->shape.setOutlineThickness(1);
                mRoot.get()->shape.setSize(sf::Vector2f(box.width, box.height));
                mRoot.get()->shape.setPosition(sf::Vector2f(box.left, box.top));
            }

            void add(const T &value)
            {
                add(mRoot.get(), 0, mBox, value);
            }

            void remove(const T &value)
            {
                remove(mRoot.get(), mBox, value);
            }

            void clear()
            {
                clearNode(mRoot.get());
            }

            std::vector<T> query(const sf::FloatRect &box) const
            {
                auto values = std::vector<T>();
                query(mRoot.get(), mBox, box, values);
                return values;
            }

            std::vector<std::pair<T, T>> findAllIntersections() const
            {
                auto intersections = std::vector<std::pair<T, T>>();
                findAllIntersections(mRoot.get(), intersections);
                return intersections;
            }

            sf::FloatRect getBox() const
            {
                return mBox;
            }

            void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default)
            {
                drawChild(target, states, mRoot.get());
            }

        private:
            static constexpr auto Threshold = std::size_t(16);
            static constexpr auto MaxDepth = std::size_t(8);

            struct Node
            {
                std::array<std::unique_ptr<Node>, 4> children;
                std::vector<T> values;
                sf::RectangleShape shape;
                sf::FloatRect box;
            };

            sf::FloatRect mBox;
            std::unique_ptr<Node> mRoot;
            GetBox mGetBox;
            Equal mEqual;

            void drawChild(sf::RenderTarget &target, sf::RenderStates states, Node *node)
            {
                target.draw(node->shape, states);
                for (auto &child : node->children)
                    if (child)
                        drawChild(target, states, child.get());
            }

            bool isLeaf(const Node *node) const
            {
                return !static_cast<bool>(node->children[0]);
            }

            sf::FloatRect computeBox(const sf::FloatRect &box, int i) const
            {
                sf::Vector2f origin(box.left, box.top);
                auto childSize = sf::Vector2f(box.width, box.height) / static_cast<Float>(2);
                switch (i) {
                    case 0:
                        return sf::FloatRect(origin, childSize);
                    case 1:
                        return sf::FloatRect(sf::Vector2<Float>(origin.x + childSize.x, origin.y), childSize);
                    case 2:
                        return sf::FloatRect(sf::Vector2<Float>(origin.x, origin.y + childSize.y), childSize);
                    case 3:
                        return sf::FloatRect(origin + childSize, childSize);
                default:
                    assert(false && "Invalid child index");
                    return sf::FloatRect();
                }
            }

            int getQuadrant(const sf::FloatRect &nodeBox, const sf::FloatRect &valueBox) const
            {
                sf::Vector2f center(nodeBox.left + nodeBox.width / 2, nodeBox.top + nodeBox.height / 2);
                if (valueBox.left + valueBox.width < center.x)
                {
                    if (valueBox.top + valueBox.height < center.y)
                        return 0;
                    else if (valueBox.top >= center.y)
                        return 2;
                    else
                        return -1;
                }
                else if (valueBox.left >= center.x)
                {
                    if (valueBox.top + valueBox.height < center.y)
                        return 1;
                    else if (valueBox.top >= center.y)
                        return 3;
                    else
                        return -1;
                }
                else
                    return -1;
            }

            void add(Node *node, std::size_t depth, const sf::FloatRect &box, const T &value)
            {
                assert(node != nullptr);
                assert(box.contains(mGetBox(value)));
                if (isLeaf(node)) {
                    if (depth >= MaxDepth || node->values.size() < Threshold)
                        node->values.push_back(value);
                    else {
                        split(node, box);
                        add(node, depth, box, value);
                    }
                } else {
                    auto i = getQuadrant(box, mGetBox(value));
                    if (i != -1)
                        add(node->children[static_cast<std::size_t>(i)].get(), depth + 1, computeBox(box, i), value);
                    else
                        node->values.push_back(value);
                }
            }

            void setRect(Node *node, Node *child, int quadrant)
            {
                assert(node != nullptr);
                assert(child != nullptr);
                assert(i >= 0 && i < 4);

                if (quadrant == 0) {
                    child->box = sf::FloatRect(node->box.left, node->box.top, node->box.width / 2, node->box.height / 2);
                } else if (quadrant == 1) {
                    child->box = sf::FloatRect(node->box.left + node->box.width / 2, node->box.top, node->box.width / 2, node->box.height / 2);
                } else if (quadrant == 2) {
                    child->box = sf::FloatRect(node->box.left, node->box.top + node->box.height / 2, node->box.width / 2, node->box.height / 2);
                } else if (quadrant == 3) {
                    child->box = sf::FloatRect(node->box.left + node->box.width / 2, node->box.top + node->box.height / 2, node->box.width / 2, node->box.height / 2);
                }

                child->shape.setFillColor(sf::Color::Transparent);
                child->shape.setOutlineColor(sf::Color::White);
                child->shape.setOutlineThickness(1);
                child->shape.setPosition(child->box.left, child->box.top);
                child->shape.setSize(sf::Vector2f(child->box.width, child->box.height));
            }

            void split(Node *node, const sf::FloatRect &box)
            {
                assert(node != nullptr);
                assert(isLeaf(node) && "Only leaves can be split");
                int x = 0;
                for (auto &child : node->children) {
                    child = std::make_unique<Node>();
                    setRect(node, child.get(), x);
                    x++;
                }
                auto newValues = std::vector<T>();
                for (const auto &value : node->values)
                {
                    auto i = getQuadrant(box, mGetBox(value));
                    if (i != -1)
                        node->children[static_cast<std::size_t>(i)]->values.push_back(value);
                    else
                        newValues.push_back(value);
                }
                node->values = std::move(newValues);
            }

            bool remove(Node *node, const sf::FloatRect &box, const T &value)
            {
                assert(node != nullptr);
                assert(box.contains(mGetBox(value)));
                if (isLeaf(node)) {
                    removeValue(node, value);
                    return true;
                } else {
                    auto i = getQuadrant(box, mGetBox(value));
                    if (i != -1) {
                        if (remove(node->children[static_cast<std::size_t>(i)].get(), computeBox(box, i), value))
                            return tryMerge(node);
                    }
                    else
                        removeValue(node, value);
                    return false;
                }
            }

            void removeValue(Node *node, const T &value)
            {
                auto it = std::find_if(std::begin(node->values), std::end(node->values),
                                       [this, &value](const auto &rhs)
                                       { return mEqual(value, rhs); });
                assert(it != std::end(node->values) && "Trying to remove a value that is not present in the node");
                *it = std::move(node->values.back());
                node->values.pop_back();
            }

            bool tryMerge(Node *node)
            {
                assert(node != nullptr);
                assert(!isLeaf(node) && "Only interior nodes can be merged");
                auto nbValues = node->values.size();
                for (const auto &child : node->children) {
                    if (!isLeaf(child.get()))
                        return false;
                    nbValues += child->values.size();
                }
                if (nbValues <= Threshold) {
                    node->values.reserve(nbValues);
                    for (const auto &child : node->children) {
                        for (const auto &value : child->values)
                            node->values.push_back(value);
                    }
                    for (auto &child : node->children)
                        child.reset();
                    return true;
                } else
                    return false;
            }

            void query(Node *node, const sf::FloatRect &box, const sf::FloatRect &queryBox, std::vector<T> &values) const
            {
                assert(node != nullptr);
                assert(queryBox.intersects(box));
                for (const auto &value : node->values) {
                    if (queryBox.intersects(mGetBox(value)))
                        values.push_back(value);
                }
                if (!isLeaf(node)) {
                    for (auto i = std::size_t(0); i < node->children.size(); ++i) {
                        auto childBox = computeBox(box, static_cast<int>(i));
                        if (queryBox.intersects(childBox))
                            query(node->children[i].get(), childBox, queryBox, values);
                    }
                }
            }

            void findAllIntersections(Node *node, std::vector<std::pair<T, T>> &intersections) const
            {
                for (auto i = std::size_t(0); i < node->values.size(); ++i) {
                    for (auto j = std::size_t(0); j < i; ++j) {
                        if (mGetBox(node->values[i]).intersects(mGetBox(node->values[j])))
                            intersections.emplace_back(node->values[i], node->values[j]);
                    }
                }
                if (!isLeaf(node)) {
                    for (const auto &child : node->children) {
                        for (const auto &value : node->values)
                            findIntersectionsInDescendants(child.get(), value, intersections);
                    }
                    for (const auto &child : node->children)
                        findAllIntersections(child.get(), intersections);
                }
            }

            void findIntersectionsInDescendants(Node *node, const T &value, std::vector<std::pair<T, T>> &intersections) const
            {
                for (const auto &other : node->values) {
                    if (mGetBox(value).intersects(mGetBox(other)))
                        intersections.emplace_back(value, other);
                }
                if (!isLeaf(node)) {
                    for (const auto &child : node->children)
                        findIntersectionsInDescendants(child.get(), value, intersections);
                }
            }

            void clearNode(Node *node)
            {
                assert(node != nullptr);
                for (auto &child : node->children) {
                    if (child != nullptr)
                        clearNode(child.get());
                }
                std::fill_n(std::begin(node->children), 4, nullptr);
                node->values.clear();
            }
        };
    }
}