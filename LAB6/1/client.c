// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

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

    struct calc
    {
        int a;
        int b;
        char op;
    };

    struct calc c;
    float res;

    printf("\nEnter first number: ");
    scanf("%d", &c.a);

    printf("\nEnter second number: ");
    scanf("%d", &c.b);

    printf("\nEnter operator:");
    scanf(" %c", &c.op);

    send(sock, &c, sizeof(c), 0);
    printf("value sent: %d %c %d\n", c.a, c.op, c.b);

    read(sock, &res, sizeof(res));
    printf("Sum form server: %f\n", res);

    return 0;
}
