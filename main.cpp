#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 450;
const int RECT_WIDTH = SCREEN_WIDTH / 8;
const int RECT_HEIGHT = SCREEN_HEIGHT / 2;
const int LINE_WIDTH = 4;

float radius = RECT_HEIGHT / 2;

int centerX = SCREEN_WIDTH / 2;
int centerY = SCREEN_HEIGHT / 2;

int main(int argc, char *args[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set background color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw vertical line
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);

    // Draw left rectangle
    SDL_Rect leftRect = {0, SCREEN_HEIGHT / 4, RECT_WIDTH, RECT_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &leftRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &leftRect);

    // Draw right rectangle
    SDL_Rect rightRect = {SCREEN_WIDTH - RECT_WIDTH, SCREEN_HEIGHT / 4, RECT_WIDTH, RECT_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rightRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rightRect);

    for (int angle = 0; angle < 360; ++angle)
    {
        float radians = angle * (M_PI / 180);
        int x = centerX + static_cast<int>(radius * cos(radians));
        int y = centerY + static_cast<int>(radius * sin(radians));
        SDL_RenderDrawPoint(renderer, x, y);
    }
    // Update screen
    SDL_RenderPresent(renderer);

    // Wait for exit
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}