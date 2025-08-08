#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

//map dimension variables 
const uint WIDTH = 640;
const uint HEIGHT = 360;

extern uint SCALE;

const uint BLOCK_SIZE = 16;
const uint MAP_HEIGHT = 23;
const uint MAP_WIDHT = 40;
const uint DIAGONAL = 57;

extern uint LEFTBORDER;
extern uint RIGHTBORDER;
extern uint UPBORDER;
extern uint DOWNBORDER;

//base function to check collisions between rectangles 
bool checkCollision(RectangleShape &rect1, RectangleShape &rect2);

//math
int pointsDistance(int xOne, int yOne, int xTwo, int yTwo);

//other
extern bool toggleHitbox;