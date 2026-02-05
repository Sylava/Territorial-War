#include "ColisionBox.h"


void CollisionBox::HandlePlayerWindowCollision(Player& player, const sf::RenderWindow& window, const sf::Vector2f& oldPos)
{
    sf::FloatRect bounds = player.getBounds();
    sf::Vector2u winSize = window.getSize();

    if (bounds.position.x < 0.f ||
        bounds.position.y < 0.f ||
        bounds.position.x + bounds.size.x > winSize.x ||
        bounds.position.y + bounds.size.y > winSize.y)
    {
        player.setPosition(oldPos);
    }
}

void CollisionBox::HandlePlayerNpcCollision(Player& player, Npc& npc,
    const sf::Vector2f& oldPlayerPos,
    const sf::Vector2f& oldNpcPos)
{
    if (player.getBounds().findIntersection(npc.getBounds()))
    {
        player.setPosition(oldPlayerPos);
        npc.setPosition(oldNpcPos);
    }
}
