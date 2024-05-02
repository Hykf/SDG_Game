#pragma once

#include "GameObject.h"
#include  <SDL.h>

class Player : public GameObject{
public:

    Player(Window* _window);
    ~Player();

    float positionX = 100;
    float positionY = 100;
    float velocityX;
    float velocityY;
    int sizeX = 20;
    int sizeY = 20;
    float acceleration = 0.5f;
    float deceleration = 0.6f;
    float maxSpeed = 10.0f;
    int counter = 0;


    virtual void Render(Window& renderer) override;
    void Movement(const Uint8* state);
    void HandleMouseClick(SDL_Event &event);
};


