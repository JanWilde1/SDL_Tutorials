#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#define TITLE "Window 1"

const int WIN_WIDTH = 512;
const int WIN_HEIGHT = 512;

enum key_surfaces {
    KEY_DEFAULT_SURFACE,
    KEY_UP_SURFACE,
    KEY_DOWN_SURFACE,
    KEY_LEFT_SURFACE,
    KEY_RIGHT_SURFACE,
    KEY_PRESS_TOTAL
};

bool init();
bool load_media();
void close_application();

SDL_Surface* load_bmp_surface(const char* relative_path);

SDL_Window* window_i = nullptr;

SDL_Surface* screen_surface_i = nullptr;
SDL_Surface* media_surface_i = nullptr;
SDL_Surface* key_press_surface_a [KEY_PRESS_TOTAL]; // KEY_PRESS_TOTAL is equal to number of components before - four

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

        if (window_i == nullptr) {
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

    key_press_surface_a[KEY_DEFAULT_SURFACE] = load_bmp_surface("../res/img/def.bmp");
    if (key_press_surface_a[KEY_DEFAULT_SURFACE] == nullptr) { success = false; }

    key_press_surface_a[KEY_UP_SURFACE] = load_bmp_surface("../res/img/up.bmp");
    if (key_press_surface_a[KEY_UP_SURFACE] == nullptr) { success = false; }

    key_press_surface_a[KEY_DOWN_SURFACE] = load_bmp_surface("../res/img/down.bmp");
    if (key_press_surface_a[KEY_DOWN_SURFACE] == nullptr) { success = false; }

    key_press_surface_a[KEY_LEFT_SURFACE] = load_bmp_surface("../res/img/left.bmp");
    if (key_press_surface_a[KEY_LEFT_SURFACE] == nullptr) { success = false; }

    key_press_surface_a[KEY_RIGHT_SURFACE] = load_bmp_surface("../res/img/right.bmp");
    if (key_press_surface_a[KEY_RIGHT_SURFACE] == nullptr) { success = false; }

    return success; // not used, for now
}


void close() {
    SDL_DestroyWindow(window_i);
    window_i = nullptr;

    SDL_Quit();
}

SDL_Surface* load_bmp_surface(const char* relative_path) {
    SDL_Surface* surface_return = SDL_LoadBMP(relative_path);
    if (surface_return == nullptr) {
        std::cout << "Could not load image (Error: " << SDL_GetError() << ", Path: " << relative_path  << ")" << std::endl;
    }

    return surface_return;
} // general purpose BMP loading function

void set_image(SDL_Surface* surface) {
    media_surface_i = surface;
    SDL_BlitSurface(media_surface_i, nullptr, screen_surface_i, nullptr);
}

int main() {
    if (!init()) {
        return 1;
    }

    load_media();

    set_image(key_press_surface_a[KEY_DEFAULT_SURFACE]);
    SDL_UpdateWindowSurface(window_i);

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) { // while events are in the queue, run through events one by one. Every time poll-events called, new event is assigned to pointer.
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) { // key symbols / identifiers
                    case SDLK_UP:
                        set_image(key_press_surface_a[KEY_UP_SURFACE]);
                        break;
                    case SDLK_DOWN:
                        set_image(key_press_surface_a[KEY_DOWN_SURFACE]);
                        break;
                    case SDLK_LEFT:
                        set_image(key_press_surface_a[KEY_LEFT_SURFACE]);
                        break;
                    case SDLK_RIGHT:
                        set_image(key_press_surface_a[KEY_RIGHT_SURFACE]);
                        break;
                    default:
                        set_image(key_press_surface_a[KEY_DEFAULT_SURFACE]);
                        break;
                }
            }

            SDL_UpdateWindowSurface(window_i);
        }
    }

    close();
}
