//#pragma once
//#include <SFML/Graphics.hpp>
//
//template <typename T>
//class Scene {
//public:
//    virtual ~Scene() = default;
//
//    virtual void handleEvent(const sf::Event& event, T& app) = 0;
//    virtual void update(T& app, float dt) = 0;
//    virtual void draw(sf::RenderWindow& window) = 0;
//};
//
//class SceneSettings : public Scene<class Application> {
//public:
//    SceneSettings() {}
//
//    void handleEvent(const sf::Event& event, Application& app) override {
//        if (event.type == sf::Event::KeyPressed &&
//            event.key.code == sf::Keyboard::Escape) {
//            app.changeScene("menu");
//        }
//    }
//
//    void update(Application&, float) override {}
//
//    void draw(sf::RenderWindow& window) override {
//        sf::Font font;
//        font.loadFromFile("arial.ttf");
//
//        sf::Text text("Parametres (Appuie sur ESC pour revenir)", font, 24);
//        text.setPosition(50, 50);
//
//        window.draw(text);
//    }
//};
