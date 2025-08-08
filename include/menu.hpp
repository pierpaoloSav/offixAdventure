#pragma once

#include <SFML/Graphics.hpp>

#include "gameState.hpp"
#include "globals.hpp"
#include "button.hpp"

using namespace sf;

class menu : public gameState
{
public:
    menu(RenderWindow *window);
    ~menu();

    int Update() override;
    void Render() override;

private:
    void BackgroundInit();

private:
    Texture BackgroundTex;
    Sprite Background;

    button ButtonPlay;
    button ButtonRule;
};