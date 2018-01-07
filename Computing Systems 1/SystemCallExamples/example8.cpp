#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
     cout << "\n Please pass in the directory name\n";
     return 1;
   }

   DIR *dp = NULL;
   struct dirent *dptr = NULL;
   //buffer for storing the directory path
   char buff[128];
   memset(buff, 0, sizeof(buff));

   //copy the path set by the user
   strcpy(buff, argv[1]);
   
   //open the directory stream
   if ((dp = opendir(argv[1])) == NULL)
   {
      cout << "\n cannot open input directory" << argv[1] << "\n";
      exit(1);
   }else
   {
     //check if user suppplied '/' at the end of directory name
     if(buff[strlen(buff) - 1] == '/')
     {
        strncpy(buff + strlen(buff), "newDir/", 7);
     }
     else
     {
        strncpy(buff + strlen(buff), "/newDir/", 8);
     }
     
     cout << "\n Creating a new directory " << buff << "\n";

     //create a new directory
     mkdir(buff, S_IRWXU|S_IRWXG|S_IRWXO);
     cout << "\n The contents of directory " << argv[1] << " are as follows\n";
     
    //Read the directory contents
    while((dptr = readdir(dp)) != NULL)
    {
       cout << dptr->d_name << "\n";
    }     
    //Close the directory stream
    closedir(dp);
    //remove the new directory created by us
    //rmdir(buff);
    cout << "\n";
   }
   
   return 0; 
}
