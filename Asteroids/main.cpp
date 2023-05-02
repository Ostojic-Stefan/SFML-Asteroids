#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
    Game game;
    while (!game.GetWindow().ShouldClose())
    {
        game.Update();
        game.Render();
    }
    return 0;
}