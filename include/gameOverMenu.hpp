#pragma once

#include <SFML/Graphics.hpp>

#include "gameState.hpp"
#include "button.hpp"
#include "globals.hpp"

using namespace sf;

class gameOverMenu : public gameState
{
public:
    gameOverMenu(RenderWindow *window);
    ~gameOverMenu();

    int Update() override;
    void Render() override;

private:
    void BackgroundInit();
    void ButtonInit();
    void TextInit();

private:
    Texture BackgroundTex;
    Sprite Background;
    RectangleShape Overlay;

    Font GameFont; 
    Text GameOverText;

    button ButtonPlay;
    button ButtonMenu;
};