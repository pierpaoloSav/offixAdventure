#include <iostream>
#include <fstream>
#include <sstream>

#include "map.hpp"

void map::mapInit()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDHT; j++)
        {
            Tmap[i][j] = nullptr;
        }
    }
}

void map::mapFilling(std::string mapFile)
{
    std::ifstream file(mapFile);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    int rows = 0;
    int cols = 0;
    std::string line;
    while (std::getline(file, line) && rows < MAP_HEIGHT) 
    {
        std::stringstream ss(line);

        int value;

        cols = 0;
        while (ss >> value && cols < MAP_WIDHT) 
        {
            switch (value) 
            {
            case 0:
                Tmap[rows][cols] = new grass(cols*BLOCK_SIZE, rows*BLOCK_SIZE);

                break;
            case 1:
                Tmap[rows][cols] = new rock(cols*BLOCK_SIZE, rows*BLOCK_SIZE);

                break;
            case 2:
                Tmap[rows][cols] = new rock2(cols*BLOCK_SIZE, rows*BLOCK_SIZE);

                break;
            case 3:
                Tmap[rows][cols] = new rock3(cols*BLOCK_SIZE, rows*BLOCK_SIZE);

                break;
            case 4:
                Tmap[rows][cols] = new water(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 5:
                Tmap[rows][cols] = new water1(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 6:
                Tmap[rows][cols] = new water2(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 7:
                Tmap[rows][cols] = new water3(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 8:
                Tmap[rows][cols] = new water4(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 9:
                Tmap[rows][cols] = new water5(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 10:
                Tmap[rows][cols] = new water6(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 11:
                Tmap[rows][cols] = new water7(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 12:
                Tmap[rows][cols] = new water8(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 13:
                Tmap[rows][cols] = new water9(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 14:
                Tmap[rows][cols] = new water10(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 15:
                Tmap[rows][cols] = new water11(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 16:
                Tmap[rows][cols] = new water12(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    
            
                break;
            case 17:
                Tmap[rows][cols] = new water13(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    

                break;
            case 18:
                Tmap[rows][cols] = new hut(cols*BLOCK_SIZE, rows*BLOCK_SIZE);    

                EnemySpawners.push_back(dynamic_cast<hut*>(Tmap[rows][cols]));

                break;
            case 19:
                Tmap[rows][cols] = new colSpawner(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                ColSpawners.push_back(dynamic_cast<colSpawner*>(Tmap[rows][cols]));

                break;
            case 20:
                Tmap[rows][cols] = new rareSpawner(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                ColSpawners.push_back(dynamic_cast<colSpawner*>(Tmap[rows][cols]));
                
                break;
            case 21:
                Tmap[rows][cols] = new path(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                break;
            case 22:
                Tmap[rows][cols] = new path1(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                break;
            case 23:
                Tmap[rows][cols] = new path2(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                break;
            case 24:
                Tmap[rows][cols] = new path3(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                break;
            case 25:
                Tmap[rows][cols] = new path4(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                break;
            case 26:
                Tmap[rows][cols] = new path5(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                break;
            case 27:
                Tmap[rows][cols] = new path6(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                break;
            case 28:
                Tmap[rows][cols] = new path7(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                break;
            case 29:
                Tmap[rows][cols] = new path8(cols*BLOCK_SIZE, rows*BLOCK_SIZE);   

                break;
            case 30:
                Tmap[rows][cols] = new path9(cols*BLOCK_SIZE, rows*BLOCK_SIZE);

                break;
            case 31:
                Tmap[rows][cols] = new path10(cols*BLOCK_SIZE, rows*BLOCK_SIZE);

                break;
            case 32:
                Tmap[rows][cols] = new path11(cols*BLOCK_SIZE, rows*BLOCK_SIZE);

                break;
            case 33:
                Tmap[rows][cols] = new path12(cols*BLOCK_SIZE, rows*BLOCK_SIZE);

                break;
            case 34:
                Tmap[rows][cols] = new tree(cols*BLOCK_SIZE, rows*BLOCK_SIZE);

                break;
            default:
                break;
            }

            cols++;
        }
        rows++;
    }
    file.close();
}

void map::collisionsInit()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDHT; j++)
        {
            if(Tmap[i][j] != nullptr && Tmap[i][j]->getCollision()) { Collisions.push_back(Tmap[i][j]); }
        }
    }
}

void map::scaleMap(float scale)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDHT; j++)
        {
            Tmap[i][j]->setScale(SCALE);
        }
    }
}

map::map(std::string mapFile)
{
    this->mapInit();
    this->mapFilling(mapFile);
    this->collisionsInit();
}

map::~map()
{
    for (int i = 0; i < MAP_HEIGHT; ++i) 
    {
        for (int j = 0; j < MAP_WIDHT; ++j) 
        {
            delete Tmap[i][j];
            Tmap[i][j] = nullptr;
        }
    }

    Collisions.clear();
    
    ColSpawners.clear();
}

std::vector<tile*>* map::getCollisions()
{
    return &Collisions;
}

std::vector<hut*>* map::getEnemySpawners()
{
    return &EnemySpawners;
}

std::vector<colSpawner*>* map::getColSpawners()
{
    return &ColSpawners;
}

void map::drawMap(RenderWindow *window)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDHT; j++)
        {
            if (Tmap[i][j] != nullptr) { Tmap[i][j]->drawTile(window); }
        }
    }
}
