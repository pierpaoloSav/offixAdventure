#pragma once

#include <SFML/Graphics.hpp>

#include "globals.hpp"

using namespace sf;

class button
{
public:
    button(std::string name, int width, int height, float posX, float posY, std::string buttonTexture);

    void drawButton(RenderWindow *window);
    bool checkPressed(float x, float y);

    void setPos(float posX, float posY);
    void setScale(float scale);

    float getScale();

private:
    void SpriteInit();

private:
    Sprite ButtonSprite;
    Texture ButtonTexture;

    std::string Name;

    int Width, Height;
    float Scale;

    float PosX, PosY;
};