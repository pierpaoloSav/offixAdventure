#include "menu.hpp"

#include <iostream>

void menu::BackgroundInit()
{
    if (!BackgroundTex.loadFromFile("../res/background.png")) { std::cerr << "ERROR: can't load the texture" << std::endl; }
    Background.setPosition(Vector2f({0, 0}));
    Background.setScale(Vector2f{float(SCALE), float(SCALE)});
}

menu::menu(RenderWindow *window) :
    gameState(window),

    BackgroundTex(Vector2u({WIDTH, HEIGHT})),
    Background(BackgroundTex),

    ButtonPlay("PLAY", 64, 32, 288, 143, "../res/playButton.png"),
    ButtonRule("MENU", 64, 32, 288, 185, "../res/ruleButton.png") //TODO: implement
{
    this->BackgroundInit();

    std::cout << "\nMENU\n";
}

menu::~menu()
{
    std::cout << "CLOSING MENU\n";
}

int menu::Update()
{
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
                Background.setScale(Vector2f{float(SCALE), float(SCALE)});
                ButtonPlay.setScale(SCALE);
                ButtonRule.setScale(SCALE);
        }

        //key pressed 
        if (auto *key = event->getIf<Event::KeyPressed>())
        {    
            if (key->scancode == Keyboard::Scancode::Escape) { Window->close(); }
            if (key->scancode == Keyboard::Scancode::P) { return 2; }
        }

        //mouse click
        if (event->is<Event::MouseButtonReleased>()) 
        {
            Vector2f mousePosInView = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));
            if(ButtonPlay.checkPressed(mousePosInView.x, mousePosInView.y))
                return 2; 
        }
    }    

    return 0;
}

void menu::Render()
{
    Window->clear();
    
        Window->draw(Background);

        ButtonPlay.drawButton(Window);
        ButtonRule.drawButton(Window);

    Window->display();
}