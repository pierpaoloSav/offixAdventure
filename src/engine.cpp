#include "engine.hpp"

engine::engine() :
    Window(VideoMode({ WIDTH*2, HEIGHT*2 }), "Offix Adventure"),

    NextState(0)
{
    Window.setFramerateLimit(360);

    //init with the menu
    this->pushState(new menu(&Window));
}

engine::~engine()
{
    Window.close();

    while (!States.empty()) 
    {
        delete States.top();
        States.pop();
    }
}

void engine::Run()
{
    while(Window.isOpen())
    {
        switch (NextState)
        {
        case 1:
            this->popState();
            this->pushState(new menu(&Window));
            break;
        case 2:
            this->popState();
            this->pushState(new game(&Window));
            break;
        case 3:
            this->pushState(new pauseMenu(&Window));
            break;
        case 4:
            this->popState();
            this->pushState(new gameOverMenu(&Window));
            break;
        case 5:
            this->popState();
            break;
        default:
            break;
        }
        
        NextState = States.top()->Update();
        States.top()->Render();
    }
}

void engine::pushState(gameState* state) 
{
    States.push(std::move(state));
}

void engine::popState() 
{
    if (!States.empty()) 
    {
        delete States.top();
        States.pop();
    }
}