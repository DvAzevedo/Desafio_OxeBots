#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <limits> 

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
    Joy() : len(0), buffer{0}
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
        std::cout << "Message sent to server." << std::endl;
    }

    void receiveMessage()
    {
        len = sizeof(servaddr);
        int n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                         (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        std::cout << "Server: " << buffer << std::endl;
    }

    void sendKeyPress()
    {
        std::cout << "Press a key: ";
        char key = getchar();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');  // Clear input buffer
        sendMessage(&key);
    }

    ~Joy() { close(sockfd); }
};

int main()
{
    Joy client;

    client.sendKeyPress();
    client.receiveMessage();

    return 0;
}
