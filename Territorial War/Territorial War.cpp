#include <SFML/Graphics.hpp>
#include "InGame.h"
#include "SceneMenu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Territorial War", sf::State::Fullscreen);
    /*InGame game(&window);
    game.init();
    game.run();*/
    while (window.isOpen())
    {
        SceneMenu menu(&window);
        menu.run();
    }
}



  

     
     
