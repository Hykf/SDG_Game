
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

}

Player::~Player() {
    window->gameObjects.erase(std::find(window->gameObjects.begin(),window->gameObjects.end(),this));
}

void Player::Render(Window &renderer) {
    SDL_Rect square = { static_cast<int>(positionX), static_cast<int>(positionY), sizeX, sizeY };
    SDL_SetRenderDrawColor(renderer.renderer, 240, 0, 0, 255);
    SDL_RenderFillRect(renderer.renderer, &square);

    const Uint8* state = SDL_GetKeyboardState(NULL);
    Movement(state);

    if(counter%10==0){
        std::cout<<"X: "<< positionX <<" Y: " << positionY <<std::endl;
        std::cout<<"V_X: "<< velocityX <<" V_Y: " << velocityY <<std::endl;
    }
    counter++;


}

void Player::Movement(const Uint8 *state) {

    if (state[SDL_SCANCODE_W]) {
        velocityY -= acceleration;
    }
    if (state[SDL_SCANCODE_S]) {
        velocityY += acceleration;
    }
    if (state[SDL_SCANCODE_A]) {
        velocityX -= acceleration;
    }
    if (state[SDL_SCANCODE_D]) {
        velocityX += acceleration;
    }

    velocityX = std::clamp(velocityX, -maxSpeed, maxSpeed);
    velocityY = std::clamp(velocityY, -maxSpeed, maxSpeed);

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

        Tile* tile = new Tile(window,mouseX,mouseY);

        ChangeHealth(10);

        /// ZAMIENIC NA CREATE GAMEOBJECT (JAKAS KLASA POCHODNA FLOOR LUB TILE) I tam w konstruktorze niech to
        /// Doda sie do gameObjecs
    }
}

void Player::ChangeHealth(int change) {

    healthbarForeground->sizeX -= std::clamp(float(healthbarBackground->sizeX)/change,0.0f,float(healthbarBackground->sizeX));

}

