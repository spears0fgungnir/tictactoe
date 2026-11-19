#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const SDL_Color BLACK = {0, 0, 0, 1};
const SDL_Color WHITE = {255, 255, 255, 1};

SDL_Color color_list[] = {BLACK, WHITE};
int current_color = 0;
int exit_code = 0;

static inline void set_render_color(SDL_Renderer* rend, SDL_Color* color) {
    SDL_SetRenderDrawColor(
        rend,
        color->r,
        color->g,
        color->b,
        color->a
    );
}

int main(void){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "fatal: Couldn't initialize video framework");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "TIC-TAC-TOE",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        exit_code = 1;
        goto terminate;
    }

    SDL_Renderer* rend = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!rend) {
        exit_code = 1;
        goto terminate;
    }

    SDL_Event event;
    int quit = 0;

    while (!quit) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            
            else if (event.type == SDL_KEYDOWN) {
                SDL_Keycode pressed_key = event.key.keysym.sym;

                if (pressed_key == SDLK_ESCAPE) {
                    quit = 1;
                }
                else if (pressed_key == SDLK_SPACE && !event.key.repeat) {
                    current_color ^= 1;
                }
            }
        }

        set_render_color(rend, &color_list[current_color]);
        SDL_RenderClear(rend);

        // there goes your work...............

        SDL_RenderPresent(rend);
    }

terminate:
    if (window)
        SDL_DestroyWindow(window);

    if (rend)
        SDL_DestroyRenderer(rend);

    SDL_Quit();
    return exit_code;
}
