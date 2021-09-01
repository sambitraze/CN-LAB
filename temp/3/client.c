// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
#define MAXLINE 1024

int main(int argc, char const *argv[])
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

    //actual    
	char query[MAXLINE];
    int res;

    printf("\nEnter word to be searched: ");
		scanf("%[^\n]%*c", query);

    send(sock, &query, sizeof(query), 0);
    printf("value sent: %s\n", query);

    read(sock, &res, sizeof(res));
    printf("No of word found form server: %d\n", res);

    return 0;
}
