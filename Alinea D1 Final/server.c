#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>

#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <input.h>

#define PORT 6969

int serverFd, newSocket;

char **fArg;

void reportAndExit(char *str);
void sockManagement();

void argumentManagement(int argc, char **argv);
char *newCharArray(int n);

int main(int argc, char **argv)
{
  sockManagement();

  argumentManagement(argc, argv);

  pid_t pid = fork();

  printf("Passou\n");

  if ( pid < 0 )
    reportAndExit("Error on fork. main\n");

  else if ( pid > 0 )
    {
      if ( waitpid(pid, NULL, 0) < 0 )
	reportAndExit("Failed to catch exit. main\n");
    }
  else
    {
      if ( execv("./main", fArg) < 0 )
	reportAndExit("Error on execv. main\n");
    }

  close(serverFd);
  close(newSocket);

  return 0;
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s", str);
  exit(EXIT_FAILURE);
}

void sockManagement()
{
  serverFd = socket(AF_INET, SOCK_STREAM, 0);

  if ( serverFd < 0 )
    reportAndExit("socket failed. main\n");

  /* Definir as opções*/
  int true = 1;
  if ( setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &true, sizeof(true)) < 0 )
    reportAndExit("setsockopt failed. main\n");

  struct sockaddr_in address;
  bzero((char *)&address, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if ( bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0 )
    reportAndExit("bind failed. main\n");

  /* Espera por uma ligação*/
  if ( listen(serverFd, 1) < 0 )
    reportAndExit("listen failed. main\n");

  /* ver api do accept para perceberes o porque de criar addressSize*/
  int addressSize = sizeof(address);

  newSocket = accept(serverFd, (struct sockaddr *)&address,(socklen_t *)&addressSize);

  if ( newSocket < 0 )
    reportAndExit("accept failed. main\n");
}

void argumentManagement(int argc, char **argv)
{
  fArg = (char **)calloc(4, sizeof(char *));

  if ( fArg == NULL )
    reportAndExit("Memory alocation failed. argumentManagement\n");

  for( int i=0; i<4; i++ )
    fArg[i] = newCharArray(128);

  strcpy(fArg[0], "main");
  snprintf(fArg[1], 127, "%d", newSocket);
  strcpy(fArg[2], "1");
  fArg[4] = NULL;
}

char *newCharArray(int n)
{
  char *temp = (char *)calloc(n, sizeof(char));

  if ( temp == NULL )
    reportAndExit("Memory alocation failed. newCharArray\n");

  return temp;
}
