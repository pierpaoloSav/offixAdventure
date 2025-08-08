#include "gameOverMenu.hpp"

#include <iostream>

void gameOverMenu::BackgroundInit()
{
    BackgroundTex.update(*Window);
    Background.setTexture(BackgroundTex);
    Background.setTextureRect(IntRect({int(Window->getSize().x - WIDTH*SCALE)/2, int(Window->getSize().y - HEIGHT*SCALE)/2}, {int(Window->getSize().x), int(Window->getSize().y)}));
    Background.setPosition(Vector2f({0, 0}));

    Overlay.setSize(Vector2f(BackgroundTex.getSize()));
    Overlay.setFillColor(Color(0, 0, 0, 150));
}

void gameOverMenu::ButtonInit()
{
    ButtonPlay.setScale(SCALE);
    ButtonMenu.setScale(SCALE);
}

void gameOverMenu::TextInit()
{
    GameOverText.setFillColor(Color::White);
    GameOverText.setCharacterSize(50.0f*SCALE);

    FloatRect bounds = GameOverText.getLocalBounds();
    GameOverText.setOrigin({ bounds.position.x+bounds.size.x/2, bounds.position.y+bounds.size.y/2});
    GameOverText.setPosition({(WIDTH / 2.f)*SCALE, ((HEIGHT / 2.f)*SCALE)-(50.0f*SCALE)});
}

gameOverMenu::gameOverMenu(RenderWindow *window) :
    gameState(window),

    BackgroundTex(Vector2u({Window->getSize().x, Window->getSize().y})),
    Background(BackgroundTex),

    ButtonPlay("PLAY", 64, 32, 251, 164, "../res/playButton.png"),
    ButtonMenu("MENU", 64, 32, 325, 164, "../res/menuButton.png"),

    GameFont("../res/gameOver.ttf"),
    GameOverText(GameFont, "GAME OVER")
{
    this->BackgroundInit();
    this->ButtonInit();
    this->TextInit();

    std::cout << "\nGAME OVER\n";
}

gameOverMenu::~gameOverMenu()
{
    std::cout << "EXITING GAME OVER MENU\n";
}

int gameOverMenu::Update()
{
    //---------------EVENT_LISTENER---------------//
    while (const std::optional event = Window->pollEvent())
    {
        //window closed
        if (event->is<Event::Closed>()) { Window->close(); }

        //window resized
        if (event->is<Event::Resized>()) 
        {
            //UNRESIZABLE
            Window->setSize(Vector2u(BackgroundTex.getSize().x, BackgroundTex.getSize().y));
        }

        //mouse click
        if (event->is<Event::MouseButtonReleased>()) 
        {
            Vector2f mousePosInView = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));
            if(ButtonPlay.checkPressed(mousePosInView.x, mousePosInView.y))
                return 2; 
            
            if(ButtonMenu.checkPressed(mousePosInView.x, mousePosInView.y))
                return 1; 
        }
    }    

    return 0;
}

void gameOverMenu::Render()
{
    Window->clear();

        Window->draw(Background);
        Window->draw(Overlay);

        Window->draw(GameOverText);

        ButtonPlay.drawButton(Window);
        ButtonMenu.drawButton(Window);

    Window->display();
}
