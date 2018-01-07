#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <string>

using namespace std;

/* SERVER SECTION */
void ServerListenForClient() {}
void ServerClientConnectsCreateThread() {}
// for each client:
void ServerNumberGeneration() {}
void ServerReceiveNameFromClient() {}
void ServerReceiveGuessFromClient(int guess) {}
void ServerSendIncorrectGuessToClient(int result) {}
// only if guess is successful:
void ServerSendCorrectGuessToClient(int guess) {}
void ServerSendVictoryMessageToClient() {}
void ServerSendLeaderboardToClient() {}
void ServerUpdateLeaderboard(string &leaderboard.front()) {}
void ServerCloseConnectionWithClient() {}
// setup Server & perform Server processes:
int Server(int argc, char *argv[])
{
  int sockfd, newsockfd, portno, clilen, n;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  // remember to lock leaderboard
  vector<string> leaderboard {}; // max 3 players

  if(argc < 2)
	{
	  fprintf(stderr,"ERROR, no port provided");
	  exit(1);
	}
  /* if socket function creates/uses listening socket fails,
	 abort server with appropriate error message
  */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if( sockfd < 0)
	{
	  fprintf(stderr,"ERROR opening socket");
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
	  fprintf(stderr, "ERROR on binding");
	  exit(1);
	}
  listen(sockfd,5);
  // if error from client, abort thread, not crash server
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd,(struct sockaddr *)
					 &cli_addr, &clilen);
  if(newsockfd < 0)
	{
	  fprintf(stderr, "ERROR on accept");
	  return 1;
	}
  // read from socket
  bzero(buffer,256);
  n = read(newsockfd,buffer,255);
  if (n < 0)
	{
	  fprintf(stderr,"ERROR reading from socket");
	  return 1;
	}
  printf("Here is the message: %s",buffer);
  // write to socket
  n = write(newsockfd, "I got your message",18);
  if (n < 0)
	{
	  fprintf(stderr, "ERROR writing to socket");
	  return 1;
	}
}

/* CLIENT SECTION */
void ClientConnectWithServer() {}
void ClientNamePrompt() {}
void ClientSendNameToServer() {}
void ClientNumberGuess() {}
void ClientSendGuessToServer() {}
void ClientReceiveGuessResult(int result) {}
void ClientIncorrectGuess() {}
// only if guess is successful:
void ClientReceiveVictoryMessage() {}
void ClientPrintVictoryMessage() {}
void ClientReceiveLeadboardFromServer() {}
void ClientPrintLeaderboard() {}
void ClientCloseConnection() {}
// setup Client & perform Client processes:
void Client(void IPaddress, void portOfServerProcess) {}

int main(int argc, char* argv[])
{
  Server(argc,&argv);
  Client();
  return 0;
}
