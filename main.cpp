#include <iostream>
#include "Game.hpp"

int main()
{

    // Init timer
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init game

    Game game;

    while (game.getWindowIsOpen())
    {
        game.update();
        game.render();
    }
}