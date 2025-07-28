#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

//map dimension variables 
const int WIDTH = 1280;
const int HEIGHT = 720;

const int LEFTBORDER = 40;
const int RIGHTBORDER = WIDTH - 40;
const int UPBORDER = 40;
const int DOWNBORDER = HEIGHT - 40;

const int MAP_HEIGHT = 18;
const int MAP_WIDHT = 32;
const int BLOCK_SIZE = 40;
const int DIAGONAL = 57;

//base function to check collisions between rectangles 
bool checkCollision(RectangleShape &rect1, RectangleShape &rect2);

//math
int pointsDistance(int xOne, int yOne, int xTwo, int yTwo);

//other
extern bool toggleHitbox;