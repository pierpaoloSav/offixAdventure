#include <iostream>
#include <cstdlib>
#include <ctime>

#include "game.hpp"
#include "menu.hpp"

void game::ClocksInit()
{
    DeltaTimeClock.start();
    ColTimer.start();
    srand(time(NULL));
}

void game::OffixInit()
{
    Offix = new player(30, 40, 15*BLOCK_SIZE, 8*BLOCK_SIZE, +1.5f, -9.0f, 3.0f, 0.15f, 1.5f, "PIETRO");
    Offix->getDamage(0.0f);    //init Hearts
}

game::game(RenderWindow *window) : 
    gameState(window),

    World("../res/map.txt"),

    Roboto("../res/robotoRegular.ttf"),
    TextScore(Roboto, "x0"),

    ColSpawnTime(5.0),
    EnemySpawnTime(10.0),

    FullSpawners(0)
{
    this->ClocksInit();
    this->OffixInit();

    //holder
    Bullets = Offix->getBullets(); 

    //text
    TextScore.setPosition({ 30*BLOCK_SIZE, 1*BLOCK_SIZE });
    TextScore.setFillColor(Color::White);

    std::cout << "Game started" << std::endl;
}

game::~game()
{
    delete Offix;

    for (collectible* c : Collectibles) { delete c; }
    Collectibles.clear();

    for (enemy* e : Enemies) { delete e; }
    Enemies.clear();

    std::cout << "Game ended" << std::endl;
}

void game::SpawnCollectibles()
{
    static const int nSpawners = World.getColSpawners()->size();
    Time colTimer = ColTimer.getElapsedTime();
    if((int)colTimer.asSeconds() >= ColSpawnTime && nSpawners > FullSpawners)
    {
        //reset time
        ColTimer.restart();

        //search a free spawner
        int randIndex;
        do
        {
            randIndex = rand()%nSpawners;
        }
        while ((World.getColSpawners()->at(randIndex))->getFull());
        colSpawner* randTile = World.getColSpawners()->at(randIndex);

        //set the spawner full
        randTile->setFull(true);

        //creating the collectible
        if(randTile->getRareness()) 
        {  
            int prob = ( rand()%100 ) + 1;
            
            if (prob >= 1 && prob <= 50)
                Collectibles.emplace_back(new hamburger(randTile->getPosX(), randTile->getPosY())); 
            else if (prob > 50 && prob <= 70)
                Collectibles.emplace_back(new chili(randTile->getPosX(), randTile->getPosY())); 
            else if (prob > 70 && prob <= 85)
                Collectibles.emplace_back(new pizza(randTile->getPosX(), randTile->getPosY())); 
            else if (prob > 85 && prob <= 100)
                Collectibles.emplace_back(new shield(randTile->getPosX(), randTile->getPosY())); 
        }
        else 
            Collectibles.emplace_back(new hamburger(randTile->getPosX(), randTile->getPosY())); 
        
        //setting the index for the collectible
        Collectibles.back()->setSpawnerIndex(randIndex);

        //one more spawner filled
        FullSpawners++;
    }
    else if ((int)colTimer.asSeconds() == 11) { ColTimer.restart(); }
}

void game::SpawnEnemies()
{
    static const int nSpawners = 5;
    static const int spawners[nSpawners][2] = {
        {16, 7}, {12, 15}, {12, 3}, {25, 5}, {30, 3}
    };  

    Time enemyTime = EnemyTimer.getElapsedTime();
    if((int)enemyTime.asSeconds() >= EnemySpawnTime)
    {
        //reset time
        EnemyTimer.restart();

        //random spawner
        int randIndex;
        randIndex = rand()%nSpawners;

        //spawn
        Enemies.push_back( new enemy(30, 40, spawners[randIndex][0] * BLOCK_SIZE, spawners[randIndex][1] * BLOCK_SIZE, +1.5f, -9.0f, 3.0f, 0.13f, 3.0f, "ENEMY") );
    }
}

