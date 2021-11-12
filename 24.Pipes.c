#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define BUF 50

int main(int argc, char *argv[])
{
    int pfd[2],loop=0;
    char buf[BUF]={};
    ssize_t numRead;
    

    if(argc<2)
    {
        printf("Give a string in terminal \nInavlid Input\n");
        exit(1);

    }

    if(pipe(pfd)==-1)
        exit(1);

    switch(fork())
    {
        case -1:
            exit(-1);
        //creates a pipe
        case 0:
            //child reads from pipe
            if(close(pfd[1])==-1)
                //write end is unused
                exit(-1);
            for(;;)
            {
                // read data from pipe, echo on stdout
                strcpy(buf,"");
                numRead=read(pfd[0],buf,BUF);
                if(numRead==-1)
                    exit(-1);
                if(numRead==0)
                {
                    printf("\nChild: parent closed write end\n");
                    break;
                }
                //end of file
                printf("\ndata received in child process is %s\n",buf);
            }
            if(close(pfd[0])==-1)
                exit(-1);
            break;
        default:
            //parent write to pipe
            if(close(pfd[0]==-1))
                //read end is unused
                exit(-1);
            printf("\nParent: sending user input string to child process %s\n",argv[1]);
            write(pfd[1],argv[1],strlen(argv[1]));
            sleep(2);
            if(close(pfd[1])==-1)
                exit(-1);
            printf("\nParent: closed write end\n");
            wait(NULL);
            exit(0);
    }
}











