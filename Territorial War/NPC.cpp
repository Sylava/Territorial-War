#include "NPC.h"
#include "Conditions.h"

void Npc::Init()
{
    context.npc = this;
    PatrolState* patrolState = fsm.CreateState<PatrolState>();
    ChaseState* chaseState = fsm.CreateState<ChaseState>();
    IdleState* idleState = fsm.CreateState<IdleState>();

    idleState->AddTransition(Conditions::IsSeeingPlayer, chaseState);
    idleState->AddTransition(Conditions::HasWaited, patrolState);
    patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);
    patrolState->AddTransition(Conditions::HasReachedPoint, idleState);

    chaseState->AddTransition([](NpcContext& _context)
        {
            return !Conditions::IsSeeingPlayer(_context);
        }, patrolState);

    fsm.Init(patrolState, context);
}

void Npc::updateFsm(float dt)
{
    fsm.Update(context, dt);
}

void Npc::move(const sf::Vector2f& move, std::vector<sf::Sprite> rocks)
{
    if (move.x > 0.f)
        animMirror = true;
    else if (move.x < 0.f)
        animMirror = false;

    sf::Vector2f oldPosition = position;
    sf::FloatRect oldHitbox = hitbox;

    position.x += move.x;
    hitbox.position.x += move.x;

    for (const sf::Sprite& rock : rocks)
    {
        if (hitbox.findIntersection(rock.getGlobalBounds()))
        {
            position.x = oldPosition.x;
            hitbox.position.x = oldHitbox.position.x;
            break;
        }
    }
    position.y += move.y;
    hitbox.position.y += move.y;

    for (const sf::Sprite& rock : rocks)
    {
        if (hitbox.findIntersection(rock.getGlobalBounds()))
        {
            position.y = oldPosition.y;
            hitbox.position.y = oldHitbox.position.y;
            break;
        }
    }
    if (position == oldPosition)
        isMoving = false;
}