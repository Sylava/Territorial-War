#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Entity
{
public:
	Entity(sf::RenderWindow* inWindow, int inHp);

    virtual sf::Sprite* attackAnimation(const float dt);
    virtual sf::Sprite* runAnimation(const float dt);
    virtual sf::Sprite* idleAnimation(const float dt);
    virtual void update(const float dt);
    virtual void draw();

    sf::Vector2f position;
    sf::FloatRect hitbox;
    sf::Sprite* currentSprite = nullptr;
    float speed = 300.f;
    float invunerability = 0.4f;
    bool isAttacking = false;
    bool isMoving = false;
    int hpMax = 5;
    int hp = 5;
    bool animMirror = true;
    bool idleReverse = false;
    bool runReverse = false;
    int attackMaxIndex = 3;
    int idleMaxIndex = 7;
    int runMaxIndex = 5;
    int runIndex = 0;
    int idleIndex = 0;
    int attackIndex = 0;
    float attackAnimTime = 0.08f;
    float runAnimTime = 0.08f;
    float idleAnimTime = 0.08f;

private:
    void buildHpBar();

protected:
    void updateHpBar();

    std::optional<sf::Sprite> startBar;
    std::vector<sf::Sprite> middleBar;
    std::optional<sf::Sprite> endBar;
    std::optional<sf::Sprite> firstHp;
    std::vector<sf::Sprite> hpFill;
    std::optional<sf::Sprite> lastHp;
    std::optional<sf::Sprite> spriteIdle;
    std::optional<sf::Sprite> spriteAttack;
    std::optional<sf::Sprite> spriteRun;
    sf::RenderWindow* window;

};

