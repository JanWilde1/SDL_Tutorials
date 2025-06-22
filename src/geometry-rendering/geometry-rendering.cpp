#include <SDL2/SDL.h>

#include <iostream>

#define TITLE ""
#define WIDTH 1000
#define HEIGHT 1000

SDL_Window* window_i;
SDL_Renderer* renderer_i;

SDL_Color light_square = {255, 255, 255, 0};
SDL_Color dark_square = {0, 0, 0, 255};

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

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                }
            }
        }

        // Render Code
        SDL_Color current_colour;

        for (int i = 0; i < 64; i++) {
            int file = i % 8;
            int rank = i / 8;

            if ((file + rank) % 2 == 0) {
                current_colour = dark_square;
            } else { current_colour = light_square; }

            SDL_Rect current_rect = {
                file * (WIDTH / 8),
                rank * (HEIGHT / 8),
                WIDTH / 8,
                HEIGHT / 8
            };

            SDL_SetRenderDrawColor(renderer_i, current_colour.r, current_colour.g, current_colour.b, current_colour.a);
            SDL_RenderFillRect(renderer_i, &current_rect);
        }

        SDL_RenderPresent(renderer_i);
    }

    deinit();
}