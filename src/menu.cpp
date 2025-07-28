#include "menu.hpp"

#include <iostream>

menu::menu(RenderWindow *window) :
    gameState(window),

    BackgroundTex(Vector2u({WIDTH, HEIGHT})),
    Background(BackgroundTex)
{
    if (!BackgroundTex.loadFromFile("../res/background.png")) { std::cerr << "ERROR: can't load the texture" << std::endl; }
    Background.setPosition(Vector2f({0, 0}));

    std::cout << "\nMENU\n";
}

menu::~menu()
{
    std::cout << "\nCLOSING MENU\n";
}

void menu::Update()
{
    //---------------EVENT_LISTENER---------------//
    while (const std::optional event = Window->pollEvent())
    {
        //window closed
        if (event->is<Event::Closed>()) { Shutting = 1; }

        //start game 
        if (auto *key = event->getIf<Event::KeyPressed>())
            if (key->scancode == Keyboard::Scancode::P) { Running = 0; }
    }    
}

void menu::Render()
{
    Window->clear();
    
        Window->draw(Background);

    Window->display();
}