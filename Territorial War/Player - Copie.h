#pragma once
#include "Entity.h"



class Player : public Entity<sf::CircleShape> {
public:
    Player();

    void update(float speed) override;
};

