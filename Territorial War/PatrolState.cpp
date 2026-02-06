//#include "PatrolState.h"
//
//void PatrolState::Enter(NpcContext _context)
//{
//    std::cout << "Enter Patrol _State" << std::endl;
//}
//
//void PatrolState::Execute(NpcContext _context)
//{
//	std::cout << "Patrol State update" << std::endl;
//}
//
//void PatrolState::Exit(NpcContext _context)
//{
//    std::cout << "Exit Patrol _State" << std::endl;
//}

//#include "PatrolState.h"
//#include <random>
//#include <cmath>
//
//void PatrolState::Enter(NpcContext& ctx)
//{
//    chooseRandomTarget(ctx);
//}
//
//void PatrolState::chooseRandomTarget(NpcContext& ctx)
//{
//    static std::mt19937 gen(std::random_device{}());
//    std::uniform_int_distribution<int> distX(50, 750);
//    std::uniform_int_distribution<int> distY(50, 550);
//
//    target = sf::Vector2f(distX(gen), distY(gen));
//}
//
//void PatrolState::Update(NpcContext& ctx, float dt)
//{
//    sf::Vector2f pos = ctx.npc->getPosition();
//    sf::Vector2f dir = target - pos;
//
//    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//    if (len > 0.1f)
//        dir /= len;
//
//    ctx.npc->move(dir * ctx.npc->speed * dt);
//
//    if (std::abs(pos.x - target.x) < 5.f &&
//        std::abs(pos.y - target.y) < 5.f)
//    {
//        chooseRandomTarget(ctx);
//    }
//}
//
//void PatrolState::Exit(NpcContext& ctx)
//{
//    // Rien à faire pour l’instant
//}

#include "PatrolState.h"
#include "Npc.h"
#include <random>
#include <cmath>

void PatrolState::Enter(NpcContext& ctx)
{
    chooseRandomTarget();
}

void PatrolState::chooseRandomTarget()
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distX(0, 800);
    std::uniform_int_distribution<int> distY(0, 600);

    target = sf::Vector2f(distX(gen), distY(gen));
}

void PatrolState::Update(NpcContext& ctx, float dt)
{
    sf::Vector2f pos = ctx.npc->getPosition();
    sf::Vector2f dir = target - pos;

    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 1.f)
        dir /= len;

    ctx.npc->move(dir * ctx.npc->speed * dt);

    if (len < 5.f)
        chooseRandomTarget();
}
