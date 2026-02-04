//
//#pragma once
//#include <SFML/Graphics.hpp>
//#include <memory>
//#include <unordered_map>
//#include <string>
//
//#include "Scene.h"
//#include "SceneMenu.h"
//#include "SceneGame.h"
//#include "Player.h"
//#include "Ennemies.h"
//
//class Launch {
//private:
//    std::unordered_map<std::string, std::unique_ptr<Scene<Launch>>> scenes;
//    Scene<Launch>* currentScene;
//public:
//    sf::RenderWindow window;
//
//    Launch() : window(sf::VideoMode(800, 600), "Menu SFML") {
//        scenes["menu"] = std::make_unique<SceneMenu>();
//        scenes["game"] = std::make_unique<SceneGame>();
//        scenes["settings"] = std::make_unique<SceneSettings>();
//
//        currentScene = scenes["menu"].get();
//    }
//
//    void changeScene(const std::string& name) {
//        currentScene = scenes[name].get();
//    }
//
//    void run() {
//        sf::Clock clock;
//
//        while (window.isOpen())
//        {
//            while (const std::optional event = window.pollEvent())
//            {
//                if (event->is<sf::Event::Closed>())
//                    window.close();
//            }
//            sf::Vector2f oldPlayerPos = player.getPosition();
//            sf::Vector2f oldSquarePos = ennemies.getPosition();
//
//            player.update(speed);
//            ennemies.update(speed);
//
//
//            sf::Vector2u winSize = window.getSize();
//            float winW = static_cast<float>(winSize.x);
//            float winH = static_cast<float>(winSize.y);
//
//
//            auto clampPosToWindow = [&](const sf::FloatRect& bounds, sf::Vector2f pos) -> sf::Vector2f
//                {
//                    float maxX = std::max(0.f, winW - bounds.size.x);
//                    float maxY = std::max(0.f, winH - bounds.size.y);
//                    pos.x = std::clamp(pos.x, 0.f, maxX);
//                    pos.y = std::clamp(pos.y, 0.f, maxY);
//                    return pos;
//                };
//
//            {
//                sf::FloatRect pBounds = player.getBounds();
//                sf::Vector2f pPos = player.getPosition();
//                pPos = clampPosToWindow(pBounds, pPos);
//                player.setPosition(pPos);
//            }
//
//            {
//                sf::FloatRect eBounds = ennemies.getBounds();
//                sf::Vector2f ePos = ennemies.getPosition();
//                ePos = clampPosToWindow(eBounds, ePos);
//                ennemies.setPosition(ePos);
//            }
//            if (player.getBounds().findIntersection(ennemies.getBounds()))
//            {
//                player.setPosition(oldPlayerPos);
//                ennemies.setPosition(oldSquarePos);
//            }
//
//
//            window.clear(sf::Color::Black);
//            player.draw(window);
//            ennemies.draw(window);
//            window.display();
//
//        }
//        return 0;
//
//};
