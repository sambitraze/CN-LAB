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
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n, len;

	int input, res;

	printf("\nEnter Number: ");
	scanf("%d", &input);

	sendto(sockfd, &input, sizeof(input),
		   0, (const struct sockaddr *)&servaddr,
		   sizeof(servaddr));
	printf("value sent: %d\n", input);

	recvfrom(sockfd, &res, sizeof(res),
			 0, (struct sockaddr *)&servaddr,
			 &len);
	;
	printf("Response from server : %d\n", res);

	close(sockfd);
	return 0;
}