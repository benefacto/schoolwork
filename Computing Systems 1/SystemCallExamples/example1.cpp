#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main(int argc, char *argv[])
{
    int fd;

    if(argc != 2)
    {
        cout << "\n Usage :  \n";
        return 1;
    }

    errno = 0;
    fd = open(argv[1],O_RDONLY);

    if(fd == -1)
    {
        cout << "\n open() failed with error " << strerror(errno) << "\n";
        return 1;
    }
    else
    {
        cout << "\n Open() Successful\n";
        /* open() succeeded, now one can do read operations
         * on the file opened since we opened it in read-only
         * mode. Also once done with processing, the file needs
         * to be closed. Closing a file can be achieved using
         * close() function. */
    }

    return 0;
}
