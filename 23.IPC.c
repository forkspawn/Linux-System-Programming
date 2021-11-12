/* IPC - Are used to send/receive data between process, IPC are also used to synchronize between process.
 * IPC are usually communication based or synchroniztion based
 * Communication Based:
   1. Data transfer based: ex-PIPE,FIFO,Message Queue and Socket
   2. Memory Sharing based: Shared Memory Based
 * Synchorinzation Based:
   1. Semaphore
   2. Mutex(used for threads)
   3. Condition Variables(used for threads)
 * 
 * PIPES: It is a byte steam used for IPC, it has 2 ends, a read end fd[0] a write end fd[1].
   Pipes are unidirectional, they have a limited capacity usually 65kb. A pipe is simply a buffer 
   maintained in kernel memory. When pipe is full of data, further writes to PIPI will be blocked,
   until the receive end process removes the data from pipe. Writing to PIPE puts data, where as 
   reading data from PIPE removes the data from PIPE.
 * 
 * int pipe(int fd[2]);
 * pipe() open two file discriptors, one if fd[0] and other in fd[1].
 * Returns 0 on success, or-1 on error.
 */

#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int fd[2];
    char buff[50];
    char data[50]={};
    
    //open a pipe
    if(pipe(fd)==-1)
    {
        perror("Pipe error\n");
        exit(1);
    }
    sprintf(buff,"PIPE data flow demo:");
    write(fd[1],buff,strlen(buff));
    printf("\n");

    //reading pipe and storing data in data buffer
    read(fd[0],data,5);
    printf("%s\n",data);

    read(fd[0],data,5);
    printf("%s\n",data);

    read(fd[0],data,10);
    printf("%s\n",data);



}




