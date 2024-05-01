#include <SDL2/SDL.h>
#include <iostream>

#undef main

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error: SDL failed to initialize\nSDL Error: '" << SDL_GetError() << "'\n";
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        std::cerr << "Error: Failed to open window\nSDL Error: '" << SDL_GetError() << "'\n";
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Error: Failed to create renderer\nSDL Error: '" << SDL_GetError() << "'\n";
        return 1;
    }

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 25, 150, 50, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
