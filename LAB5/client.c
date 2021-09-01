// client side implementation of UDP client-server model
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

// #define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
    int ans = 0;
    short PORT = 8080;
    printf("Enter 1 for UDP else 0 for TCP (The one in which server is running): \n");
    scanf("%d", &ans);

    printf("Enter PORT NO(The one in which server is running):  \n");
    scanf("%hi", &PORT);

    if (ans)
    {
        int sockfd;
        struct sockaddr_in servaddr;
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = INADDR_ANY;

        printf("Server Started in UDP mode in port :%hi\n", PORT);

        int len;
        char input[4] = "qotd", res[MAXLINE];
        int choice = 1;
        do
        {
            sendto(sockfd, &input, sizeof(input),
                   0, (const struct sockaddr *)&servaddr,
                   sizeof(servaddr));
            printf("value sent: %s\n", input);

            recvfrom(sockfd, &res, sizeof(res),
                     0, (struct sockaddr *)&servaddr,
                     &len);
            printf("Response from server : %s\n", res);
            printf("Do you want to get more quotes? 1 for yes 0 for no");
            scanf("%d", &choice);
        } while (choice);
    }
    else
    {

        int sock = 0;
        struct sockaddr_in serv_addr;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        printf("Server Started in TCP mode in port :%hi\n", PORT);
        char input[MAXLINE] = "qotd", res[MAXLINE];
        int choice = 1;
        do
        {
            send(sock, &input, sizeof(input), 0);
            printf("value sent: %s\n", input);

            read(sock, &res, sizeof(res));
            printf("Respone form server: %s\n", res);
            printf("Do you want to get more quotes? 1 for yes 0 for no");
            scanf("%d", &choice);
        } while (choice);
    }

    return 0;
}
