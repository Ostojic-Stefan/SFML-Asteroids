#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp"

#include <vector>
#include <memory>

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