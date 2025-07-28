#pragma once

#include <SFML/Graphics.hpp>

#include "gameState.hpp"
#include "globals.hpp"

using namespace sf;

class menu : public gameState
{
public:
    menu(RenderWindow *window);
    ~menu();

private:
    void Update();
    void Render();

private:
    Texture BackgroundTex;
    Sprite Background;
};

//TODO: pulsanti 