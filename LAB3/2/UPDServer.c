// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
	int sockfd;
	int arr[5];
	float res;
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
	len = sizeof(cliaddr); 

	recvfrom(sockfd, &arr, 5 * sizeof(int),
				 0, (struct sockaddr *)&cliaddr,
				 &len);
	printf("Client : %d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
	res = (arr[0]+arr[1]+arr[2]+arr[3]+arr[4])/5;

	sendto(sockfd, &res, sizeof(float),
		   0, (const struct sockaddr *)&cliaddr,
		   len);
	printf("avg sent to client\n");

	return 0;
}
