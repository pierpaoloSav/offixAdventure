#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class gameState {
public:
    gameState(RenderWindow *window) : Window(window) {}
    virtual ~gameState() {}

    void Loop();

    bool isRunning();
    bool isShutting();

protected:
    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    RenderWindow *Window;

    bool Running = 1;
    bool Shutting = 0;
};
