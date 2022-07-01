#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
int main()
{
    int sockfd, newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char a[50];
    time_t now;
    struct tm present;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // create a socket for communication
    // AF_INET for IPv4 addresses
    // SOCK_STREAM provides reliable, two-way, connection-based byte streams
    // 0 for default protocol for the socket
    if (sockfd < 0)
    {
        printf("socket failed\n");
        exit(0);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // INADDR_ANY - Accept connections from any address (client)
    // change address to the client IPv4 Address to accept only on client
    if (serv_addr.sin_addr.s_addr < 0)
    {
        printf("Invalid IP address: Unable to decode\n");
        exit(0);
    }
    serv_addr.sin_port = htons(13);
    // Binding to any port below 1024 might fail
    // You will need root previliges to bind to this (13) port then

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Bind failed\n");
        exit(1);
    }
    if (listen(sockfd, 5) < 0)
    {
        printf("Listen failed\n");
        exit(0);
    }

    clilen = sizeof(cli_addr);
    printf("Waiting for clients' messages (\'exit\' to close)\n");
    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
        memset(a, 0, sizeof(a));
        read(newsockfd, a, 50);

        time(&now); // gets present time in seconds

        present = *localtime(&now);
        // localtime breaks time t variable ' now' into 'stuct tmn'
        // and returns the pointer to the newly created sturcture
        // The structure 1S copied into 'present'

        sprintf(a, "Time : %d-%d-%d %d:%d:%d\n", present.tm_year + 1900, present.tm_mon + 1, present.tm_mday, present.tm_hour, present.tm_min, present.tm_sec);
        // The formatted date and time (as string) is copied into char *a' using sprintf
        write(newsockfd, a, 50);
        close(newsockfd);
    }
    return 0;
}
