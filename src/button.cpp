#include <iostream>

#include "button.hpp"

using namespace sf;

void button::SpriteInit()
{
    ButtonSprite.setTexture(ButtonTexture);              //texture
    ButtonSprite.setPosition(Vector2f({ PosX*Scale, PosY*Scale }));  //position
    ButtonSprite.setTextureRect(IntRect({ 0, 0 }, { Width, Height }));
}

button::button(std::string name, int width, int height, float posX, float posY, std::string buttonTexture) : 
    Name(name),

    Width(width), 
    Height(height),
    Scale(1.0f),

    PosX(posX), 
    PosY(posY),
    
    ButtonTexture(Vector2u({ static_cast<unsigned int>(width), static_cast<unsigned int>(height) })),
    ButtonSprite(ButtonTexture)
{
    //texture load
    if(!ButtonTexture.loadFromFile(buttonTexture)) { std::cerr << "ERROR: can't load the texture"; }

    this->SpriteInit();
    this->setScale(SCALE);
}

bool button::checkPressed(float x, float y)
{
    if ((x >= PosX && x <= (PosX+(Width))) && (y >= PosY && y <= (PosY+(Height))))
    {
        std::cout << "Button " << Name << " PRESSED" << std::endl;
        return 1;
    }
    else   
        return 0;
}

void button::drawButton(sf::RenderWindow *window)
{
    window->draw(ButtonSprite);
}

void button::setPos(float posX, float posY)
{
    PosX = posX;
    PosY = posY;
    ButtonSprite.setPosition(Vector2f({ PosX, PosY }));  
}

void button::setScale(float scale)
{
    Width /= Scale;
    Height /= Scale;
    PosX /= Scale;
    PosY /= Scale;

    //set the Scale
    Scale = scale;
    ButtonSprite.setScale(Vector2f{Scale, Scale});
    this->setPos(PosX*Scale, PosY*Scale);

    //reset the dimensions
    Width *= Scale;
    Height *= Scale;
}

float button::getScale()
{
    return Scale;
}
