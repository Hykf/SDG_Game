#include "Window.h"
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Tile.h"


Window::Window(int width, int height) {
    SDL_Init( SDL_INIT_EVERYTHING );
    width = width;
    height = height;
    if (auto error = SDL_CreateWindowAndRenderer( width, height,SDL_WINDOW_SHOWN, &window, &renderer )) {
        std::cout << "Nie udalo sie utworzyc okienka" << std::endl;
    }
    player = new Player(this);

    tile = new Tile(this,50,800,250,750);
    tile = new Tile(this,300,800,250,750);
    tile = new Tile(this,550,800,250,750);
    tile = new Tile(this,800,800,250,750);

}

Window::~Window() {

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

}

void Window::RenderAll() {

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    SDL_RenderClear(renderer);

    Render(farBackground);
    Render(nearBackground);
    Render(levelDesign);
    Render(gameObjects);
    Render(foreGround);
    Render(UI);

    SDL_RenderPresent(renderer);
}

void Window::Render(std::vector<GameObject *> objToRender) {

    for(auto go : objToRender){
        go->Render(*this);
    }

}

