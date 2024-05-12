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

    proto::KeyEvent keyEvent;

    if (!keyEvent.ParseFromString(buffer))
    {
        std::cerr << "Failed to parse key event." << std::endl;
        return;
    }

    keyEvents.push(keyEvent);

    // // client address
    // std::cout << "Client: " << inet_ntoa(cliaddr.sin_addr) << std::endl;
    // std::cout << "Client: " << buffer << std::endl;
}

void JoyInterface::sendMessage(const char * message)
{
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
           (const struct sockaddr *)&cliaddr, len);
    std::cout << "Message sent to client." << std::endl;
}

void JoyInterface::run()
{
    while (true)
    {
        this->receiveMessage();
        this->sendMessage("Hello from server");
    }
}

proto::KeyEvent JoyInterface::getKeyEvent()
{
    proto::KeyEvent keyEvent = keyEvents.front();
    keyEvents.pop();
    return keyEvent;
}
