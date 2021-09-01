// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
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

    //actual

    struct calc
    {
        int a;
        int b;
        char op;
    };

    struct calc c;
    float res = 0.0;

    read(new_socket, &c, sizeof(c));
    printf("Client: %d %c %d\n", c.a, c.op, c.b);

    if (c.op == '+')
        res = (float)(c.a + c.b);
    else if (c.op == '-')
        res = (float)(c.a - c.b);
    else if (c.op == '*' || c.op == 'x' || c.op == 'X')
        res = (float)(c.a * c.b);
    else if (c.op == '/')
        res = (float)c.a / (float)c.b;

    send(new_socket, &res, sizeof(res), 0);
    printf("Result sent to client: %f\n", res);
    return 0;
}
