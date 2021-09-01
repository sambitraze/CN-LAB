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

int wordCount(char s[MAXLINE])
{
	int count = 0;
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == ' ' && s[i + 1] != ' ')
			count++;
	}
	return count + 1;
}

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
	int word[5];
	char input[5][MAXLINE];

	len = sizeof(cliaddr);

	recvfrom(sockfd, &input, sizeof(input),
			 0, (struct sockaddr *)&cliaddr,
			 &len);
	for (int i = 0; i < 5; i++)
	{
		word[i] = wordCount(input[i]);
	}
	
	printf("\nClient : %s (Word Count %d)", input[0], word[0]);
	printf("\nClient : %s (Word Count %d)", input[1], word[1]);
	printf("\nClient : %s (Word Count %d)", input[2], word[2]);
	printf("\nClient : %s (Word Count %d)", input[3], word[3]);
	printf("\nClient : %s (Word Count %d)", input[4], word[4]);

	int max = word[0];
	for (int i = 0; i < 5; i++)
	{
		if (word[i] > max)
			max = word[i];
	}

	sendto(sockfd, &max, sizeof(max),
		   0, (const struct sockaddr *)&cliaddr,
		   len);
	printf("\nMax Word sent to client\n");

	return 0;
}
