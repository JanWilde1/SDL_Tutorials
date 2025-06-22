#include <SDL2/SDL.h>

#include <iostream>

#define TITLE ""
#define WIDTH 1200
#define HEIGHT 1200

SDL_Window* window_i;
SDL_Renderer* renderer_i;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialise SDL, Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window_i = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
        );

    if (window_i == nullptr) {
        std::cerr << "Window could not be created, Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer_i = SDL_CreateRenderer(window_i, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_i == nullptr) {
        std::cerr << "Renderer could not be created, Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void deinit() {
    SDL_DestroyWindow(window_i);
    SDL_DestroyRenderer(renderer_i);

    SDL_Quit();
}

int main() {
    if (!init()) { return 1; }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { quit = true; }

            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
            }
        }

        // Render Code
    }

    deinit();
}