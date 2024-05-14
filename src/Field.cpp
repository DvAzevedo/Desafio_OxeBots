#include "../include/Field.hpp"

Field::Field(int width, int height) : width(width), height(height) {}

void Field::draw(SDL_Renderer * renderer)
{
    const int rec_width = width / 8;
    const int rec_height = height / 2;
    const int gol_width = SIDE_MARGIN;
    const int gol_height = height / 4;
    float radius = rec_height / 2;
    int centerX = width / 2 + SIDE_MARGIN;
    int centerY = height / 2 + TOP_MARGIN;

    // Cor de fundo
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Linhas verticais
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, centerX, TOP_MARGIN, centerX,
                       height + TOP_MARGIN);
    SDL_RenderDrawLine(renderer, SIDE_MARGIN, TOP_MARGIN, SIDE_MARGIN,
                       height + TOP_MARGIN);
    SDL_RenderDrawLine(renderer, SIDE_MARGIN + width, TOP_MARGIN,
                       SIDE_MARGIN + width, height + TOP_MARGIN);

    // Retângulo esquerdo
    SDL_Rect leftRect = {SIDE_MARGIN, height / 4 + TOP_MARGIN, rec_width,
                         rec_height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &leftRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &leftRect);

    // Retângulo direito
    SDL_Rect rightRect = {
      SIDE_MARGIN + width - rec_width + 1, height / 4 + TOP_MARGIN, rec_width,
      rec_height};  // + 1 para corrigir falha na divisao de 450 por 8
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rightRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rightRect);

    // Gol Robot 1 defende
    SDL_Rect leftGol = {0, TOP_MARGIN + 3 * gol_height / 2, gol_width,
                        gol_height};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &leftGol);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &leftGol);

    // Gol Robot 2 defende
    SDL_Rect rightGol = {SIDE_MARGIN + width + 1,
                         TOP_MARGIN + 3 * gol_height / 2, gol_width,
                         gol_height};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rightGol);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rightGol);

    // Placar
    SDL_Rect scoreboard = {0, 0, SCREEN_WIDTH, TOP_MARGIN};
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);
    SDL_RenderFillRect(renderer, &scoreboard);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &scoreboard);

    // Circulo central
    for (int angle = 0; angle < 360; angle += 10)
    {
        float radians = angle * (M_PI / 180);
        int x1 = centerX + static_cast<int>(radius * cos(radians));
        int y1 = centerY + static_cast<int>(radius * sin(radians));
        radians = (angle + 10) * (M_PI / 180);
        int x2 = centerX + static_cast<int>(radius * cos(radians));
        int y2 = centerY + static_cast<int>(radius * sin(radians));
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}
