#include <SDL3/SDL.h>

#include <iostream>

#define TITLE ""
#define WIDTH 1000
#define HEIGHT 1000

SDL_Window* window_i;
SDL_Renderer* renderer_i;

SDL_Color light_square = {255, 255, 255, 0};
SDL_Color dark_square = {0, 0, 0, 255};

float padding = 80;

float square_width = (WIDTH - (2 * padding)) / 8;
float square_height = (HEIGHT - (2 * padding)) / 8;

bool init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Could not initialise SDL, Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window_i = SDL_CreateWindow(
        TITLE,
        WIDTH,
        HEIGHT,
        0
        );

    if (window_i == nullptr) {
        std::cerr << "Window could not be created, Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_ShowWindow(window_i);

    renderer_i = SDL_CreateRenderer(window_i, nullptr);
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
        Uint32 start_time, frame_time;
        float fps;

        start_time = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_EVENT_QUIT) { quit = true; }

            if (e.type == SDL_EVENT_KEY_DOWN) {
                switch (e.key.key) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer_i, 0, 0, 0, 255);
        SDL_RenderClear(renderer_i);

        // Render Code
        SDL_Color current_colour;

        for (int i = 0; i < 64; i++) {
            int file = i % 8;
            int rank = i / 8;

            if ((file + rank) % 2 == 0) {
                current_colour = dark_square;
            } else { current_colour = light_square; }

            SDL_FRect current_rect = {
                (file * square_width + padding),
                (rank * square_height + padding),
                (square_width),
                (square_height)
            };

            SDL_SetRenderDrawColor(renderer_i, current_colour.r, current_colour.g, current_colour.b, current_colour.a);
            SDL_RenderFillRect(renderer_i, &current_rect);
        }

        SDL_SetRenderDrawColor(renderer_i, 255, 255, 255, 255);
        SDL_FRect surround_rect = {(padding), (padding), (8 * square_width),(8 * square_height)};
        SDL_RenderRect(renderer_i, &surround_rect);

        SDL_RenderPresent(renderer_i);

        frame_time = SDL_GetTicks() - start_time;
        fps = (frame_time > 0) ? 1000.0 / frame_time : 0.0f;

        std::cout << "FPS: " << fps << std::endl;
    }

    deinit();
}