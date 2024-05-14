#include <SDL2/SDL.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <limits>
#include <set>

#include "../../include/GlobalVariables.hpp"
#include "../../proto/JoyMessage.pb.h"

#define PORT 8080
#define MAXLINE 1024

#include <SDL2/SDL.h>

class Button
{
   private:
    SDL_Rect rect;
    bool pressed;
    SDL_Keycode key;
    SDL_Color color;

   public:
    Button(int x, int y, int w, int h, SDL_Keycode key, SDL_Color color)
    : pressed(false), key(key), color(color)
    {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

    void handleEvent(const SDL_Event & e)
    {
        if (e.type == SDL_KEYDOWN and e.key.keysym.sym == key and !pressed)
        {
            pressed = true;
        }
        else if (e.type == SDL_KEYUP and e.key.keysym.sym == key and pressed)
        {
            pressed = false;
        }
    }

    void render(SDL_Renderer * renderer)
    {
        // Draw button background
        if (pressed)
        {
            // Fill with the color when pressed
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,
                                   color.a);
        }
        else
        {
            // White when released
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
        SDL_RenderFillRect(renderer, &rect);

        // Draw button border
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, &rect);
    }
};

class Joy
{
   private:
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len;
    char buffer[MAXLINE];
    std::set<int> pressedKeys;

    // SDL variables
    SDL_Window * window;
    SDL_Renderer * renderer;

    // players buttons
    std::vector<Button> player1Buttons;
    std::vector<Button> player2Buttons;

   public:
    bool running;

    Joy() : len(0), buffer{0}, running(true)
    {
        // Creating socket file descriptor
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = INADDR_ANY;

        // Initialize SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        // Create window
        window = SDL_CreateWindow("Joy", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, 640, 480, 0);
        if (window == nullptr)
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError()
                      << std::endl;
            SDL_Quit();
            exit(EXIT_FAILURE);
        }

        // Create renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == nullptr)
        {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError()
                      << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(EXIT_FAILURE);
        }

        // Set window color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Color red = {255, 0, 0, 255};
        SDL_Color blue = {0, 0, 255, 255};
        SDL_Color green = {0, 255, 0, 255};
        SDL_Color purple = {255, 0, 255, 255};

        // Create buttons
        player1Buttons.push_back(Button(152, 120, 20, 50, SDLK_w, blue));  // W
        player1Buttons.push_back(Button(55, 235, 50, 20, SDLK_a, blue));   // A
        player1Buttons.push_back(Button(152, 311, 20, 50, SDLK_s, blue));  // S
        player1Buttons.push_back(Button(215, 235, 50, 20, SDLK_d, blue));  // D
        player1Buttons.push_back(Button(55, 35, 50, 50, SDLK_r, purple));  // R
        player1Buttons.push_back(Button(137, 216, 50, 50, SDLK_f, red));   // F

        player2Buttons.push_back(
          Button(472, 120, 20, 50, SDLK_UP, green));  // UP
        player2Buttons.push_back(
          Button(376, 235, 50, 20, SDLK_LEFT, green));  // LEFT
        player2Buttons.push_back(
          Button(472, 311, 20, 50, SDLK_DOWN, green));  // DOWN
        player2Buttons.push_back(
          Button(535, 235, 50, 20, SDLK_RIGHT, green));  // RIGHT
        player2Buttons.push_back(
          Button(535, 35, 50, 50, SDLK_SPACE, purple));  // SPACE
        player2Buttons.push_back(
          Button(457, 216, 50, 50, SDLK_RETURN, red));  // ENTER
    }

    void sendMessage(const char * message)
    {
        sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
               (const struct sockaddr *)&servaddr, sizeof(servaddr));
    }

    void receiveMessage()
    {
        len = sizeof(servaddr);
        int n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                         (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
    }

    // Function to handle SDL events and send key presses
    void handleInput()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    pressedKeys.insert(event.key.keysym.sym);
                    for (Button & button : player1Buttons)
                        button.handleEvent(event);
                    for (Button & button : player2Buttons)
                        button.handleEvent(event);
                    break;
                case SDL_KEYUP:
                    pressedKeys.erase(event.key.keysym.sym);
                    for (Button & button : player1Buttons)
                        button.handleEvent(event);
                    for (Button & button : player2Buttons)
                        button.handleEvent(event);
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        for (int key : pressedKeys)
        {
            proto::KeyEvent keyEvent;
            switch (key)
            {
                case SDLK_LEFT:
                    keyEvent.set_key(proto::KeyType::LEFT);
                    break;
                case SDLK_RIGHT:
                    keyEvent.set_key(proto::KeyType::RIGHT);
                    break;
                case SDLK_UP:
                    keyEvent.set_key(proto::KeyType::UP);
                    break;
                case SDLK_DOWN:
                    keyEvent.set_key(proto::KeyType::DOWN);
                    break;
                case SDLK_SPACE:
                    keyEvent.set_key(proto::KeyType::SPACE);
                    break;
                case SDLK_RETURN:
                    keyEvent.set_key(proto::KeyType::ENTER);
                    break;
                case SDLK_BACKSPACE:
                    keyEvent.set_key(proto::KeyType::BACKSPACE);
                    break;
                case SDLK_w:
                    keyEvent.set_key(proto::KeyType::W);
                    break;
                case SDLK_a:
                    keyEvent.set_key(proto::KeyType::A);
                    break;
                case SDLK_s:
                    keyEvent.set_key(proto::KeyType::S);
                    break;
                case SDLK_d:
                    keyEvent.set_key(proto::KeyType::D);
                    break;
                case SDLK_r:
                    keyEvent.set_key(proto::KeyType::R);
                    break;
                case SDLK_f:
                    keyEvent.set_key(proto::KeyType::F);
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                default:
                    continue;
            }

            std::string message;
            keyEvent.SerializeToString(&message);
            sendMessage(message.c_str());
        }
    }

    ~Joy()
    {
        // Cleanup
        close(sockfd);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void renderButtons()
    {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Render buttons
        for (Button & button : player1Buttons) button.render(renderer);
        for (Button & button : player2Buttons) button.render(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
    }
};

int main()
{
    Joy client;

    while (client.running)
    {
        client.handleInput();
        client.renderButtons();
        SDL_Delay(MS_PER_FRAME);
    }

    std::cout << "Joy finished." << std::endl;
    return 0;
}
