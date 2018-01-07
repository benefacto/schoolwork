#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <strings.h> // for bzero
#include <unistd.h> // for read and write
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <map>
#include <sstream>
#include <math.h>
#include <errno.h>

using namespace std;

//pthread_mutex_t leaderboardLock;
// max 3 players
typedef map<int,string> LeaderboardMap;
typedef map<int,string>::iterator it_type;
int randNum;
LeaderboardMap leaderboard;

void ReadCharFromSocket(char * buffer, int newsockfd)
{
	int n;
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0)
	{
	  printf("SERVER ERROR reading from socket %s\n", strerror(errno));
	  // abort thread
	  return; // integer to handle errors
	}
}
void WriteCharToSocket(char * buffer, int length, int newsockfd)
{
	int n;
	n = write(newsockfd,buffer,length);
	if (n < 0)
	{
	  printf("SERVER ERROR writing to socket %s\n", strerror(errno));
	  // abort thread
	  return; // integer to handle errors
	}
}

// change to return integer to handle errors
// for each client:

string ReadNameFromClient(char * buffer, int newsockfd)
{
	char * bufferConst;
	ReadCharFromSocket(buffer,newsockfd);
	bufferConst = buffer;
	string name(bufferConst);
	return name;
}
int RandomNumberGeneration()
{
	int randNum = rand() % 1000;
	cout << "\nRandom number is " << randNum << "\n";
	return randNum;
}
int ReadGuessFromClient(char * buffer, int newsockfd)
{
	int guess = 0;
	const char * bufferConst;
	ReadCharFromSocket(buffer,newsockfd);
	bufferConst = buffer;
	guess = atoi(bufferConst);
	return guess;
}
void WriteGuessResultToClient(int result, char * buffer, int newsockfd)
{
	char result_string[32];
	char message[] = "Result of guess: ";
	int length = 0;
	
	sprintf(result_string, "%d.\n\n", result);
	strcat(message,result_string);
	bzero(buffer,256);
	buffer = message;
	length = strlen(buffer);
	WriteCharToSocket(buffer,length,newsockfd);
}

void WriteVictoryMessageToClient(int turns, char * buffer, int newsockfd)
{
	char turns_string[32];
	char message[] = "Congratulations! Total turns: ";
	int length = 0;
	
	sprintf(turns_string, "%d.\n\n", turns);
	strcat(message,turns_string);
	bzero(buffer,256);
	buffer = message;
	length = strlen(buffer);
	WriteCharToSocket(buffer,length,newsockfd);
}

void UpdateLeaderboard(string name, int numGuesses) 
{
	leaderboard[numGuesses] = name;
}

void WriteLeaderboardToClient(char * buffer, int newsockfd) 
{
	int index = 1;
	stringstream ss;
	it_type it;
	int length = 0;
	
	ss << "Leader board:\n";
	for (it = leaderboard.begin(); it != leaderboard.end(); it++)
	{
		if (index <= 3)
		{
			ss << index;
			ss << ". ";
			ss << it->second;
			ss << " "; 
			ss << it->first; 
			ss << "\n";
			index++;
		}
		else
		{
			break;
		}
	}
	bzero(buffer,256);
	buffer = const_cast<char*>(ss.str().c_str());
	length = strlen(buffer);
	WriteCharToSocket(buffer,length,newsockfd);
}

void CloseConnectionWithClient(int newsockfd)
{
	if(close(newsockfd) < 0)
	{
		printf("SERVER ERROR closing socket %s\n", strerror(errno));
	}
}
void ClientThreadFunction(int newsockfd)
//void *args_p)
{
	//int newsockfd = *(int * (args_p));

	int guess = 0;
	int result = -1;
	int turns = 0;
	int randNum = 0;
	char buffer[256];
	string name;
		
	// for each client:
	name = ReadNameFromClient(buffer,newsockfd);
	randNum = RandomNumberGeneration();
	// guessing cycle
	while (result != 0)
	{
		guess = ReadGuessFromClient(buffer,newsockfd);
		result = abs((randNum - guess));
		WriteGuessResultToClient(result,buffer,newsockfd);
		turns++;
	}
	// only if guess is successful:
	WriteVictoryMessageToClient(turns,buffer,newsockfd);
	// begin critical section
	//pthread_mutex_lock(&leaderboardLock);
	UpdateLeaderboard(name,turns);
	WriteLeaderboardToClient(buffer,newsockfd);
	//pthread_mutex_unlock(&leaderboardLock);
	// end critical section
	CloseConnectionWithClient(newsockfd);
}
void ListenAndConnectClient(sockaddr_in cli_addr, int sockfd)
{
	socklen_t clilen;
	//pthread_t clientThreadId;
	int newsockfd;
	//int threadCreationStatus;

	listen(sockfd,5);
	// if error from client, abort thread, not crash server
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,(struct sockaddr *)
					 &cli_addr, &clilen);
	if(newsockfd < 0)
	{
		printf("SERVER ERROR on accept %s\n", strerror(errno));
	}
	else
	{
		/*
		int * args_p = newsockfd;
		threadCreationStatus = 
			pthread_create(&clientThreadId, NULL, ClientThreadFunction, (void *) args_p);
		if(threadCreationStatus < 0)
		{
			printf(stderr,"SERVER ERROR creating client thread");
			// abort thread
			return;
		}
		*/
		ClientThreadFunction(newsockfd);
	}
}

// setup Server & perform Server processes:
int main(int argc, char* argv[])
{
	//pthread_mutex_init(&leaderboardLock, NULL);
	while(true)	// handle multiple clients
	{
		int sockfd, portno;
		struct sockaddr_in serv_addr, cli_addr;

		if(argc < 2)
		{
			printf("SERVER ERROR, no port provided %s\n", strerror(errno));
			exit(1);
		}
		/* if socket function creates/uses listening socket fails,
		abort server with appropriate error message
		*/
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if( sockfd < 0)
		{
			printf("SERVER ERROR opening socket %s\n", strerror(errno));
			exit(1);
		}

		bzero((char *) &serv_addr, sizeof(serv_addr));
		portno = atoi(argv[1]);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(portno);
		serv_addr.sin_addr.s_addr = INADDR_ANY;

		if(bind(sockfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0)
		{
			printf("SERVER ERROR on binding %s\n", strerror(errno));
			exit(1);
		}
	
		ListenAndConnectClient(cli_addr,sockfd);
	}
	return 0;
}