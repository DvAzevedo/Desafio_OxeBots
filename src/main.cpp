#include "../include/main.hpp"

using namespace std;
#undef main
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
    SDL_Color blue = {0, 0, 200, 255};
    SDL_Color green = {0, 200, 0, 255};

    Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, red);
    Robot robot1(blue, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
    Robot robot2(green, SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);

    Colisions colisions(ball, {&robot1, &robot2});

    ball.setSpeed(0, 0);

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        // Desenha o campo
        field.draw(renderer);
        ball.draw(renderer);
        robot1.draw(renderer);
        robot2.draw(renderer);

        // Verifica colisões
        colisions.checkColisions();

        ball.move();
        robot1.move();
        robot2.move();

        colisions.checkColisions();

        // Atualizar a tela
        SDL_RenderPresent(renderer);

        // Atraso para manter a taxa de quadros constante em ~60 FPS
        SDL_Delay(MS_PER_FRAME);

        // Processa os eventos
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                robot1.setMove(e);
            }
        }
    }

    // Fechar os recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
