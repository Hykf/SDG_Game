#pragma once

#include "GameObject.h"
#include "UI.h"
#include  <SDL.h>
#include "BoundingBox.h"
#include <vector>

class Player : public GameObject{
public:

    Player(Window* _window);
    ~Player();

    //
    //Kiedys moze warto pomyslec nad
    // stworzeniem struktur do trzymania zmiennych
    //


    float positionX = 100;
    float positionY = 100;
    float velocityX;
    float velocityY;
    int sizeX = 20;
    int sizeY = 20;
    float acceleration = 5.5f;
    float deceleration = 0.6f;
    float maxSpeed = 5.0f;
    int counter = 0;
    std::vector<int> collisionDirection;
    int isOnGround = 1;
    int jumpSpeed = 25;
    double gravity = 1;

    BoundingBox* boxCollision;

    UI* healthbarBackground = nullptr;
    UI* healthbarForeground = nullptr;


    virtual void Render(Window& renderer) override;
    void Movement(const Uint8* state);
    void HandleMouseClick(SDL_Event &event);
    void ChangeHealth(int change);
    void Update();
    bool CheckForCollision();
    void CheckOnGround();
};


