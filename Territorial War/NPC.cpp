//#include "NPC.h"
//#include "NPC.h"
//
//#include <cmath>
//#include <cstdlib>
//
//Npc::Npc() :
//    Entity(sf::RectangleShape({ 50.f, 50.f }))
//{
//    // Apparence par défaut
//    shape.setFillColor(sf::Color::Red);
//}
//
//void Npc::Init()
//{
//    // Création des états
//    auto* patrolState = fsm.CreateState<PatrolState>();
//    auto* chaseState = fsm.CreateState<ChaseState>();
//
//    // Transitions
//    patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);
//
//    chaseState->AddTransition(
//        [](const NpcContext ctx)
//        {
//            return !Conditions::IsSeeingPlayer(ctx);
//        },
//        patrolState
//    );
//
//    // État initial obligatoire
//    fsm.SetInitialState(patrolState);
//
//    // Direction aléatoire
//    float angle = static_cast<float>(std::rand() % 360);
//    direction = { std::cos(angle), std::sin(angle) };
//}
//
//sf::Vector2f Npc::Normalize(const sf::Vector2f& v)
//{
//    float length = std::sqrt(v.x * v.x + v.y * v.y);
//    return (length != 0.f) ? v / length : sf::Vector2f(0.f, 0.f);
//}
//
//void Npc::update(float dt, const sf::RenderWindow& window)
//{
//    // Mise à jour du FSM
//    NpcContext ctx;
//    ctx.npc = this;
//    ctx.window = &window;
//    fsm.Update(ctx);
//
//    // Déplacement simple (si ton état Patrol ne gère pas déjà le mouvement)
//    sf::Vector2f pos = getPosition();
//    pos += direction * speed * dt;
//    setPosition(pos);
//
//    // Si le NPC sort de la fenêtre  nouvelle direction aléatoire
//    sf::FloatRect bounds = getBounds();
//    sf::Vector2u win = window.getSize();
//
//    bool changeDir = false;
//
//    if (bounds.left < 0 || bounds.left + bounds.width > win.x)
//        changeDir = true;
//
//    if (bounds.top < 0 || bounds.top + bounds.height > win.y)
//        changeDir = true;
//
//    if (changeDir)
//    {
//        float angle = static_cast<float>(std::rand() % 360);
//        direction = { std::cos(angle), std::sin(angle) };
//    }
//}

//
//#include <iostream>
//#include <cmath>
//
//Npc::Npc()
//    : Entity(sf::RectangleShape({ 50.f, 50.f })),
//    gen(std::random_device{}()),
//    distX(50, 750),   // limites X de la fenêtre
//    distY(50, 550)    // limites Y de la fenêtre
//{
//    shape.setFillColor(sf::Color::Blue);
//    chooseRandomTarget();
//}
//
//Npc::~Npc() {}
//
//void Npc::Init()
//{
//    // Exemple si tu veux garder ton FSM
//    PatrolState* patrolState = fsm.CreateState<PatrolState>();
//    ChaseState* chaseState = fsm.CreateState<ChaseState>();
//
//    patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);
//
//    chaseState->AddTransition([](const NpcContext _context)
//        {
//            return !Conditions::IsSeeingPlayer(_context);
//        }, patrolState);
//
//    fsm.Init(patrolState, context);
//}
//
//sf::Vector2f Npc::getDirection(const sf::Vector2f& v)
//{
//    float length = std::sqrt(v.x * v.x + v.y * v.y);
//    return (length != 0.f) ? v / length : sf::Vector2f(0.f, 0.f);
//}
//
//void Npc::chooseRandomTarget()
//{
//    target = sf::Vector2f(distX(gen), distY(gen));
//}
//
//void Npc::update(float dt)
//{
//    fsm.Update(context);
//
//    // Calcul direction vers la cible
//    direction = getDirection(target - getPosition());
//
//    // Déplacement
//    move(direction * speed * dt);
//
//    // Vérifie si on est proche du point cible
//    if (std::abs(getPosition().x - target.x) < 5.f &&
//        std::abs(getPosition().y - target.y) < 5.f)
//    {
//        chooseRandomTarget();
//    }
//}


#include "Npc.h"

Npc::Npc()
    : Entity(sf::RectangleShape({ 50.f, 50.f }))
{
    getShape().setFillColor(sf::Color::Red);
    context.npc = this;
}

void Npc::Init(Player* player)
{
    context.player = player;

    IdleState* idle = new IdleState();
    PatrolState* patrol = new PatrolState();
    ChaseState* chase = new ChaseState();

    idle->AddTransition([](const NpcContext& ctx) {
        return true;
        }, patrol);

    patrol->AddTransition([](const NpcContext& ctx) {
        float dx = ctx.player->getPosition().x - ctx.npc->getPosition().x;
        float dy = ctx.player->getPosition().y - ctx.npc->getPosition().y;
        return dx * dx + dy * dy < 150 * 150;
        }, chase);

    chase->AddTransition([](const NpcContext& ctx) {
        float dx = ctx.player->getPosition().x - ctx.npc->getPosition().x;
        float dy = ctx.player->getPosition().y - ctx.npc->getPosition().y;
        return dx * dx + dy * dy > 200 * 200;
        }, patrol);

    fsm.Init(idle, context);
}

void Npc::update(float dt)
{
    fsm.Update(context, dt);

    // Empêcher de sortir de la fenêtre
    auto pos = getPosition();
    pos.x = std::clamp(pos.x, 0.f, 750.f);
    pos.y = std::clamp(pos.y, 0.f, 550.f);
    setPosition(pos);
}
