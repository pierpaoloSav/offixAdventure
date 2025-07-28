#pragma once

#include <SFML/Graphics.hpp>

#include "gameState.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "tile.hpp"
#include "map.hpp"
#include "collectible.hpp"
#include "bullet.hpp"

using namespace sf;

class game : public gameState
{
public:
    game(RenderWindow *window);
    ~game();
private:
    void ClocksInit();
    void OffixInit();

    void SpawnCollectibles();
    void SpawnEnemies();
    void CheckCollectibles();
    void Update();
        void UpdatePlayer(float deltatime);
        void UpdateEnemies(float deltatime);
        void UpdateCombat(float deltatime);
        void UpdateCollectibles();
    void Render();

private:  
    Font Roboto;
    Text TextScore;

    Clock DeltaTimeClock;
    Clock ColTimer;
    Clock EnemyTimer;
    float ColSpawnTime;
    float EnemySpawnTime;

    player *Offix;
    std::vector<bullet*> *Bullets; //holder

    map World;

    std::vector<collectible*> Collectibles;
    int FullSpawners;

    std::vector<enemy*> Enemies;
};