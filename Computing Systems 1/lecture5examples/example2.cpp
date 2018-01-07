#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main()
{
  pid_t  pid;
  
  switch(pid = fork()) {
    case 0: 
      cout << "I'm the child\n";
      break;
    default:
      cout << "I'm the parent of " << pid << "\n";
      break;
    case -1:
      cout << "fork error";
  }
  
  return 0;
}

