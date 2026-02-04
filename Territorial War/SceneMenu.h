#pragma once
#include "Scene.h"
#include "Button.h"

class SceneMenu : public Scene<class Application> {
public:
    SceneMenu() :
        btnPlay({ 200, 150 }, { 200, 60 }, "Jouer"),
        btnSettings({ 200, 250 }, { 200, 60 }, "Parametres"),
        btnQuit({ 200, 350 }, { 200, 60 }, "Quitter")
    {
    }

    void handleEvent(const sf::Event& event, Application& app) override {
        sf::Vector2i mousePos = sf::Mouse::getPosition(app.window);

        if (btnPlay.isClicked(event, mousePos)) {
            app.changeScene("game");
        }
        if (btnSettings.isClicked(event, mousePos)) {
            app.changeScene("settings");
        }
        if (btnQuit.isClicked(event, mousePos)) {
            app.window.close();
        }
    }

    void update(Application&, float) override {}

    void draw(sf::RenderWindow& window) override {
        btnPlay.draw(window);
        btnSettings.draw(window);
        btnQuit.draw(window);
    }

private:
    Button btnPlay;
    Button btnSettings;
    Button btnQuit;
};
