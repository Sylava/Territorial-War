//#include <SFML/Graphics.hpp>
//#include "Player.h"
//#include "Ennemies.h"
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");
//    sf::CircleShape shape(100.f);
//   
//    Player player; 
//    Ennemies ennemies;
//    float speed = 0.1f;
//
    //while (window.isOpen())
    //{
    //    while (const std::optional event = window.pollEvent())
    //    {
    //        if (event->is<sf::Event::Closed>())
    //            window.close();
    //    }
//        sf::Vector2f oldPlayerPos = player.getPosition();
//        sf::Vector2f oldSquarePos = ennemies.getPosition();
//
//        player.update(speed);
//        ennemies.update(speed);
//
//
//        sf::Vector2u winSize = window.getSize();
//        float winW = static_cast<float>(winSize.x);
//        float winH = static_cast<float>(winSize.y);
//
//
//        auto clampPosToWindow = [&](const sf::FloatRect& bounds, sf::Vector2f pos) -> sf::Vector2f
//            {
//                float maxX = std::max(0.f, winW - bounds.size.x);
//                float maxY = std::max(0.f, winH - bounds.size.y);
//                pos.x = std::clamp(pos.x, 0.f, maxX);
//                pos.y = std::clamp(pos.y, 0.f, maxY);
//                return pos;
//            };
//
//        {
//            sf::FloatRect pBounds = player.getBounds();
//            sf::Vector2f pPos = player.getPosition();
//            pPos = clampPosToWindow(pBounds, pPos);
//            player.setPosition(pPos);
//        }
//
//        {
//            sf::FloatRect eBounds = ennemies.getBounds();
//            sf::Vector2f ePos = ennemies.getPosition();
//            ePos = clampPosToWindow(eBounds, ePos);
//            ennemies.setPosition(ePos);
//        }
//        if (player.getBounds().findIntersection(ennemies.getBounds()))
//        {
//            player.setPosition(oldPlayerPos);
//            ennemies.setPosition(oldSquarePos);
//        }
//
//        
//        window.clear(sf::Color::Black);
//        player.draw(window);
//        ennemies.draw(window);
//        window.display();
//
//    }
//}
//
//
//
//  
//
//     
//     
//
//
//
//
//
//
//
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "terrain");

    TileMap map(25, 18);
    Player player;

    bool editMode = true; // E pour basculer

    sf::Clock clock;

    while (const auto event = window.pollEvent()) {

         //Clic gauche = herbe
        if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mb->button == sf::Mouse::Button::Left) {

                int x = mb->position.x / TileMap::TILE_X;
                int y = mb->position.y / TileMap::TILE_Y;

                map.setTile(x, y, TileType::Grass);
            }
        }

        // T = mur transparent
        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::Y) {

                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                int x = mouse.x / TileMap::TILE_X;
                int y = mouse.y / TileMap::TILE_Y;

                map.setTile(x, y, TileType::Wall);
            }

            // G = sauvegarder
            if (key->code == sf::Keyboard::Key::G) {
                map.save("map.txt");
            }

            // L = charger
            if (key->code == sf::Keyboard::Key::L) {
                map.load("map.txt");
            }
        }
    }



    float dt = clock.restart().asSeconds();

    player.update(dt, map);

    window.clear(sf::Color(100, 100, 100));
    map.draw(window);
    window.draw(player.shape);
    window.display();


    return 0;
}
