#pragma once

#include <SFML/Graphics.hpp>

#include "character.hpp"
#include "animation.hpp"
#include "tile.hpp"
#include "bullet.hpp"

using namespace sf;

class player : public character
{
public:
    player(int width, int height, float posX, float posY, float offsetX, float offsetY, 
           float life, float speed, float strenght,
           std::string name, std::string pgTexture = "../res/playerSheet.png");
    ~player();

    //score
    int getScore();
    void incScore();

    //modifiers
    void heal(float life);
    std::vector<tile*>* getHearts();
    std::vector<bullet*>* getBullets();
    void buffSpeed(float speed, float time);
    void shield(float time);
    void modifiersUpdate();

    //combat    
    void getDamage(float damage) override;
    void attack(float deltatime);

    //movement  
    void moveForward() override;
    void moveLeft() override;
    void moveRight() override;
    void moveBack() override;

    void movement(float deltatime);

    void drawProps(RenderWindow *window);
    
private:
    void PropsInit();
    void hearts(std::vector<tile*>& hearts);

private:
    int Score;
    std::vector<tile*> Hearts;
    std::vector<bullet*> Bullets;

    //modifiers
    float SpeedMod;
    float SpeedModTime;
    Clock SpeedModClock;
    bool Immune;
    Texture ShieldTex;
    Sprite Shield;
    float ShieldModTime;
    Clock ShieldModClock;
    float AttackCooldown;

    //animations
    animation RunningUp;
    animation RunningDown;
    animation RunningLeft;
    animation RunningRight;
    animation AttackLeft;
    animation AttackRight;
    animation AttackUp;
    animation AttackDown;
    Clock Cooldown;
    bool Attacking;
};