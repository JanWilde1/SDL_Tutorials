#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#define TITLE "Window 1"

const int WIN_WIDTH = 512;
const int WIN_HEIGHT = 512;

enum key_textures {
    KEY_DEFAULT_TEXTURE,
    KEY_UP_TEXTURE,
    KEY_DOWN_TEXTURE,
    KEY_LEFT_TEXTURE,
    KEY_RIGHT_TEXTURE,
    KEY_PRESS_TOTAL
};

SDL_Texture* load_texture(const char* relative_path);
SDL_Renderer* renderer_i = nullptr;

SDL_Window* window_i = nullptr;

SDL_Texture* key_press_texture_a [KEY_PRESS_TOTAL]; // KEY_PRESS_TOTAL is equal to number of components before - four

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
            renderer_i = SDL_CreateRenderer(window_i, -1, SDL_RENDERER_ACCELERATED);
            if (renderer_i == nullptr) {
                std::cout << "Renderer could not be created (Error: " << SDL_GetError() << ")" << std::endl;
                success_code = false;
            }
        }
    }

    return success_code;
}

bool load_media() {
    bool success = true;

    key_press_texture_a[KEY_DEFAULT_TEXTURE] = load_texture("../res/img/def.bmp");
    if (key_press_texture_a[KEY_DEFAULT_TEXTURE] == nullptr) { success = false; }

    key_press_texture_a[KEY_UP_TEXTURE] = load_texture("../res/img/up.bmp");
    if (key_press_texture_a[KEY_UP_TEXTURE] == nullptr) { success = false; }

    key_press_texture_a[KEY_DOWN_TEXTURE] = load_texture("../res/img/down.bmp");
    if (key_press_texture_a[KEY_DOWN_TEXTURE] == nullptr) { success = false; }

    key_press_texture_a[KEY_LEFT_TEXTURE] = load_texture("../res/img/left.bmp");
    if (key_press_texture_a[KEY_LEFT_TEXTURE] == nullptr) { success = false; }

    key_press_texture_a[KEY_RIGHT_TEXTURE] = load_texture("../res/img/right.bmp");
    if (key_press_texture_a[KEY_RIGHT_TEXTURE] == nullptr) { success = false; }

    return success;
}


void close() {
    SDL_DestroyWindow(window_i);
    window_i = nullptr;

    SDL_Quit();
}

SDL_Texture* load_texture(const char* relative_path) {
    SDL_Surface* loaded_surface = SDL_LoadBMP(relative_path);
    if (loaded_surface == nullptr) {
        std::cout << "Could not load image (Error: " << SDL_GetError() << ", Path: " << relative_path  << ")" << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_i, loaded_surface);
    if (texture == nullptr) {
        std::cout << "Could not create texture (Error: " << SDL_GetError() << ")" << std::endl;
    }

    SDL_FreeSurface(loaded_surface);
    return texture;
}

void set_image(SDL_Texture* texture, SDL_Rect size) {
    SDL_RenderClear(renderer_i);
    SDL_RenderCopy(renderer_i, texture, nullptr, &size);
    SDL_RenderPresent(renderer_i);
}

int main() {
    if (!init()) {
        return 1;
    }

    load_media();

    SDL_Texture* current_texture;

    float divider = 2;

    SDL_Rect size_rect;
    size_rect.x = 0;
    size_rect.y = 0;
    size_rect.w = WIN_WIDTH / 2;
    size_rect.h = WIN_HEIGHT / 2;

    current_texture = key_press_texture_a[KEY_DEFAULT_TEXTURE];

    set_image(current_texture, size_rect);

    SDL_Event e;
    bool quit = false;

    while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            current_texture = key_press_texture_a[KEY_UP_TEXTURE];
                            break;
                        case SDLK_DOWN:
                            current_texture = key_press_texture_a[KEY_DOWN_TEXTURE];
                            break;
                        case SDLK_LEFT:
                            current_texture = key_press_texture_a[KEY_LEFT_TEXTURE];
                            break;
                        case SDLK_RIGHT:
                            current_texture = key_press_texture_a[KEY_RIGHT_TEXTURE];
                            break;
                        case SDLK_COMMA:
                            size_rect.w -= 20;
                            size_rect.h -= 20;
                            break;
                        case SDLK_PERIOD:
                            divider -= 0.2;
                            size_rect.w += 20;
                            size_rect.h += 20;
                            break;
                            break;
                        case SDLK_w:
                            size_rect.y -= 20;
                            break;
                        case SDLK_a:
                            size_rect.x -= 20;
                            break;
                        case SDLK_s:
                            size_rect.y += 20;
                            break;
                        case SDLK_d:
                            size_rect.x += 20;
                            break;
                        default:
                            current_texture = key_press_texture_a[KEY_DEFAULT_TEXTURE];
                            break;
                    }
                }
            }

            set_image(current_texture, size_rect);

            SDL_Delay(16);

        }

        close();
    }
