/*  A Fifo is similar to pipe, which is also called as 'name pipe'.
 *  Differences between pipes and fifo:
 *  1. A FIFO has a name within the file system and is opened in the same way as a regular file,
    where as PIPES does not have a name in the file system.
 *  2. FIFO to be used for communication between unrelated proccess eg: Client and server, but 
    PIPES are used to send data only between realated process. eg: Parent and child.
 *``Once a FIFO had been opened, we use the same I/O system calls as are used with pipes and other
    files i.e: read,write,close. Just as with pipes, a FIFO has a write end and a read end, and
    data is read from the FIFo in the same order as it is written.(This means first the data written to
    write end of fifo, is the ifrst read out from the reading end of fifo).
 *  int mkfifo(const char *pathname, mode_t mode);
 *  returns 0 on success, or -1 on error.
 */

#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    char arr[60];

    //creating the name file(FIFO)
    //mkfifo(pathname,permission)
    mkfifo(myfifo,0660);
    fd=open(myfifo,O_WRONLY);
    while(1)
    {
        printf("\nEnter string to be sent via fifo\n");
        fgets(arr,60,stdin);

        write(fd,arr,strlen(arr)+1);
    }
    close(fd);
    return 0;
}



