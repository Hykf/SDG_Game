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


    BuildLevel();
}

Window::~Window() {

    if(level) delete level;

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

void Window::BuildLevel() {

    level = new Level();
    int blocksize = 150;
    int innerLoop = 10;

    for(int i = 0; i!= 10 ; i++){
        level->farBackground = new FarBackground(this,-250 + (i*1500),0);
        level->nearBackground = new NearBackground(this,-250+ (i*1000),500);

        for(int j = 0; j != innerLoop ; j++){
            level->levelTile = new Tile(this,0+(((i*innerLoop) + j) * blocksize) ,800,blocksize,blocksize);

        }
    }

}

