#include "animation.hpp"

#include <iostream>

animation::animation(float lenght, std::vector<frame> frames) :
    Lenght(lenght),
    Frames(frames)
{
}

void animation::setFrame(std::vector<frame> frames)
{
    Frames = frames;
}

IntRect animation::getRect()
{
    while(Time > Lenght)
        Time -= Lenght;

    for (auto& frame : Frames)
    {
        if (Time >= frame.Time)
            return frame.Rect;
    }
    
    //that's an error cause it has to find one in the loop
    return IntRect();
}

float animation::getTime()
{
    return Time;
}

float animation::getLenght()
{
    return Lenght;
}

void animation::update(float time, float deltatime)
{
    if (time == 0.0f) { Time = Lenght-0.1f; }
    else { Time += time * deltatime; }
}

void animation::reset()
{
    Time = 0.0f;
}