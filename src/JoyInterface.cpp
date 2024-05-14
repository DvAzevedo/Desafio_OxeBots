#include "../include/JoyInterface.hpp"

JoyInterface::JoyInterface()
{
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;  // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void JoyInterface::receiveMessage()
{
    len = sizeof(cliaddr);
    int n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                     (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';

    // if receives -1 from client, it means that has no key event
    if (buffer[0] == '-') return;

    proto::KeyEvent keyEvent;

    if (!keyEvent.ParseFromString(buffer))
    {
        std::cerr << "Failed to parse key event." << std::endl;
        std::cerr << "Buffer: " << (char *)buffer << std::endl;
        return;
    }

    keyEvents.push(keyEvent);
}

void JoyInterface::sendMessage(const char * message)
{
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
           (const struct sockaddr *)&cliaddr, len);
}

void JoyInterface::run()
{
    while (true)
    {
        this->receiveMessage();
    }
}

proto::KeyEvent JoyInterface::getKeyEvent()
{
    proto::KeyEvent keyEvent = keyEvents.front();
    keyEvents.pop();
    return keyEvent;
}

bool JoyInterface::hasKeyEvent() { return !keyEvents.empty(); }
