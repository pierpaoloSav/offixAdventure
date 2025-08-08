#pragma once 

#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "tile.hpp"

using namespace sf;

class map
{
public:
    map(std::string mapFile);
    ~map();

    std::vector<tile*>* getCollisions();
    std::vector<hut*>* getEnemySpawners();
    std::vector<colSpawner*>* getColSpawners();

    void scaleMap(float scale);
    void drawMap(RenderWindow *window);

private:
    void mapInit();
    void mapFilling(std::string mapFile);
    void collisionsInit();

private:
    tile *Tmap[MAP_HEIGHT][MAP_WIDHT];

    std::vector<tile*> Collisions; 

    std::vector<hut*> EnemySpawners;

    std::vector<colSpawner*> ColSpawners;
};