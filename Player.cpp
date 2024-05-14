
#include "Player.h"
#include "Window.h"
#include <algorithm>
#include  <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Tile.h"
#include "SDL_mixer.h"
#include "Arrow.h"


Player::Player(Window *_window) {
    window = _window;
    window->gameObjects.push_back(this);

    healthbarBlackBackground = new UI(window,5,945);
    healthbarBlackBackground->sizeX = healthbarBlackBackground->sizeX + 10;
    healthbarBlackBackground->sizeY = healthbarBlackBackground->sizeY + 10;
    healthbarBlackBackground->ChangeColor(0,0,0,255);

    healthbarBackground = new UI(window,10,950);
    healthbarBackground->ChangeColor(250,0,0,255);

    healthbarForeground = new UI(window,healthbarBackground->positionX,healthbarBackground->positionY);
    healthbarForeground->ChangeColor(15,105,10,255);

    boxCollision = new BoundingBox(positionX,positionY,sizeX,sizeY);
    boxCollision->debugShow = 0;

    objectTexture = IMG_LoadTexture(window->renderer, "../images/knight.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);
}

Player::~Player() {
    window->gameObjects.erase(std::find(window->gameObjects.begin(),window->gameObjects.end(),this));
    SDL_DestroyTexture(objectTexture);
}

void Player::Render(Window &renderer) {

    Update();
    SDL_Rect square = { renderer.width, static_cast<int>(positionY), sizeX, sizeY };
    //SDL_SetRenderDrawColor(renderer.renderer, 240, 120, 0, 255);
    //SDL_RenderFillRect(renderer.renderer, &square);
    RunAnimation(renderer);

    //Update();
}

void Player::Movement(const Uint8 *state) {

    AnimStage tempAnim = (animStage==GETHIT)?GETHIT:IDLE;

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
        facingRight = false;
        animStage = (animStage==GETHIT)?GETHIT:RUN;
    } else if (!hasRightCollision && state[SDL_SCANCODE_D]) {
        velocityX += acceleration;
        facingRight = true;
        animStage = (animStage==GETHIT)?GETHIT:RUN;
    } else {
        velocityX = 0;
        animStage = (animStage==GETHIT)?GETHIT:IDLE;
    }

        CheckOnGround();

        if (!isOnGround) {
            velocityY += gravity;
        }

        velocityX = std::clamp(velocityX, -maxSpeed, maxSpeed);
        velocityY = std::clamp(velocityY, float(-jumpSpeed), (maxSpeed/2));

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

        if (tile) {
            delete tile;
            tile = nullptr;
        }

        tile = new Tile(window,mouseX+positionX,mouseY,75,75);
        tile->cc = 3;


        /// ZAMIENIC NA CREATE GAMEOBJECT (JAKAS KLASA POCHODNA FLOOR LUB TILE) I tam w konstruktorze niech to
        /// Doda sie do gameObjecs
    }
}

void Player::ChangeHealth(int change) {

    healthbarForeground->sizeX -= std::clamp(float(healthbarBackground->sizeX)/change,0.0f,float(healthbarBackground->sizeX));
    SetHealthColor();
}

void Player::Update() {

    bool isCollision = CheckForCollision(this->velocityX,velocityY);

    boxCollision->drawBoundingBox(window->renderer);
    boxCollision->Move(500,positionY);



    //0 gora
    //1 prawo
    //2 dol
    //3 lewo
    //-1 ERROR
    const Uint8* state = SDL_GetKeyboardState(NULL);

    Movement(state);

    if(counter%10==0){

        //std::cout<<"DT: "<<window->DeltaTime << "\n";

    }

    counter++;

    collisionDirection.clear();

    if(positionY > window->height){
        positionY = -10;
        ChangeHealth(5);
    }

}

bool Player::CheckForCollision(float dx, float dy) {

    bool ret = false;
    for(auto x : window->gameObjects){

        if(x == this) continue;

        auto coll = x->boxCollision;

        if(coll != nullptr){


            if(boxCollision->CheckCollision(*coll,velocityX,velocityY)){
                switch(coll->collType){

                    case BoundingBox::BLOCK:
                        collisionDirection.push_back(boxCollision->CollisionDirection(*coll));
                        ret =  true;
                        break;

                    case BoundingBox::DANGER:

                        ChangeHealth(17);
                        animStage = GETHIT;
                        coll->collType = BoundingBox::NONE;
                        {
                            auto a = dynamic_cast<Arrow*>(x);
                            a->sizeX = 0;
                            a->sizeY = 0;

                        }
                        break;

                    case BoundingBox::COIN:
                        score++;
                        coll->collType = BoundingBox::NONE;
                        {
                            auto a = dynamic_cast<Coin*>(x);
                            a->sizeX = 0;
                            a->sizeY = 0;

                        }
                        break;

                    case BoundingBox::FINISH:
                        break;
                    default:
                        break;

                }

            }
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
        gravity = 2; //Im wieksze to tym nizej da rade skoczyc
    }

}

void Player::SetHealthColor() {



    float x = healthbarForeground->sizeX;
    float y = healthbarBackground->sizeX;
    float health = x/y;
    //std::cout<< health << std::endl;

    if(health > 0.66){
        healthbarForeground->ChangeColor(15,105,10,255);
    }else if(health <= 0.66 && health > 0.33 ){
        healthbarForeground->ChangeColor(190,170,0,255);
    }else{
        healthbarForeground->ChangeColor(110,0,0,255);
    }

    if(health-0.01f <= 0)
        alive = false;


}

void Player::RunAnimation(Window &renderer) {

    int startYpos = 9;
    int animEndFram = 4;

    switch (animStage) {
        case IDLE:
            startYpos = 9;
            animEndFram = 4;
            currentStage = currentStage % animEndFram;
            break;
        case RUN:
            startYpos = 74;
            animEndFram = 8;
            currentStage = currentStage % animEndFram;
            break;
        case GETHIT:
            startYpos = 201;
            animEndFram = 4;
            break;
        case DEATH:
            break;
        default:
            break;
    }


    SDL_Rect dstRect = { static_cast<int>(500)-(sizeX/2), static_cast<int>(positionY)-(sizeY), sizeX*2, sizeY*2 }; // x i y pozycja na ekranie w i h rozmiar
    SDL_Rect srcRect = { 9 + (currentStage * 32), startYpos, 13, 20 };

    if (counter % 10 == 0) {
        currentStage++;

        if(animStage==GETHIT && currentStage==animEndFram){
            animStage = IDLE;
        }

        currentStage = currentStage % animEndFram;
    }

    SDL_RendererFlip flip;

    flip = static_cast<SDL_RendererFlip>((facingRight == 0) ? SDL_FLIP_HORIZONTAL : NULL);

    SDL_RenderCopyEx(renderer.renderer, objectTexture, &srcRect, &dstRect,0.0, NULL, flip);



}
