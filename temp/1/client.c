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

	char input[MAXLINE], res[MAXLINE];

	printf("\nEnter word or sentence: ");
	fgets(input, MAXLINE, stdin);

	sendto(sockfd, &input, sizeof(input),
		   0, (const struct sockaddr *)&servaddr,
		   sizeof(servaddr));
	printf("value sent: %s\n", input);

	recvfrom(sockfd, &res, sizeof(res),
			 0, (struct sockaddr *)&servaddr,
			 &len);
	;
	printf("Response from server : %s\n", res);

	close(sockfd);
	return 0;
}