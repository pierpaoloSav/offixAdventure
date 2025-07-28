#include <iostream>

#include "player.hpp"

void player::PropsInit()
{
    //shield 
    if(!ShieldTex.loadFromFile("../res/shield.png")) { std::cerr << "ERROR: can't load the texture"; }
    Shield.setPosition( { PosX, PosY+10 } );
    Shield.setScale({ 0.8f , 0.8f });
}

player::player(int width, int height, float posX, float posY, float offsetX, float offsetY, float life, float speed, float strenght, std::string name, std::string pgTexture) :
    character(width, height, posX, posY, offsetX, offsetY, life, speed, strenght, name, pgTexture),

    Score(0),
    SpeedMod(0),
    SpeedModTime(0),
    ShieldModTime(0),
    Immune(0),
    ShieldTex( Vector2u({ static_cast<unsigned int>(BLOCK_SIZE), static_cast<unsigned int>(BLOCK_SIZE) }) ),
    Shield(ShieldTex),
    AttackCooldown(0.3f),

    Attacking(0),

    RunningUp(5.2f,
    {
        frame(3.9f, IntRect({ 0, 40 }, { 12, 20 })),
        frame(2.6f, IntRect({ 36, 40 }, { 12, 20 })),
        frame(1.3f, IntRect({ 24, 40 }, { 12, 20 })),
        frame(0.0f, IntRect({ 12, 40 }, { 12, 20 })),
    }),

    RunningDown(5.2f,
    {
        frame(3.9f, IntRect({ 0, 0 }, { 12, 20 })),
        frame(2.6f, IntRect({ 36, 0 }, { 12, 20 })),
        frame(1.3f, IntRect({ 24, 0 }, { 12, 20 })),
        frame(0.0f, IntRect({ 12, 0 }, { 12, 20 })),
    }),

    RunningLeft(5.2f,
    {
        frame(3.9f, IntRect({ 0, 20 }, { 12, 20 })),
        frame(2.6f, IntRect({ 36, 20 }, { 12, 20 })),
        frame(1.3f, IntRect({ 24, 20 }, { 12, 20 })),
        frame(0.0f, IntRect({ 12, 20 }, { 12, 20 })),
    }),

    RunningRight(5.2f,
    {
        frame(3.9f, IntRect({ 36, 60 }, { 12, 20 })),
        frame(2.6f, IntRect({ 24, 60 }, { 12, 20 })),
        frame(1.3f, IntRect({ 12, 60 }, { 12, 20 })),
        frame(0.0f, IntRect({ 0, 60 }, { 12, 20 })),
    }),

    AttackLeft(3.2f,
    {
        frame(2.4f, IntRect({ 36, 100 }, { 12, 20 })),
        frame(1.6f, IntRect({ 24, 100 }, { 12, 20 })),
        frame(0.8f, IntRect({ 12, 100 }, { 12, 20 })),
        frame(0.0f, IntRect({ 0, 100 }, { 12, 20 })),
    }),

    AttackRight(3.2f,
    {
        frame(2.4f, IntRect({ 36, 80 }, { 12, 20 })),
        frame(1.6f, IntRect({ 24, 80 }, { 12, 20 })),
        frame(0.8f, IntRect({ 12, 80 }, { 12, 20 })),
        frame(0.0f, IntRect({ 0, 80 }, { 12, 20 })),
    }),

    AttackUp(3.2f,
    {
        frame(2.4f, IntRect({ 0, 40 }, { 12, 20 })),
        frame(1.6f, IntRect({ 36, 40 }, { 12, 20 })),
        frame(0.8f, IntRect({ 24, 40 }, { 12, 20 })),
        frame(0.0f, IntRect({ 12, 40 }, { 12, 20 })),
    }),

    AttackDown(3.2f,
    {
        frame(2.4f, IntRect({ 0, 120 }, { 12, 20 })),
        frame(1.6f, IntRect({ 36, 120 }, { 12, 20 })),
        frame(0.8f, IntRect({ 24, 120 }, { 12, 20 })),
        frame(0.0f, IntRect({ 12, 120 }, { 12, 20 })),
    })
{
    //starting frame
    RunningDown.update(0.0f, 0.0f);
    CurrentFrame = RunningDown.getRect();

    //scaling
    Pg.setScale({ 2.5f, 2.5f });

    this->PropsInit();

    std::cout << std::endl << "Player " << Name << " created" << std::endl;
}

player::~player()
{
    for (tile* h : Hearts) { delete h; }
    Hearts.clear();

    for (bullet* b : Bullets) { delete b; }
    Bullets.clear();
}

