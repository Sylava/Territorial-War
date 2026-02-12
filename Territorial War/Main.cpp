#include <SFML/Graphics.hpp>
#include "Scene/InGame.h"
#include "Scene/SceneMenu.h"
#include "TextureManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Territorial War", sf::State::Windowed);
    std::srand(std::time(nullptr));
    TextureManager texManager;
    while (window.isOpen())
    {
        SceneMenu menu(&window);
        ScenePause pause(&window);
        menu.run();
        texManager.clear();
        InGame game(&window);
        game.run();
        texManager.clear();
    }
}