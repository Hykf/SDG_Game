
#include "Player.h"
#include "Window.h"
#include <algorithm>
#include  <SDL.h>
#include <iostream>
#include "Tile.h"


Player::Player(Window *_window) {
    window = _window;
    window->gameObjects.push_back(this);

    healthbarBackground = new UI(window,10,950);
    healthbarBackground->ChangeColor(250,0,0,255);
    healthbarForeground = new UI(window,healthbarBackground->positionX,healthbarBackground->positionY);
    healthbarForeground->ChangeColor(10,250,25,255);

    boxCollision = new BoundingBox(positionX,positionY,sizeX,sizeY);
    boxCollision->debugShow = 0;
}

Player::~Player() {
    window->gameObjects.erase(std::find(window->gameObjects.begin(),window->gameObjects.end(),this));
}

void Player::Render(Window &renderer) {

    Update();

    SDL_Rect square = { renderer.width, static_cast<int>(positionY), sizeX, sizeY };
    SDL_SetRenderDrawColor(renderer.renderer, 240, 120, 0, 255);
    SDL_RenderFillRect(renderer.renderer, &square);

    //Update();
}

void Player::Movement(const Uint8 *state) {

    bool hasTopCollision = (std::find(collisionDirection.begin(), collisionDirection.end(), 0) != collisionDirection.end());
    bool hasRightCollision = (std::find(collisionDirection.begin(), collisionDirection.end(), 1) != collisionDirection.end());
    bool hasLeftCollision = (std::find(collisionDirection.begin(), collisionDirection.end(), 3) != collisionDirection.end());

    for (int i=0;i!=collisionDirection.size();i++){

        switch (i) {
            case 0:
                if (state[SDL_SCANCODE_W]) {
                } break;
            case 1:
                if (state[SDL_SCANCODE_D]) {
                    velocityX = 0;
                } break;
            case 2:
                if (state[SDL_SCANCODE_S]) {
                    velocityY = 0;
                } break;
            case 3:
                if (state[SDL_SCANCODE_A]) {
                    velocityX = 0;
                } break;
            default: break;

        }
    }

    const float jumpImpulse = 50.0f;
    const float jumpDuration = 0.5f;
    static float jumpTime = 0.1f;

        if (state[SDL_SCANCODE_W] && isOnGround) {
            velocityY = -jumpImpulse;
            jumpTime = jumpDuration;
        }

    if (jumpTime > 0.0f) {
        velocityY += gravity * (1.0f - (jumpTime / jumpDuration));

    } else {
        velocityY += gravity;
    }

        if (state[SDL_SCANCODE_S]) {
            //velocityY += acceleration;
        }

    if (!hasLeftCollision && state[SDL_SCANCODE_A]) {
        velocityX -= acceleration;
    } else if (!hasRightCollision && state[SDL_SCANCODE_D]) {
        velocityX += acceleration;
    } else {
        velocityX = 0;
    }

        CheckOnGround();

        if (!isOnGround) {
            velocityY += gravity;
        }

        velocityX = std::clamp(velocityX, -maxSpeed, maxSpeed);
        velocityY = std::clamp(velocityY, float(-jumpSpeed), maxSpeed/2);

        positionX += velocityX;
        positionY += velocityY;

        if (!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S]) {
            if (std::abs(velocityY) < deceleration) {
                velocityY = 0.0f;
            } else {
                velocityY -= (velocityY > 0) ? deceleration : -deceleration;
            }
        }
        if (!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]) {
            if (std::abs(velocityX) < deceleration) {
                velocityX = 0.0f;
            } else {
                velocityX -= (velocityX > 0) ? deceleration : -deceleration;
            }
        }

}

void Player::HandleMouseClick(SDL_Event &event) {

    if (event.button.button == SDL_BUTTON_LEFT) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        Tile* tile = new Tile(window,mouseX+positionX,mouseY);

        ChangeHealth(10);

        /// ZAMIENIC NA CREATE GAMEOBJECT (JAKAS KLASA POCHODNA FLOOR LUB TILE) I tam w konstruktorze niech to
        /// Doda sie do gameObjecs
    }
}

void Player::ChangeHealth(int change) {

    healthbarForeground->sizeX -= std::clamp(float(healthbarBackground->sizeX)/change,0.0f,float(healthbarBackground->sizeX));

}

void Player::Update() {

    boxCollision->drawBoundingBox(window->renderer);
    boxCollision->Move(500,positionY);

    bool isCollision = CheckForCollision(this->velocityX,velocityY);
    //0 gora
    //1 prawo
    //2 dol
    //3 lewo
    //-1 ERROR
    const Uint8* state = SDL_GetKeyboardState(NULL);

    Movement(state);


    if(counter%10==0){

        std::cout<<"DT: "<<window->DeltaTime << "\n";

    }

    counter++;

    collisionDirection.clear();
}

bool Player::CheckForCollision(float dx, float dy) {

    bool ret = false;
    for(auto x : window->gameObjects){

        if(x == this) continue;
        auto coll = x->boxCollision;
        if(coll != nullptr)
            if(boxCollision->CheckCollision(*coll,velocityX,velocityY)){
                collisionDirection.push_back(boxCollision->CollisionDirection(*coll));
                ret =  true;
            }
    }

    for(auto x : window->levelDesign){
        auto coll = x->boxCollision;

        if(coll != nullptr)
            if(boxCollision->CheckCollision(*coll,velocityX,velocityY)){
                collisionDirection.push_back(boxCollision->CollisionDirection(*coll));
                ret = true;
            }
   }

    return ret;
}

void Player::CheckOnGround() {

    auto x = std::find(collisionDirection.begin(), collisionDirection.end(), 2);
    isOnGround = (x != collisionDirection.end());

    if(isOnGround){
        gravity = 0;
    } else{
        gravity = 10; //Im wieksze to tym nizej da rade skoczyc
    }

}
