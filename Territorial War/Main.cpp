#include <SFML/Graphics.hpp>
#include "InGame.h"
#include "SceneMenu.h"
#include "ScenePause.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Territorial War", sf::State::Fullscreen);
    std::srand(std::time(nullptr));
    while (window.isOpen())
    {
        SceneMenu menu(&window);
        ScenePause pause(&window);
        menu.run();
        pause.run();
    }
}