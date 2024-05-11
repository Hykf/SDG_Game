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
    float accelerationX = 0.5f;
    float accelerationY = 0.5f;
    int sizeX = 20;
    int sizeY = 35;
    float acceleration = 50.5f;
    float deceleration = 0.6f;
    float maxSpeed = 5.0f;
    int counter = 0;
    std::vector<int> collisionDirection;
    int isOnGround = 1;
    int jumpSpeed = 25;
    double gravity = 1;

    int textureWidth;
    int textureHeight;
    bool facingRight = true;
    int currentStage = 0;

    BoundingBox* boxCollision;

    UI* healthbarBlackBackground = nullptr;
    UI* healthbarBackground = nullptr;
    UI* healthbarForeground = nullptr;

    SDL_Texture* playerTexture = nullptr;

    virtual void Render(Window& renderer) override;
    void Movement(const Uint8* state);
    void HandleMouseClick(SDL_Event &event);
    void ChangeHealth(int change);
    void Update();
    bool CheckForCollision(float dx, float dy);
    void CheckOnGround();
    void SetHealthColor();
};


