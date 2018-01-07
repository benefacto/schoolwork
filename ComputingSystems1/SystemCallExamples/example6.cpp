#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
using namespace std;


int main(int argc, char * argv[]){

  struct stat st;

  if( argc < 2){
    cerr << "ERROR: Require a path\n";
    return 2;   //return status error                                             
  }

  if( stat(argv[1], &st) < 0){    
     //error, cannot stat file                        
     cerr << argv[0];   
     return 2; //return status error
  }

  if ( S_ISDIR(st.st_mode) ){
    cout << "It's a directory!\n";
    return 0;  //return status true                                               
  }

  cout << "Not a directory :(\n";
  return 1; //return status false                                            

}
