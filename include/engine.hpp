#pragma once

#include <SFML/Graphics.hpp>
#include <stack>

#include "gameState.hpp"
#include "menu.hpp"
#include "game.hpp"
#include "pauseMenu.hpp"
#include "gameOverMenu.hpp"
#include "globals.hpp"

using namespace sf;

class engine
{
public:
    engine();
    ~engine();

    void Run();

private:
    void popState();
    void pushState(gameState* state);

private:
    std::stack<gameState*> States;
    RenderWindow Window;

    int NextState;
};