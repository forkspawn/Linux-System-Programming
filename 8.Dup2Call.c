#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

void main()
{
     int ofd,nfd=1,ret;
     char buf[20]="Welcome hahah";

     ofd=open("text.txt",O_RDWR);
     if(ofd<0)
     {
        printf("Failed to open the file\n");
        exit(1);
     }

     printf("File is opened succefully\n"); 
     ret=dup2(ofd,nfd);
     if(ret<0)
     {
        printf("Fail to duplicate\n");
        exit(2);
     }

     printf("ret fd=%d\n",ret); //printf this internally calls write system call

     printf("%s\n",buf);
     close(ofd);
}

/*to get output after dup2 call, put > operator while
executing the ./a.out > 1.txt , this will save the ouput
to the to the text file and normally it will be get updated
into the text.txt file*/
