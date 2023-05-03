#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "StateManager.hpp"

#include <vector>
#include <memory>

SharedContext* ctx = new SharedContext();

struct A
{
    ~A() {
        std::cout << "Death\n";
    }
    int num = 5;
};

int main()
{
    StateManager stateManager = StateManager(ctx);
    Game game;
    while (!game.GetWindow().ShouldClose())
    {
        game.Update();
        game.Render();
        stateManager.Update(sf::Time());
    }

    //std::vector<std::unique_ptr<A>> vec;
    //vec.push_back(std::make_unique<A>());

    //std::unique_ptr<A> tmp = std::move(*vec.begin());
    //vec.erase(vec.begin());

    return 0;
}