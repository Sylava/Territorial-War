#include <SFML/Graphics.hpp>
#include "InGame.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!", sf::State::Fullscreen);
    InGame game;
    game.init();
    game.run(&window);
    
}



  

     
     
