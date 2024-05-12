#ifndef JOY_INTERFACE_HPP
#define JOY_INTERFACE_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <queue>

#include "../proto/JoyMessage.pb.h"

#define PORT 8080
#define MAXLINE 1024

class JoyInterface
{
   private:
    // UDP variables
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char buffer[MAXLINE];

    // Protocol Buffers variables
    std::queue<proto::KeyEvent> keyEvents;

   public:
    JoyInterface();

    void receiveMessage();

    proto::KeyEvent getKeyEvent();

    bool hasKeyEvent();

    void sendMessage(const char * message);

    void run();

    inline ~JoyInterface() { close(sockfd); }
};

#endif  // JOY_INTERFACE_HPP
