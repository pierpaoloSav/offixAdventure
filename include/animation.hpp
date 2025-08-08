#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

struct frame 
{
    frame(float time = 0.0f, IntRect rect = IntRect()) :
        Time(time), Rect(rect)
    {
    }

    float Time;
    IntRect Rect;
};

/*
    Always restart an animation before using it for the first time
*/

class animation
{
public:
    animation(float lenght, std::vector<frame> frames);

    void update(float time, float deltatime);
    void reset();

    //setters
    void setFrame(std::vector<frame> frames);

    //getters
    IntRect getRect();
    float getTime();
    float getLenght();

private:
    std::vector<frame> Frames;
    
    float Time;
    float Lenght;
};