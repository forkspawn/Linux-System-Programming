#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

#define FILE "text.txt"

void main()
{
    int fd=0,ret;
    char buf[30]="What is \t  goin on"; //char buf[10]="aaaaaaaaaaaa";

    fd=open(FILE,O_RDWR);
    if(fd<0)
    {
        printf("Failed to open the file");
        exit(1);
    }

    printf("Returned fd values = %d \n",fd);

    ret=write(fd,buf,20); // this writes contents in buf to text.txt of 10 bytes
    if(ret<0)
    {
        printf("Failed to read data\n");
        exit(2);
    }
    
    close(fd);
}

