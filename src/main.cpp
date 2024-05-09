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

    Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, red);

    Robot robot1(blue, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);

    ball.setSpeed(-10, -10);
    robot1.SetAngle(0);
    int teste = 0;
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        if (robot1.getWithBall() && robot1.getThrowBall())
        {
            cout << "Aqui\n";
            robot1.setThrowBall(false);
            robot1.setWithBall(false);
            ball.setIsCatch(false);
            ball.setJustBeenThrow(true);
            cout << robot1.getXSpeed();
            cout << robot1.getYSpeed();
            ball.setSpeed(robot1.getXSpeed(), robot1.getYSpeed());
        }

        field.draw(renderer);
        ball.draw(renderer);
        robot1.Draw(renderer);

        ball.move();
        robot1.Move();

        if (robotCatchBall(robot1.getCoordinates(), ball.getCoordinates()))
        {
            if (!(ball.getJustBeenThrow()))
            {
                ball.setCoordinates(robot1.getCoordinates());
                ball.setIsCatch(true);
                robot1.setWithBall(true);
            }
        }
        else
        {
            ball.setJustBeenThrow(false);
        }

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
