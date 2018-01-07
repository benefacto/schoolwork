#include <iostream>
#include <unistd.h>
using namespace std;

int main () {
   cout << "--beginning of program\n";

   int counter = 0;
   pid_t pid = fork();

   if (pid == 0)
   {
     // child process
     int i;
     for (i = 0; i < 5; i++)
     {
       cout << "child process: counter = " 
            << ++counter << endl;
       sleep(2);
     }
   }
   else if (pid > 0)
   {
      // parent process
      int j;
      for (j = 0; j < 5; j++)
      {
        cout << "parent process: counter = "   
             << ++counter << endl;
        sleep(2);
      }
   }
   else
   {
      // fork failed
      cout << "fork() failed" << endl;
      return 1;
   }
      cout << "--end of program" << endl;
      return 0;
}
     
