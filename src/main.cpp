#include <iostream>
#include <SDL2/SDL.h>

#define TITLE "Window 1"

const int WIN_WIDTH = 512;
const int WIN_HEIGHT = 512;

bool init();
bool load_media();
void close_application();

SDL_Window* window_i = NULL;
SDL_Surface* screen_surface_i = NULL;
SDL_Surface* media_surface_i = NULL;

bool init() {
    bool success_code = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Could Not Initialise (Error: " << SDL_GetError() << ")" << std::endl;
        success_code = false;
    } else {
        // create the window
        window_i = SDL_CreateWindow(
            TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIN_WIDTH,
            WIN_HEIGHT,
            SDL_WINDOW_SHOWN // visible
            );

        if (window_i == NULL) {
            std::cout << "Window could not be created (Error: " << SDL_GetError() << ")" << std::endl;
            success_code = false;
        } else {
            screen_surface_i = SDL_GetWindowSurface(window_i);
        }
    }

    return success_code;
}

bool load_media() {
    bool success = true;

    media_surface_i = SDL_LoadBMP("../res/img/chessboard.bmp");
    if (media_surface_i == NULL) {
        std::cout << "Could not load image (Error: " << SDL_GetError() << ")" << std::endl;
        success = false;
    }

    return success;
}


void close() {
    SDL_DestroyWindow(window_i);
    window_i = NULL;

    SDL_Quit();
}

int main() {
    if (!init()) {
        return 1;
    }

    if (load_media()) {
        SDL_BlitSurface(media_surface_i, NULL, screen_surface_i, NULL); // apply image surface to screen surface TODO: Study BlitSurface
        SDL_UpdateWindowSurface(window_i);
    }

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    close();
}
