#pragma once

#include <SFML/Graphics.hpp>

#include "gameState.hpp"
#include "button.hpp"
#include "globals.hpp"

using namespace sf;

class pauseMenu : public gameState
{
public:
    pauseMenu(RenderWindow *window);
    ~pauseMenu();

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
    Text TitleText;

    button ButtonPlay;
    button ButtonMenu;
};