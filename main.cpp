#include <SDL.h>
#include <iostream>
#include "Window.h"
#include "Player.h"
#include "Tile.h"

int main( int argc, char* args[] ) {
    using namespace std;
    Window window(1000,1000);


    bool quit = false;
    SDL_Event event;
    Uint32 lastFrameTime = SDL_GetTicks();
    const Uint32 MS_PER_FRAME = 1000 / 60; // Limit FPS do 60

    //TEST

    for(int i = 0; i != (1000/50);i++){
        Tile* tile = new Tile(&window,(i*50),800);
    }


    //TEST --END

    while (!quit) { //MAIN GAME DRAWING LOOP

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }else if (event.type == SDL_MOUSEBUTTONDOWN) {
                window.player->HandleMouseClick(event);
            }
        }

        window.RenderAll();

    // FRAME MANAGEMENT -- START

        Uint32 currentFrameTime = SDL_GetTicks();
        Uint32 elapsedTime = currentFrameTime - lastFrameTime;

        if (elapsedTime < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - elapsedTime);
        }

        lastFrameTime = SDL_GetTicks();

    // FRAME MANAGEMENT -- END

    } // GAMELOOP END



    return 0;
}