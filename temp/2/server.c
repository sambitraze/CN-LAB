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

#define PORT 8080
#define MAXLINE 1024
// Driver code
int main()
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	// Bind the socket with the server address
	if (bind(sockfd, (const struct sockaddr *)&servaddr,
			 sizeof(servaddr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// actual part
	int len;
	int n = 0;
	len = sizeof(cliaddr); //len is value/resuslt

	recvfrom(sockfd, &n, sizeof(n),
			 0, (struct sockaddr *)&cliaddr,
			 &len);

	int input[n], res[n];
	recvfrom(sockfd, &input, sizeof(int) * n,
			 0, (struct sockaddr *)&cliaddr,
			 &len);
	printf("Client : \n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", input[i]);
	}

	for (int i = 0; i < n; ++i) 
        {
 
            for (int j = i + 1; j < n; ++j)
            {
 
                if (input[i] > input[j]) 
                {
 
                    int a =  input[i];
                    input[i] = input[j];
                    input[j] = a;
 
                }
 
            }
 
        }

	sendto(sockfd, &res, sizeof(int) * n,
		   0, (const struct sockaddr *)&cliaddr,
		   len);
	printf("\nResponse sent to client:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", input[i]);
	}

	return 0;
}
