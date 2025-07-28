#include <SFML/Graphics.hpp>
#include <iostream>

#include "character.hpp"
#include "globals.hpp"
#include "tile.hpp"

using namespace sf;

void character::PgInit()
{
    //setting the Sprite
    CurrentFrame = IntRect({ 0, 0 }, { Width, Height });
    Pg.setPosition({ PosX, PosY });
    Pg.setTexture(PgTexture);
    Pg.setTextureRect(CurrentFrame);
}

void character::HitboxInit()
{
    //setting the Hitbox
    Hitbox.setSize(sf::Vector2f(Width, Height));
    Hitbox.setPosition({ PosX, PosY });
    Hitbox.setFillColor(sf::Color::Transparent);
    Hitbox.setOutlineColor(sf::Color::Blue);
    Hitbox.setOutlineThickness(1.0);
}

bool character::checkAlive()
{
    if (Life <= 0.0f)
        return false;
    else 
        return true;
}

character::character(int width, int height, float posX, float posY, float offsetX, float offsetY, float life, float speed, float strenght, std::string name, std::string pgTexture):
    Width(width), Height(height), 
    PosX(posX), PosY(posY), 
    OffsetX(offsetX), OffsetY(offsetY),
    Life(life), 
    Strenght(strenght),
    stdSpeed(speed), 
    Name(name),  

    CurrentFrame(),
    PgTexture(Vector2u({ static_cast<unsigned int>(Width), static_cast<unsigned int>(Height) })),
    Pg(PgTexture),

    SpeedX(0), 
    SpeedY(0), 
    IsColliding(0),
    LastDirection(DOWN)
{
    //texture load
    if(!PgTexture.loadFromFile(pgTexture)) { std::cerr << "ERROR: can't load the texture"; }
    
    this->PgInit();
    this->HitboxInit();
}


void character::setPosition(float posX, float posY)
{
    PosX = posX;
    PosY = posY;
    Pg.setPosition({ PosX, PosY });
}
    

void character::setTexture(std::string texture)
{
    if (!PgTexture.loadFromFile(texture)) { std::cerr << "ERROR: can't load the texture"; }
    Pg.setTexture(PgTexture);
}

float character::getPosX()
{
    return PosX;
}

float character::getPosY()
{
    return PosY;
}

RectangleShape &character::getHitbox()
{
   return Hitbox;
}

float character::getLife()
{
    return Life;
}

float character::getStrenght()
{
    return Strenght;
}

bool character::isColliding()
{
    return IsColliding;
}

void character::moveForward()
{
    SpeedY = -stdSpeed;
    LastDirection = UP;
}
void character::moveLeft()
{
    SpeedX = -stdSpeed;
    LastDirection = LEFT;
}
void character::moveRight()
{
    SpeedX = +stdSpeed;
    LastDirection = RIGHT;
}
void character::moveBack()
{
    SpeedY = stdSpeed;
    LastDirection = DOWN;
}

void character::rotate(float angle)
{
    Angle a = degrees(angle);
    Pg.rotate(a);
    Hitbox.rotate(a);
}

float character::attack(character *attacked)
{
    return Strenght;
}

void character::getDamage(float damage)
{
    Life -= damage;
}

void character::update(float deltatime, std::vector<tile*> *collisions)
{
    //Texture Update
    Pg.setTextureRect(CurrentFrame);

    //Position Update
    PosX += SpeedX * deltatime;
    PosY += SpeedY * deltatime;

    bool xColliding = false;
    bool yColliding = false;
    //X collision check
        //Border
        if (PosX < LEFTBORDER) { PosX = LEFTBORDER; xColliding = true; }
        if (PosX > RIGHTBORDER - Width) { PosX = RIGHTBORDER - Width; xColliding = true; }
        //objs
        Hitbox.setPosition({ PosX , PosY - SpeedY * deltatime });
        for (int i = 0; i < collisions->size(); i++)
        {
            RectangleShape Hitbox2 = (collisions->at(i))->getHitbox();
            if (checkCollision(Hitbox, Hitbox2)) 
            { 
                xColliding = true;

                if(SpeedX > 0) //right
                    Hitbox.setPosition({ Hitbox2.getPosition().x - Hitbox.getSize().x, Hitbox.getPosition().y });
                if(SpeedX < 0) //left
                    Hitbox.setPosition({ Hitbox2.getPosition().x + Hitbox2.getSize().x, Hitbox.getPosition().y });
            }

            Pg.setPosition(Hitbox.getPosition());
            PosX = Hitbox.getPosition().x;
        }
        

    //Y collision check
        //Border
        if (PosY < UPBORDER) { PosY = UPBORDER; yColliding = true; }
        if (PosY > DOWNBORDER - Height) { PosY = DOWNBORDER - Height; yColliding = true; }
        //objs
        Hitbox.setPosition({ PosX , PosY });
        for (int i = 0; i < collisions->size(); i++)
        {
            RectangleShape Hitbox2 = (collisions->at(i))->getHitbox();
            if (checkCollision(Hitbox, Hitbox2)) 
            { 
                yColliding = true;

                if(SpeedY < 0) //up
                    Hitbox.setPosition({ Hitbox.getPosition().x, Hitbox2.getPosition().y + Hitbox2.getSize().y });
                if(SpeedY > 0) //down
                    Hitbox.setPosition({ Hitbox.getPosition().x, Hitbox2.getPosition().y - Hitbox.getSize().y });
            }

            Pg.setPosition(Hitbox.getPosition());
            PosY = Hitbox.getPosition().y;
        }
    if (xColliding || yColliding)
        IsColliding = true;
    else
        IsColliding = false;

    //offset
    Pg.move({ OffsetX, OffsetY });

    //Speed Reset 
    SpeedX = 0;
    SpeedY = 0;
}

void character::drawCharacter(RenderWindow *window)
{
    window->draw(Pg);
    if(toggleHitbox)
        window->draw(Hitbox);
}