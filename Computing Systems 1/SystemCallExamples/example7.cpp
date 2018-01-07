#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

int main()
{
  pid_t  pid;
  pid = fork();
  if (pid < 0) { 		// error
    exit(-1);
  }
  else if (pid == 0) { 	// child process
    execlp("/bin/ls", "ls", NULL);
  }
  else { 			// parent process
    wait(NULL);
    cout << "Child Complete." << endl;
  }
  return 0;
}

