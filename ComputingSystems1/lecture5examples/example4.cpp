#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
   if (fork())    /*fork, assume it always works */
      for (;;)    /* parent prints a message forever */
        cout << "I am the parent\n";
   else {
      sleep(3);   /* do nothing for three seconds */
      kill(getppid(), SIGKILL);  /* kill the parent */
   }
   return 0;
}

