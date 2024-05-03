#include "../include/main.hpp"

#undef main

constexpr int SCREEN_WIDTH = 900;
constexpr int SCREEN_HEIGHT = 450;
constexpr int MS_PER_FRAME = 16; // ~60 FPS

int main()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
                  << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Desafio OxeBots Equipe 1", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cerr << "A janela não pôde ser criada! SDL_Error: "
                  << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        std::cerr << "Não foi possível criar o renderizador! SDL_Error: "
                  << SDL_GetError() << std::endl;
        return 1;
    }

    Field field(SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Color red = {200, 0, 0, 255};

    Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, red);

    ball.setSpeed(10, -10);

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        // Desenha o campo
        field.draw(renderer);
        ball.draw(renderer);

        ball.move();

        // Atualizar a tela
        SDL_RenderPresent(renderer);

        // Atraso para manter a taxa de quadros constante em ~60 FPS
        SDL_Delay(MS_PER_FRAME);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    // Fechar os recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
