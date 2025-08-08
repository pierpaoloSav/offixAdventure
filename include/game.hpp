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

    int Update() override;
    void Render() override;
private:
    void ClocksInit();
    void OffixInit();
    void TextInit();

    void SpawnCollectibles();
    void SpawnEnemies();
    void CheckCollectibles();
    
    void UpdatePlayer(float deltatime);
    void UpdateEnemies(float deltatime);
    void UpdateCombat(float deltatime);
    void UpdateCollectibles();

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