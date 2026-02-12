#include <SFML/Graphics.hpp>
#include "GameCore/InGame.h"
#include "Scene/SceneMenu.h"
#include "GameCore/TextureManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Territorial War", sf::State::Fullscreen);
    std::srand(std::time(nullptr));
    TextureManager texManager;
    while (window.isOpen())
    {
        SceneMenu menu(&window);
        // affichage du menu
        menu.run();
        texManager.clear(); // clear des textures
        InGame game(&window);
        // lancement de la partie
        game.run();
        texManager.clear(); // clear des textures
    }
}