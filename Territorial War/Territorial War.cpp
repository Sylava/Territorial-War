#include <SFML/Graphics.hpp>
#include "InGame.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::State::Fullscreen);
    InGame game;
    game.init(&window);
    game.run(&window);
    
}



  

     
     
