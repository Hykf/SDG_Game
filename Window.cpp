#include "Window.h"
#include <iostream>
#include <vector>
#include "GameObject.h"

Window::Window(int width, int height) {
    SDL_Init( SDL_INIT_EVERYTHING );
    width = width;
    height = height;
    if (auto error = SDL_CreateWindowAndRenderer( width, height,SDL_WINDOW_SHOWN, &window, &renderer )) {
        std::cout << "Nie udalo sie utworzyc okienka" << std::endl;
    }

}

Window::~Window() {

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

}

void Window::RenderAll() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for(auto go : gameObjects){
        go->Render(*this);
    }

    SDL_RenderPresent(renderer);
}
