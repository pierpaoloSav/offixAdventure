#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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
    //TODO: this values will be standards in player class except the pos
    Offix = new player(11, 15, 20*BLOCK_SIZE, 10*BLOCK_SIZE, 0, -5.0f, 3.0f, 0.075f, 1.5f, "PIETRO");
    //init Hearts
    Offix->getDamage(0.0f);    

    //holder
    Bullets = Offix->getBullets(); 
}

void game::TextInit()
{
    TextScore.setPosition({ float(38*BLOCK_SIZE*SCALE), float(1*BLOCK_SIZE*SCALE) });
    TextScore.setFillColor(Color::White);
    TextScore.setCharacterSize(15.0f*SCALE);
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
    this->TextInit();

    std::cout << "\nGAME STARTED\n";
}

game::~game()
{
    delete Offix;

    for (collectible* c : Collectibles) { delete c; }
    Collectibles.clear();

    for (enemy* e : Enemies) { delete e; }
    Enemies.clear();

    std::cout << "GAME ENDED\n";
}

void game::SpawnCollectibles()
{
    static const int nSpawners = World.getColSpawners()->size();
    Time colTime = ColTimer.getElapsedTime();
    if((int)colTime.asSeconds() >= ColSpawnTime && nSpawners > FullSpawners)
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
    else if ((int)colTime.asSeconds() == ColSpawnTime) { ColTimer.restart(); }
}

void game::SpawnEnemies()
{
    static const int nSpawners = World.getEnemySpawners()->size();
    Time enemyTime = EnemyTimer.getElapsedTime();
    if((int)enemyTime.asSeconds() >= EnemySpawnTime)
    {
        //reset time
        EnemyTimer.restart();

        //random spawner
        int randIndex;
        randIndex = rand()%nSpawners;
        hut* randTile = World.getEnemySpawners()->at(randIndex);

        //spawn
        //TODO: this values will be standards in player class except the pos
        Enemies.push_back( new enemy(11, 15, randTile->getPosX(), randTile->getPosY(), 0, -5, 3.0f, 0.070f, 3.0f, "ENEMY") );
    }
    else if ((int)enemyTime.asSeconds() == EnemySpawnTime) { EnemyTimer.restart(); }
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

int game::Update()
{
    //DELTA TIME FOR FRAME INDIPENDENT MOVEMENT 
    sf::Time timer = DeltaTimeClock.restart();
    float deltaTime = timer.asMilliseconds();

    //---------------EVENT_LISTENER---------------//
    while (const std::optional event = Window->pollEvent())
    {
        //window closed
        if (event->is<Event::Closed>()) { Window->close(); }
 
        //window resized
        if (event->is<Event::Resized>()) 
        {
            //new dimensions
            float newW = Window->getSize().x;
            float newH = Window->getSize().y;
            if (newW < WIDTH || newH < HEIGHT) 
            {
                newW = std::max(newW, float(WIDTH));
                newH = std::max(newH, float(HEIGHT));
                Window->setSize(Vector2u(newW, newH));
            }

            //set scale
            if (newW/WIDTH < newH/HEIGHT)
                SCALE = newW/WIDTH;
            else
                SCALE = newH/HEIGHT;

            //set borders
            LEFTBORDER = BLOCK_SIZE*SCALE;
            RIGHTBORDER = WIDTH*SCALE - LEFTBORDER;
            UPBORDER = BLOCK_SIZE*SCALE;
            DOWNBORDER = HEIGHT*SCALE - UPBORDER;

            //set view    
            FloatRect visible({(WIDTH*SCALE-newW)/2, (HEIGHT*SCALE-newH)/2}, {newW, newH}); 
            Window->setView(View(visible));

            //updating objects
                //characters
                Offix->setScale(SCALE);
                for (enemy *e : Enemies) { e->setScale(SCALE); }
                //map
                World.scaleMap(SCALE);
                //collectibles
                for (collectible *c : Collectibles) { c->setScale(SCALE); }
                //text
                this->TextInit();
        }

        //key pressed
        if (auto *key = event->getIf<Event::KeyPressed>())
        {
            if (key->scancode == Keyboard::Scancode::T) { toggleHitbox = !toggleHitbox; }
            
            if (key->scancode == Keyboard::Scancode::Escape) { return 3; }
        }
    }      

    //---------------GAME_UPDATING--------------//
    if(!Offix->checkAlive()) { return 4; }
    
    this->UpdatePlayer(deltaTime);

    this->UpdateEnemies(deltaTime);

    this->UpdateCombat(deltaTime);

    this->UpdateCollectibles();

    return 0;
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
        
        for (enemy* e : Enemies) 
            e->drawCharacter(Window);

        Window->draw(TextScore);

    Window->display();
}