void game::CheckCollectibles()
{
    for (int i = 0; i < Collectibles.size(); i++)
    {
        if (Collectibles[i]->checkTaked(Offix)) 
        { 
            //setting the spawner no more filled
            (World.getColSpawners()->at(Collectibles[i]->getSpawnerIndex()))->setFull(false);

            //erasing the collectible
            delete Collectibles[i];
            Collectibles.erase(Collectibles.begin()+i);

            //minus one spawner filled
            FullSpawners--;
        }
    }   
}

void game::UpdatePlayer(float deltatime)
{
    //player
    Offix->movement(deltatime);
    Offix->update(deltatime, World.getCollisions()); 
    Offix->modifiersUpdate();

    //bullets
    for (auto it = Bullets->begin(); it != Bullets->end(); )
    {
        bullet* b = *it;
        b->movement(deltatime);
        b->update(deltatime, World.getCollisions());

        if (b->isColliding())
        {
            delete b;                     
            it = Bullets->erase(it);       
        }
        else
        {
            ++it;                         
        }
    }
}

void game::UpdateEnemies(float deltatime)
{
    this->SpawnEnemies();

    for (enemy* e : Enemies) 
    {
        e->movement(deltatime, Offix);
        e->update(deltatime, World.getCollisions());
    }
}

void game::UpdateCombat(float deltatime)
{
    //bullets shoot
    Offix->attack(deltatime);

    if(Enemies.size() == 0) return;

    //player gets damage
    for (enemy* e : Enemies)
        Offix->getDamage(e->attack(Offix, deltatime));

    //enemy gets damage
    for (int j = 0; j < Bullets->size(); j++)
    {
        bullet* b = Bullets->at(j);

        for (int i = 0; i < Enemies.size(); i++)
        {
            enemy *e = Enemies[i];

            if(checkCollision(b->getHitbox(), e->getHitbox()))
            {
                //enemy damage
                e->getDamage(b->getStrenght());
                if(!e->checkAlive())
                {
                    delete e;
                    Enemies.erase(Enemies.begin()+i);
                }
                
                //bullet breaks
                delete b;                     
                Bullets->erase(Bullets->begin()+j);       
            }
        }
    }
}

void game::UpdateCollectibles()
{
    //collectibles
    this->SpawnCollectibles();
    this->CheckCollectibles();

    //score
    TextScore.setString(String("x") + String( std::to_string(Offix->getScore()) ));
}

void game::Update()
{
    //DELTA TIME FOR FRAME INDIPENDENT MOVEMENT 
    sf::Time timer = DeltaTimeClock.restart();
    float deltaTime = timer.asMilliseconds();

    //---------------EVENT_LISTENER---------------//
    while (const std::optional event = Window->pollEvent())
    {
        //window closed
        if (event->is<Event::Closed>()) { Shutting = 1; }
 
        //TOGGLE_HITBOX 
        if (auto *key = event->getIf<Event::KeyPressed>())
            if (key->scancode == Keyboard::Scancode::T) { toggleHitbox = !toggleHitbox; }
    }      

    //---------------GAME_UPDATING--------------//
    if(!Offix->checkAlive()) { Running = 0; }
    if (Running)
    {
        this->UpdatePlayer(deltaTime);

        this->UpdateEnemies(deltaTime);

        this->UpdateCombat(deltaTime);

        this->UpdateCollectibles();
    }
    else //TODO: pausa con pulsante che quando viene clickato fa tornare al menu
        std::cout << "\nGAME OVER\n";
}

void game::Render()
{
    //---------------RENDER---------------//
    Window->clear();

        World.drawMap(Window);

        Offix->drawCharacter(Window);
        Offix->drawProps(Window);

        for (collectible* c : Collectibles) 
            c->drawCollectible(Window);

        for (bullet* b : *Bullets)
            b->drawCharacter(Window);

        for (tile* h : *Offix->getHearts()) 
            h->drawTile(Window);
        
        for (enemy* e : Enemies) 
            e->drawCharacter(Window);

        Window->draw(TextScore);

    Window->display();
}