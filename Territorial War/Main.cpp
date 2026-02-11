#include <SFML/Graphics.hpp>
#include "Scene/InGame.h"
#include "Scene/SceneMenu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Territorial War", sf::State::Windowed);
    std::srand(std::time(nullptr));
    while (window.isOpen())
    {
        SceneMenu menu(&window);
        menu.run();
    }
}