
#pragma once
#include "Obstacle.h"
#include <SFML/Graphics.hpp>

// Fonction intersects compatible SFML 2.x et 3.x
inline bool rectIntersects(const sf::FloatRect& a, const sf::FloatRect& b)
{
    return !(a.position.x + a.size.x < b.position.x ||
        b.position.x + b.size.x < a.position.x ||
        a.position.y + a.size.y < b.position.y ||
        b.position.y + b.size.y < a.position.y);
}

template<typename T>
void resolveCollision(T& entity, const Obstacle& obs)
{
    auto eBounds = entity.getShape().getGlobalBounds();
    auto oBounds = obs.getShape().getGlobalBounds();

    if (rectIntersects(eBounds, oBounds))
    {
        if (eBounds.position.x < oBounds.position.x) entity.move({ -2.f, 0.f });
        if (eBounds.position.x > oBounds.position.x) entity.move({ 2.f, 0.f });
        if (eBounds.position.y < oBounds.position.y)  entity.move({ 0.f, -2.f });
        if (eBounds.position.y > oBounds.position.y)  entity.move({ 0.f,  2.f });
    }
}
