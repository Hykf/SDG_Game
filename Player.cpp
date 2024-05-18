
#include "Player.h"
#include "Window.h"
#include <algorithm>
#include  <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Tile.h"
#include "Arrow.h"
#include <windows.h>

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
    bool hasCollision = CheckForCollision(velocityX, velocityY);

    CheckOnGround();

    if (!isOnGround) {
        velocityY += gravity;
        velocityY += maxSpeed * window->DeltaTime;
        velocityY += gravity * (1.0f - (jumpTime / jumpDuration));
    }

    Uint32 currentTime = SDL_GetTicks();
    bool canJump = (currentTime - lastJumpTime > jumpCooldown);

    if (state[SDL_SCANCODE_W] && isOnGround && canJump) {
        velocityY = -jumpImpulse;
        jumpTime = jumpDuration;
        PlaySound(TEXT("../sounds/jump.wav"), NULL, SND_FILENAME | SND_ASYNC);
        lastJumpTime = currentTime;
    }

    if (state[SDL_SCANCODE_A] && !hasLeftCollision && !hasTopCollision) {
        velocityX -= acceleration;
        facingRight = false;
        animStage = (animStage == GETHIT) ? GETHIT : RUN;
    }
    else if (state[SDL_SCANCODE_D] && !hasRightCollision && !hasTopCollision) {
        velocityX += acceleration;
        facingRight = true;
        animStage = (animStage == GETHIT) ? GETHIT : RUN;
    } else {
        velocityX = 0;
        animStage = (animStage == GETHIT) ? GETHIT : IDLE;
    }

    velocityX = std::clamp(velocityX, -maxSpeed, maxSpeed);
    velocityY = std::clamp(velocityY, float(-jumpSpeed), (maxSpeed * 2));

    positionX += velocityX;
    positionY += velocityY;

    if (!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S] && isOnGround) {
        velocityY = 0.0f;
    }

    if (!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]) {
        velocityX = 0.0f;
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
        tile->cc = 6;
        PlaySound(TEXT("../sounds/tap.wav"), NULL, SND_FILENAME | SND_ASYNC);


        /// ZAMIENIC NA CREATE GAMEOBJECT (JAKAS KLASA POCHODNA FLOOR LUB TILE) I tam w konstruktorze niech to
        /// Doda sie do gameObjecs
    }
}

void Player::ChangeHealth(int change) {

    healthbarForeground->sizeX -= std::clamp(float(healthbarBackground->sizeX)/change,0.0f,float(healthbarBackground->sizeX));
    SetHealthColor();
}

void Player::Update() {

    bool isCollision = CheckForCollision(this->maxSpeed,maxSpeed);

    boxCollision->drawBoundingBox(window->renderer);
    boxCollision->Move(500,positionY);



    //0 gora
    //1 prawo
    //2 dol
    //3 lewo
    //-1 ERROR
    const Uint8* state = SDL_GetKeyboardState(NULL);

    Movement(state);

    if(counter%100==0){

        std::cout<<"SCORE: "<< score << "\n";

    }

    counter++;

    collisionDirection.clear();

    if(positionY > window->height){
        positionY = -10;
        ChangeHealth(5);
        PlaySound(TEXT("../sounds/hurt.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }

}

bool Player::CheckForCollision(float dx, float dy) {

    bool ret = false;
    BoundingBox futureBox = *boxCollision;
    futureBox.x += dx;
    futureBox.y += dy;

    for (auto x : window->gameObjects) {
        if (x == this) continue;
        auto coll = x->boxCollision;
        if (coll != nullptr) {
            if (futureBox.CheckCollision(*coll, 0, 0)) {
                HandleCollision(coll,x);
                ret = true;
            }
        }
    }

    for (auto x : window->levelDesign) {
        auto coll = x->boxCollision;
        if (coll != nullptr && futureBox.CheckCollision(*coll, 0, 0)) {
            HandleCollision(coll,x);
            ret = true;
        }
    }

    return ret;
}

void Player::CheckOnGround() {

    bool isCollision = CheckForCollision(this->maxSpeed,maxSpeed);
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

    flip = static_cast<SDL_RendererFlip>((facingRight == 0) ? SDL_FLIP_HORIZONTAL :  SDL_FLIP_NONE);

    SDL_RenderCopyEx(renderer.renderer, objectTexture, &srcRect, &dstRect,0.0, NULL, flip);



}

void Player::HandleCollision(BoundingBox *coll, GameObject* go) {
    switch (coll->collType) {
        case BoundingBox::BLOCK:
            collisionDirection.push_back(boxCollision->CollisionDirection(*coll));
            break;
        case BoundingBox::DANGER:
            PlaySound(TEXT("../sounds/hurt.wav"), NULL, SND_FILENAME | SND_ASYNC);
            ChangeHealth(17);
            animStage = GETHIT;
            coll->collType = BoundingBox::NONE;

            {
                Arrow *arr = dynamic_cast<Arrow *>(go);
                arr->sizeX = 0;
                arr->sizeY = 0;
            }

            break;
        case BoundingBox::COIN:
            score++;
            coll->collType = BoundingBox::NONE;
            PlaySound(TEXT("../sounds/coin.wav"), NULL, SND_FILENAME | SND_ASYNC);

            {
                Coin *coin = dynamic_cast<Coin *>(go);
                coin->sizeX = 0;
                coin->sizeY = 0;
            }

            break;
        case BoundingBox::FINISH:
            break;
        default:
            break;
    }
}
