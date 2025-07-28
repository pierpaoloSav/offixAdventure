#include "gameState.hpp"

void gameState::Loop()
{
    this->Update();
    this->Render();
}

bool gameState::isRunning()
{
    return Running;
}

bool gameState::isShutting()
{
    return Shutting;
}