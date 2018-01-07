#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main()
{
  int fd;
  if ( (fd = creat("file.hole", 0640)) < 0 )
  {
    cerr << "create error\n";
    exit(1);
  }
  
  if ( write(fd, buf1, 10) != 10 )
  {
    cerr << "buf1 write error\n";
    exit(1);
  }

  /*offset now = 10 */
  if ( lseek(fd, 40, SEEK_SET) == -1 )
  {
    cerr << "lseek error\n";
    exit(1);
  }
  
  /* offset now = 40 */
  if ( write(fd, buf2, 10) != 10 )
  {
    cerr << "buf2 write error\n";
    exit(1);
  }
 
  /*offset now = 50*/
  return 0;
}
