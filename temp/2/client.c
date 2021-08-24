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

	int n, len;
	printf("\nEnter n: ");
	scanf("%d", &n);

	int res[n], input[n];
	for (int i = 0; i < n; i++)
	{
		printf("\nEnter element %d:", i + 1);
		scanf("%d", &input[i]);
	}

	
	sendto(sockfd, &n, sizeof(n),
		   0, (const struct sockaddr *)&servaddr,
		   sizeof(servaddr));
	sendto(sockfd, &input, sizeof(int) * n,
		   0, (const struct sockaddr *)&servaddr,
		   sizeof(servaddr));
	printf("value sent: \n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", input[i]);
	}

	recvfrom(sockfd, &res, sizeof(int) * n,
			 0, (struct sockaddr *)&servaddr,
			 &len);
	printf("\nvalue recived: \n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", res[i]);
	}

	close(sockfd);
	return 0;
}