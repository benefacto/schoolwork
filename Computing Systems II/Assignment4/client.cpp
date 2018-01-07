#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 		//defines structure hostent
#include <iostream>
#include <string>
#include <strings.h> // for bzero & bzero
#include <unistd.h> // for read and write
#include <cstdlib>
#include <cstdio>
#include <cstring> // for strlen
#include <errno.h>

using namespace std;

void ReadCharFromSocket(char * buffer, int sockfd)
{
	int n;
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if (n < 0)
	{
		printf("CLIENT ERROR reading char from socket %s\n", strerror(errno));
		exit(1);
	}
	printf("%s",buffer);
}
void WriteCharToSocket(char * buffer, int sockfd)
{
	int n;
	const char * bufferConst;	// for strlen parameter
	bufferConst = buffer;
	n = write(sockfd,buffer,strlen(bufferConst));
	if (n < 0)
	{
		printf("CLIENT ERROR writing char to socket %s\n", strerror(errno));
		exit(1);
	}
}
int ConnectWithServer(int argc, char *argv[])
{
	int sockfd, portno;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	if (argc < 3)
	{
		printf("CLIENT ERROR usage hostname port %s\n", strerror(errno));
		exit(1);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("CLIENT ERROR opening socket %s\n", strerror(errno));
		exit(1);
	}
	
	server = gethostbyname(argv[1]); 
	if (server == NULL)
	{
		printf("CLIENT ERROR, no such host %s\n", strerror(errno));
		exit(1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);
	
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	{
		printf("CLIENT ERROR connecting %s\n", strerror(errno));
		exit(1);
	}
	return sockfd;
}
void NamePrompt(char * buffer)
{
	printf("Welcome to Number Guessing Game!\n");
	printf("Enter your name: ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
}
void WriteNameToServer(int sockfd, char * buffer)
{
	WriteCharToSocket(buffer,sockfd);
}
void NumberGuess(char * buffer)
{
	printf("Enter a guess (0000-9999): ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
}
void WriteGuessToServer(int sockfd, char * buffer)
{
	WriteCharToSocket(buffer,sockfd);	
}
int ReadGuessResult(int sockfd, char * buffer)
{
	int result = -1;
	char * correct;
	ReadCharFromSocket(buffer,sockfd);
	correct = strstr(buffer,"Result of guess: 0.");
	if(correct)
	{
		result = 0;
		return result;
	}
	return result;
}
void IncorrectGuess() {}
// only if guess is successful:
void ReadVictoryMessage(int sockfd, char * buffer)
{
	ReadCharFromSocket(buffer,sockfd);
}
void ReadLeadboardFromServer(int sockfd, char * buffer)
{
	ReadCharFromSocket(buffer,sockfd);	
}
void ClientCloseConnection(int sockfd)
{
	if(close(sockfd) < 0)
	{
		printf("CLIENT ERROR closing socket on client %s\n", strerror(errno));
		exit(1);
	}
}

// setup Client & perform Client processes:
int main(int argc, char *argv[])
{
	int result = -1;
	int sockfd = 0;
	char buffer[256];
	
	sockfd = ConnectWithServer(argc, argv);
	NamePrompt(buffer);
	WriteNameToServer(sockfd, buffer);
	// guessing cycle
	while(result != 0)
	{
		NumberGuess(buffer);
		WriteGuessToServer(sockfd, buffer);
		result = ReadGuessResult(sockfd,buffer);
	}
	// only if guess is successful:
	ReadVictoryMessage(sockfd,buffer);
	ReadLeadboardFromServer(sockfd,buffer);
	ClientCloseConnection(sockfd);
	return 0;
}