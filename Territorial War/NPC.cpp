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
//    // Si le NPC sort de la fenêtre → nouvelle direction aléatoire
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
