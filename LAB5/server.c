// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// #define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
    int ans = 0;
    short PORT = 8080;
    printf("Enter 1 for UDP else 0 for TCP: \n");
    scanf("%d", &ans);

    printf("Enter PORT NO: \n");
    scanf("%hi", &PORT);

    if (ans)
    {
        int sockfd;
        struct sockaddr_in servaddr, cliaddr;
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(PORT);
        if (bind(sockfd, (const struct sockaddr *)&servaddr,
                 sizeof(servaddr)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        int len = sizeof(cliaddr);

        printf("Server Started in UDP mode in port :%hi\n", PORT);

        //computation
        char input[MAXLINE], res[MAXLINE] = "hello";
        recvfrom(sockfd, &input, sizeof(input),
                 0, (struct sockaddr *)&cliaddr,
                 &len);
        printf("Client : %s\n", input);
        srand(time(0));
        int val = rand() % (4 + 1 - 0) + 0;
        char array[][10] = {"q1", "q2", "q3", "q4", "q5"};
        strcpy(res, array[val]);
        if (1)
        {
            sendto(sockfd, &res, sizeof(res),
                   0, (const struct sockaddr *)&cliaddr,
                   len);
            printf("Response sent to client: %s\n", res);
        }
        else
        {
            char res[MAXLINE] = "invalid input";
            sendto(sockfd, &res, sizeof(res),
                   0, (const struct sockaddr *)&cliaddr,
                   len);
            printf("Invalid input\n");
        }
    }
    else
    {
        int server_fd, new_socket, valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                       &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);
        if (bind(server_fd, (struct sockaddr *)&address,
                 sizeof(address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("Server Started in TCP mode in port :%hi\n", PORT);

        char input[MAXLINE], res[MAXLINE];
        read(new_socket, &input, sizeof(input));
        printf("Client : %s\n", input);
        srand(time(0));
        int val = rand() % (4 + 1 - 0) + 0;
        printf("%d", val);
        char array[][10] = {"q1", "q2", "q3", "q4", "q5"};
        strcpy(res, array[val]);
        if (1)
        {
            send(new_socket, &res, sizeof(res), 0);
            printf("QUote sent to client\n");
        }
        else
        {
            char res[MAXLINE] = "invalid input";
            send(new_socket, &res, sizeof(res), 0);
            printf("Invalid input\n");
        }
    }

    return 0;
}
