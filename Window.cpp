#include "Window.h"
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Tile.h"
#include "Arrow.h"
#include <random>
#include <SDL_mixer.h>

Window::Window(int width, int height) {
    SDL_Init( SDL_INIT_EVERYTHING );
    width = width;
    height = height;
    if (auto error = SDL_CreateWindowAndRenderer( width, height,SDL_WINDOW_SHOWN, &window, &renderer )) {
        std::cout << "Nie udalo sie utworzyc okienka" << std::endl;
    }
    player = new Player(this);

    level = new Level(this);
    //Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    //music = Mix_LoadMUS("../music/time_for_adventure.mp3");
    //Mix_PlayMusic(music, -1);
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



        if(counter%20==0)
            level->SpawnArrow(player->positionX+500,0);
        counter++;

}

void Window::Render(std::vector<GameObject *> objToRender) {

    for(auto go : objToRender){
        go->Render(*this);
    }

}

void Window::BuildLevel() {

    int blocksize = 150;
    int innerLoop = 10;

    for(int i = 0; i!= 10 ; i++){
        level->farBackground = new FarBackground(this,-250 + (i*1500),0);
        level->nearBackground = new NearBackground(this,-250+ (i*1000),0);

        for(int j = 0; j != innerLoop ; j++){
            level->levelTile = new Tile(this,0+(((i*innerLoop) + j) * blocksize) ,900,blocksize,blocksize);

        }
    }

}

void Window::Level::SpawnArrow(int x, int y) {
    Arrow* arr = nullptr;
    arr = new Arrow(this->window,x,y);
}
