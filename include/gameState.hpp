#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class gameState {
public:
    gameState(RenderWindow *window) : Window(window) {}
    virtual ~gameState() {}

    virtual int Update() = 0;  //0: nothing | 1: mainMenu | 2: game | 3: pauseMenu | 4: gameOverMenu | 5: Pop State
    virtual void Render() = 0;
    
protected:
    RenderWindow *Window;
};
