#include "enemy.hpp"

enemy::enemy(int width, int height, float posX, float posY, float offsetX, float offsetY, float life, float speed, float strenght, std::string name, std::string pgTexture) :
    character(width, height, posX, posY, offsetX, offsetY, life, speed, strenght, false, name, pgTexture),
    
    MovingSide(0),

    RunningUp(3.2f,
    {
        frame(2.4f, IntRect({ 0, 40 }, { 12, 20 })),
        frame(1.6f, IntRect({ 36, 40 }, { 12, 20 })),
        frame(0.8f, IntRect({ 24, 40 }, { 12, 20 })),
        frame(0.0f, IntRect({ 12, 40 }, { 12, 20 })),
    }),

    RunningDown(3.2f,
    {
        frame(2.4f, IntRect({ 0, 0 }, { 12, 20 })),
        frame(1.6f, IntRect({ 36, 0 }, { 12, 20 })),
        frame(0.8f, IntRect({ 24, 0 }, { 12, 20 })),
        frame(0.0f, IntRect({ 12, 0 }, { 12, 20 })),
    }),

    RunningLeft(3.2f,
    {
        frame(2.4f, IntRect({ 0, 20 }, { 12, 20 })),
        frame(1.6f, IntRect({ 36, 20 }, { 12, 20 })),
        frame(0.8f, IntRect({ 24, 20 }, { 12, 20 })),
        frame(0.0f, IntRect({ 12, 20 }, { 12, 20 })),
    }),

    RunningRight(3.2f,
    {
        frame(2.4f, IntRect({ 36, 60 }, { 12, 20 })),
        frame(1.6f, IntRect({ 24, 60 }, { 12, 20 })),
        frame(0.8f, IntRect({ 12, 60 }, { 12, 20 })),
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
    })
{
    //starting frame
    RunningDown.update(0.0, 0.0);
    CurrentFrame = RunningDown.getRect();

    //resetting animations
    RunningUp.reset();
    RunningLeft.reset();
    RunningRight.reset();
    AttackLeft.reset();
    AttackRight.reset();

    std::cout << std::endl << "Enemy " << Name << " created" << std::endl;
}

float enemy::attack(character *attacked, float deltatime)
{
    //player position
    float pPosX = attacked->getPosX()*Scale;
    float pPosY = attacked->getPosY()*Scale;
    //distance 
    float distance = pointsDistance( (int)PosX, (int)PosY, (int)pPosX, (int)pPosY);

    if (distance <= Width + 10 && Cooldown.getElapsedTime().asSeconds() >= 2) 
    { 
        //when the animation ends
        if (AttackRight.getTime() > AttackRight.getLenght()-0.01f || AttackLeft.getTime() > AttackLeft.getLenght()-0.01f) 
        {
            //restart animation
            AttackRight.reset();
            AttackLeft.reset();            
            //restart Cooldown
            Cooldown.restart();

            //result
            if (distance <= Width + 10)
                return Strenght;
        }

        //animation
        if (LastDirection == RIGHT)
        {
            //condition to check switching sides during the animation
            if (AttackLeft.getTime() != 0.0f)
            {
                AttackRight.update(AttackLeft.getTime(), deltatime);
                AttackLeft.reset();
            }
            else
                AttackRight.update(0.01f, deltatime);

            if ( !(AttackRight.getTime() >= AttackRight.getLenght()-0.01f) )
            {
                CurrentFrame = AttackRight.getRect();
                Pg.setTextureRect(CurrentFrame);        //don't know why cause it's already in the update method
            }                                           //but without it doesn't work
        }                                           
        else
        {
            //condition to check switching sides during the animation
            if (AttackRight.getTime() != 0.0f)
            {
                AttackLeft.update(AttackRight.getTime(), deltatime);
                AttackRight.reset();
            }
            else
                AttackLeft.update(0.01f, deltatime);

            //set the frame
            if ( !(AttackLeft.getTime() >= AttackLeft.getLenght()-0.01f) )
            {
                CurrentFrame = AttackLeft.getRect();
                Pg.setTextureRect(CurrentFrame);    
            }      
        }                                
    } 
    else //attack dodged
    {
        AttackLeft.reset();
        AttackRight.reset();
    }

    return 0.0f;
}

void enemy::movement(float deltatime, player* pg)
{
    //player position
    float pPosX = pg->getPosX()*Scale;
    float pPosY = pg->getPosY()*Scale;

    //distance 
    float distance = pointsDistance( (int)PosX, (int)PosY, (int)pPosX, (int)pPosY);

    if (distance <= BLOCK_SIZE*SCALE*2 && distance >= Width) //near
    {
        //follow the player directly
        if (pPosY > PosY)
        {
            //movement
            moveBack();
            
            //animation update
            RunningDown.update(0.01f, deltatime);
            CurrentFrame = RunningDown.getRect();
        }
        else 
        {
            //movement
            moveForward();
            
            //animation update
            RunningUp.update(0.01f, deltatime);
            CurrentFrame = RunningUp.getRect();
        }
        if (pPosX > PosX && (pPosX-PosX > 5 || PosX-pPosX > 5)) 
        {
            //movement
            moveRight();
            LastDirection = RIGHT; //don't know why cause it's already in the moveRight method
                                   //but without it doesn't work

            //animation update
            RunningRight.update(0.01f, deltatime);
            CurrentFrame = RunningRight.getRect();
        }
        else if (pPosX-PosX > 5 || PosX-pPosX > 5)
        {
            //movement
            moveLeft();
            LastDirection = LEFT; //don't know why cause it's already in the moveLeft method
                                  //but without it doesn't work
            
            //animation update
            RunningLeft.update(0.01f, deltatime);
            CurrentFrame = RunningLeft.getRect();
        }
    }
    else                            //too far
    {
        //TODO: pathfinding

    }
}