int player::getScore()
{
    return Score;
}

void player::incScore()
{
    Score++;
}

void player::heal(float life)
{
    Life += life;
    if(Life > 3.0f) { Life = 3.0f; }

    this->hearts(Hearts);
}

std::vector<tile*>* player::getHearts()
{
    return &Hearts;
}

std::vector<bullet*>* player::getBullets()
{
    return &Bullets;
}

void player::buffSpeed(float speed, float time)
{
    SpeedMod = speed;    //effect 
    SpeedModTime += time; //time
}

void player::shield(float time)
{
    Immune = true;        //effect
    ShieldModTime += time; //time
}

void player::modifiersUpdate()
{
    //speed
        //start
        if(SpeedMod != 0 && SpeedModClock.getElapsedTime().asMilliseconds() == 0 ) 
            SpeedModClock.restart();

        //reset
        if((float)(SpeedModClock.getElapsedTime().asMilliseconds() / 1000) == SpeedModTime)
        {
            //reset
            SpeedMod = 0;
            
            SpeedModTime = 0;

            SpeedModClock.stop();
            SpeedModClock.reset();
        }

    //shield
        //start
        if (Immune && ShieldModClock.getElapsedTime().asMilliseconds() == 0 ) 
            ShieldModClock.restart();

        //reset
        if((float)(ShieldModClock.getElapsedTime().asMilliseconds() / 1000) == ShieldModTime)
        {
            //reset
            Immune = 0;
            
            ShieldModTime = 0;

            ShieldModClock.stop();
            ShieldModClock.reset();
        }
}

void player::getDamage(float damage)
{
    if(Immune)
        return;
    
    character::getDamage(damage);

    this->hearts(Hearts);
}

void player::attack(float deltatime)
{
    static Direction attackDirection = NONE;
    if (Keyboard::isKeyPressed(Keyboard::Key::Space))
    {
          Attacking = true;
          if (attackDirection == NONE)
            attackDirection = LastDirection;
    }

    if (Attacking && Cooldown.getElapsedTime().asSeconds() >= AttackCooldown) 
    { 
        //when the animation ends
        if (AttackRight.getTime() >= AttackRight.getLenght()-0.01f || AttackLeft.getTime() >= AttackLeft.getLenght()-0.01f || 
            AttackUp.getTime() >= AttackUp.getLenght()-0.01f || AttackDown.getTime() >= AttackDown.getLenght()-0.01f)
        {
            //restart animation
            AttackRight.reset();
            AttackLeft.reset();
            AttackUp.reset();
            AttackDown.reset();
            Attacking = false;
            //restart Cooldown
            Cooldown.restart();

            //result
            Bullets.push_back(new bullet(attackDirection, PosX+(Width/2), PosY+(Height/2), Strenght));
            attackDirection = NONE;
        }

        //animation
        if (attackDirection == RIGHT)
        {
            AttackRight.update(0.01f, deltatime);

            if ( !(AttackRight.getTime() >= AttackRight.getLenght()-0.01f) )
            {
                CurrentFrame = AttackRight.getRect();
                Pg.setTextureRect(CurrentFrame);        //don't know why cause it's already in the update method
            }                                           //but without it doesn't work
        }                                           
        else if (attackDirection == LEFT)
        {
            AttackLeft.update(0.01f, deltatime);

            //set the frame
            if ( !(AttackLeft.getTime() >= AttackLeft.getLenght()-0.01f) )
            {
                CurrentFrame = AttackLeft.getRect();
                Pg.setTextureRect(CurrentFrame);    
            }    
        }                                
        else if (attackDirection == UP)
        {
            AttackUp.update(0.01f, deltatime);

            //set the frame
            if ( !(AttackUp.getTime() >= AttackUp.getLenght()-0.01f) )
            {
                CurrentFrame = AttackUp.getRect();
                Pg.setTextureRect(CurrentFrame);    
            }    
        }                              
        else if (attackDirection == DOWN)
        {
            AttackDown.update(0.01f, deltatime);

            //set the frame
            if ( !(AttackDown.getTime() >= AttackDown.getLenght()-0.01f) )
            {
                CurrentFrame = AttackDown.getRect();
                Pg.setTextureRect(CurrentFrame);    
            }    
        }                                
    } 
    else //attack finished
    {
        AttackLeft.reset();
        AttackRight.reset();
        Attacking = false;
    }
}

