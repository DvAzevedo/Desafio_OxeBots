#include <arpa/inet.h>
#include <ncurses.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <limits>

#include "../../proto/JoyMessage.pb.h"

#define PORT 8080
#define MAXLINE 1024

class Joy
{
   private:
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len;
    char buffer[MAXLINE];

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

    void sendKeyPress()
    {
        int c = getch();

        std::cout << c << '\t' << std::flush;

        proto::KeyEvent keyEvent;
        switch (c)
        {
            case KEY_LEFT:
                keyEvent.set_key(proto::KeyType::LEFT);
                break;
            case KEY_RIGHT:
                keyEvent.set_key(proto::KeyType::RIGHT);
                break;
            case KEY_UP:
                keyEvent.set_key(proto::KeyType::UP);
                break;
            case KEY_DOWN:
                keyEvent.set_key(proto::KeyType::DOWN);
                break;
            case ' ':
                keyEvent.set_key(proto::KeyType::SPACE);
                break;
            case 10:
                keyEvent.set_key(proto::KeyType::ENTER);
                break;
            case KEY_BACKSPACE:
                keyEvent.set_key(proto::KeyType::BACKSPACE);
                break;
            case 'W':
                keyEvent.set_key(proto::KeyType::W);
                break;
            case 'w':
                keyEvent.set_key(proto::KeyType::W);
                break;
            case 'A':
                keyEvent.set_key(proto::KeyType::A);
                break;
            case 'a':
                keyEvent.set_key(proto::KeyType::A);
                break;
            case 'S':
                keyEvent.set_key(proto::KeyType::S);
                break;
            case 's':
                keyEvent.set_key(proto::KeyType::S);
                break;
            case 'D':
                keyEvent.set_key(proto::KeyType::D);
                break;
            case 'd':
                keyEvent.set_key(proto::KeyType::D);
                break;
            case 'R':
                keyEvent.set_key(proto::KeyType::R);
                break;
            case 'r':
                keyEvent.set_key(proto::KeyType::R);
                break;
            case 'F':
                keyEvent.set_key(proto::KeyType::F);
                break;
            case 'f':
                keyEvent.set_key(proto::KeyType::F);
                break;
            case 3:  // CTRL('C') - quit
                running = false;
            default:
                return;
        }

        std::string message;
        keyEvent.SerializeToString(&message);
        sendMessage(message.c_str());
    }

    ~Joy() { close(sockfd); }
};

int main()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    Joy client;

    while (true)
    {
        client.sendKeyPress();

        if (!client.running) break;
    }

    std::cout << "Joy finished." << std::endl;
    refresh();
    getch();
    endwin();
    return 0;
}
