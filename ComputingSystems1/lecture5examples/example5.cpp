#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
using namespace std;

//Define the function to be called when ctrl-c (SIGINT) signal is sent to process
void signal_callback_handler(int signum)
{
   cout << "Caught signal " << signum << "\n";
   exit(0);
}

int main()
{
  //Register  signal and signal handler
  signal(SIGINT, signal_callback_handler);

  while(1)
  {
     cout << "Program processing stuff here\n";
     sleep(1);
  }
  return 0;
}
