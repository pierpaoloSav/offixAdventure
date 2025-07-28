#include "engine.hpp"

engine::engine() :
    Window(VideoMode({ WIDTH, HEIGHT }), "Offix Adventure", Style::Titlebar | Style::Close),

    Gaming(0)
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
    while(!States.top()->isShutting())
    {
        if (!States.top()->isRunning())
        {
            this->popState();

            if (Gaming)
                this->pushState(new menu(&Window));
            else
                this->pushState(new game(&Window));
            Gaming = !Gaming;
        }

        States.top()->Loop();
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