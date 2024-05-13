#include "../include/main.hpp"

using namespace std;

int mainFunction(JoyInterface & ji)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
                  << std::endl;
        return 1;
    }

    SDL_Window * window = SDL_CreateWindow(
      "Desafio OxeBots Equipe 1", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cerr << "A janela não pôde ser criada! SDL_Error: "
                  << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer * renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        std::cerr << "Não foi possível criar o renderizador! SDL_Error: "
                  << SDL_GetError() << std::endl;
        return 1;
    }

    Field field(FIELD_WIDTH, FIELD_HEIGHT);

    SDL_Color red = {200, 0, 0, 255};
    SDL_Color blue = {0, 0, 200, 255};
    SDL_Color green = {0, 200, 0, 255};

    Ball ball(SIDE_MARGIN + FIELD_WIDTH / 2, FIELD_HEIGHT / 2 + TOP_MARGIN, 10,
              red);
    Robot robot1(blue, SIDE_MARGIN + FIELD_WIDTH / 2 - 100,
                 FIELD_HEIGHT / 2 + TOP_MARGIN, 0, 1, ji);
    Robot robot2(green, SIDE_MARGIN + FIELD_WIDTH / 2 + 100,
                 FIELD_HEIGHT / 2 + TOP_MARGIN, M_2_PI + 2.5F, 2, ji);

    Colisions colisions(ball, {&robot1, &robot2});
    Interactions Interactions(ball, {&robot1, &robot2});
    Score Score(ball, {&robot1, &robot2});

    ball.setSpeed(0, 0);

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        Interactions.robotsThrowBall();

        // Desenha o campo
        field.draw(renderer);
        ball.draw(renderer);
        robot1.draw(renderer);
        robot2.draw(renderer);
        Score.updateScore();

        // Verifica colisões
        // colisions.checkColisions();

        ball.move();
        robot1.move();
        robot2.move();

        Interactions.robotsCatchBall();

        // colisions.checkColisions();

        // Atualizar a tela
        SDL_RenderPresent(renderer);

        // Atraso para manter a taxa de quadros constante em ~60 FPS
        SDL_Delay(MS_PER_FRAME);

        // Processa os eventos do SDL (tela principal)
        while (SDL_PollEvent(&e) != 0)
            if (e.type == SDL_QUIT) quit = true;

        // Processa os eventos do JoyInterface (controle remoto)
        while (ji.hasKeyEvent())
        {
            proto::KeyEvent key_event = ji.getKeyEvent();
            robot1.setMove(key_event);
            robot2.setMove(key_event);
        }
    }

    // Fechar os recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#undef main
int main()
{
    JoyInterface ji;

    std::thread JoyInterfaceThread(&JoyInterface::run, &ji);
    std::thread MainThread(&mainFunction, std::ref(ji));

    JoyInterfaceThread.join();
    MainThread.join();

    return 0;
}