void player::hearts(std::vector<tile *>& hearts)
{
    float life = Life;

    for (tile* h : hearts) { delete h; }
    hearts.clear();

    //full hearts
    while (life >= 1.0f)
    { 
        hearts.push_back( new fullHeart((MAP_WIDHT-hearts.size()-1)*BLOCK_SIZE, 0.0f) ); 

        life -= 1.0f;
    }

    //half hearts
    if (life == 0.5) 
        hearts.push_back( new halfHeart((MAP_WIDHT-hearts.size()-1)*BLOCK_SIZE, 0.0f) ); 

    //empty hearts
    while (hearts.size() != 3)
        hearts.push_back( new heart((MAP_WIDHT-hearts.size()-1)*BLOCK_SIZE, 0.0f) ); 
}

void player::moveForward()
{
    SpeedY += -(stdSpeed + SpeedMod);
}
void player::moveLeft()
{
    SpeedX += -(stdSpeed + SpeedMod);
}
void player::moveRight()
{
    SpeedX += +(stdSpeed + SpeedMod);
}
void player::moveBack()
{
    SpeedY += +(stdSpeed + SpeedMod);
}

void player::movement(float deltatime)
{
    //movement
    if (Keyboard::isKeyPressed(Keyboard::Key::W))
    {
        //movement
        moveForward();

        //animation update
        RunningUp.update(0.01, deltatime);
        CurrentFrame = RunningUp.getRect();
        LastDirection = UP;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        //movement
        moveBack();

        //animation update
        RunningDown.update(0.01, deltatime);
        CurrentFrame = RunningDown.getRect();
        LastDirection = DOWN;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::A))
    {
        //movement
        moveLeft();

        //animation update
        RunningLeft.update(0.01, deltatime);
        CurrentFrame = RunningLeft.getRect();
        LastDirection = LEFT;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::D))
    {
        //movement
        moveRight();

        //animation update
        RunningRight.update(0.01, deltatime);
        CurrentFrame = RunningRight.getRect();
        LastDirection = RIGHT;
    }

    if  (!Keyboard::isKeyPressed(Keyboard::Key::W) &&
         !Keyboard::isKeyPressed(Keyboard::Key::S) &&
         !Keyboard::isKeyPressed(Keyboard::Key::A) &&
         !Keyboard::isKeyPressed(Keyboard::Key::D))
    {
        switch (LastDirection)
        {
        case UP:
            RunningUp.update(0.0f, 0.0f);    
            CurrentFrame = RunningUp.getRect();

            break;
        case DOWN:
            RunningDown.update(0.0f, 0.0f);    
            CurrentFrame = RunningDown.getRect();    

            break;
        case LEFT:
            RunningLeft.update(0.0f, 0.0f);    
            CurrentFrame = RunningLeft.getRect();
            
            break;
        case RIGHT:
            RunningRight.update(0.0f, 0.0f);    
            CurrentFrame = RunningRight.getRect();    

            break;
        default:
            break;
        }
    }
}

void player::drawProps(RenderWindow *window)
{
    if (ShieldModTime > 0.0f) 
    {  
        Shield.setPosition( { PosX, PosY+10 } );
        window->draw(Shield); 
    }
}

//BALD GUY INTRECTS
/*RunningUp(3.2f,
    {
        frame(2.4f, IntRect({ 690, 285 }, { 230, 280 })),
        frame(1.6f, IntRect({ 460, 285 }, { 230, 280 })),
        frame(0.8f, IntRect({ 230, 285 }, { 230, 280 })),
        frame(0.0f, IntRect({ 0, 285 }, { 230, 280 })),
    }),

    RunningDown(3.2f,
    {
        frame(2.4f, IntRect({ 690, 0 }, { 230, 280 })),
        frame(1.6f, IntRect({ 460, 0 }, { 230, 280 })),
        frame(0.8f, IntRect({ 230, 0 }, { 230, 280 })),
        frame(0.0f, IntRect({ 0, 0 }, { 230, 280 })),
    }),

    RunningLeft(3.2f,
    {
        frame(2.4f, IntRect({ 690, 560 }, { 230, 275 })),
        frame(1.6f, IntRect({ 460, 560 }, { 230, 275 })),
        frame(0.8f, IntRect({ 230, 560 }, { 230, 275 })),
        frame(0.0f, IntRect({ 0, 560 }, { 230, 275 })),
    }),

    RunningRight(3.2f,
    {
        frame(2.4f, IntRect({ 690, 850 }, { 230, 280 })),
        frame(1.6f, IntRect({ 460, 850 }, { 230, 280 })),
        frame(0.8f, IntRect({ 230, 850 }, { 230, 280 })),
        frame(0.0f, IntRect({ 0, 850 }, { 230, 280 })),
    })*/