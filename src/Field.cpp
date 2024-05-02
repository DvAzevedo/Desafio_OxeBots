#include "../include/Field.hpp"

Field::Field(int width, int height) : width(width), height(height) {}

void Field::draw(SDL_Renderer * renderer) {
    const int rec_width = width / 8;
    const int rec_height = height / 2;
    float radius = rec_height / 2;
    int centerX = width / 2;
    int centerY = height / 2;

    // Cor de fundo
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Linha vertical
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, centerX, 0, centerX, height);

    // Retângulo esquerdo
    SDL_Rect leftRect = {0, height / 4, rec_width, rec_height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &leftRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &leftRect);

    // Retângulo direito
    SDL_Rect rightRect = {width - rec_width, height / 4, rec_width,
                          rec_height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rightRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rightRect);

    // Circulo central
    for (int angle = 0; angle < 360; angle += 10) {
        float radians = angle * (M_PI / 180);
        int x1 = centerX + static_cast<int>(radius * cos(radians));
        int y1 = centerY + static_cast<int>(radius * sin(radians));
        radians = (angle + 10) * (M_PI / 180);
        int x2 = centerX + static_cast<int>(radius * cos(radians));
        int y2 = centerY + static_cast<int>(radius * sin(radians));
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}
