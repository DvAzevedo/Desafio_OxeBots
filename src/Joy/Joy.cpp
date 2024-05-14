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

   public:
    bool running;

    Joy() : len(0), buffer{0}, running(true)
    {
        // Creating socket file descriptor (same as before)
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information (same as before)
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
            std::cout << "Event type: " << event.type << std::endl;
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    pressedKeys.insert(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    pressedKeys.erase(event.key.keysym.sym);
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
            std::cout << key << '\t' << std::flush;

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
        close(sockfd);
        SDL_Quit();
    }
};

int main()
{
    Joy client;

    while (client.running)
    {
        client.handleInput();
        SDL_Delay(MS_PER_FRAME);
    }

    std::cout << "Joy finished." << std::endl;
    return 0;
}
