// Client side implementation of UDP client-server model
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
	int arr[5] = {1, 2, 3, 4, 5};
	float res;
	struct sockaddr_in servaddr;

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

	int n;
	int len = sizeof(servaddr);

	sendto(sockfd, &arr, 5 * sizeof(int),
		   0, (const struct sockaddr *)&servaddr,
		   sizeof(servaddr));

	recvfrom(sockfd, &res, sizeof(float),
				 0, (struct sockaddr *)&servaddr,
				 &len);
	printf("avg sent from server : %f\n", res);

	close(sockfd);
	return 0;
}