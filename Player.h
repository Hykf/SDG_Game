#pragma once

#include "GameObject.h"
#include "UI.h"
#include  <SDL.h>
#include "BoundingBox.h"
#include <vector>


class Tile;

class Player : public GameObject{
public:

    Player(Window* _window);
    ~Player();

    //
    //Kiedys moze warto pomyslec nad
    // stworzeniem struktur do trzymania zmiennych
    //

    enum AnimStage{
        IDLE,
        RUN,
        GETHIT,
        DEATH,
    };

    float positionX = 100;
    float positionY = 200;
    float velocityX;
    float velocityY;
    const float jumpImpulse = 50.0f;
    const float jumpDuration = 0.5f;
    float jumpTime = 0.1f;
    float accelerationX = 0.5f;
    float accelerationY = 0.5f;
    int score = 0;
    int sizeX = 20;
    int sizeY = 35;
    float acceleration = 50.5f;
    float deceleration = 0.6f;
    float maxSpeed = 8.0f;
    int counter = 0;
    std::vector<int> collisionDirection;
    int isOnGround = 1;
    int jumpSpeed = 25;
    double gravity = 1;
    bool alive = true;

    AnimStage animStage = IDLE;

    bool facingRight = true;
    int currentStage = 0;

    BoundingBox* boxCollision = nullptr;

    UI* healthbarBlackBackground = nullptr;
    UI* healthbarBackground = nullptr;
    UI* healthbarForeground = nullptr;

    Tile* tile = nullptr;

    virtual void Render(Window& renderer) override;
    void Movement(const Uint8* state);
    void HandleMouseClick(SDL_Event &event);
    void ChangeHealth(int change);
    void Update();
    bool CheckForCollision(float dx, float dy);
    void CheckOnGround();
    void SetHealthColor();
    void RunAnimation(Window &renderer);
};


