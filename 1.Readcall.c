#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

#define FILE "text.txt"

void main()
{
    int fd=0,ret;
    char buf[10]; //char buf[10]="aaaaaaaaaaaa";

    fd=open(FILE,O_RDONLY);
    if(fd<0)
    {
        printf("Failed to open the file");
        exit(1);
    }

    printf("Returned fd values = %d",fd);

    ret=read(fd,buf,10);
    if(ret<0)
    {
        printf("Failed to read data\n");
        exit(2);
    }
    
    buf[ret]='\0'; // if we dont put this
                /*after reading text from file, the eof is next line character, so printf prints the
                 text file and prints the remainings aaa in the buf, to remove this we put a null character at the end of the read characters */

    printf("Bytes read = %d \n",ret);
    printf("%s\n",buf);

    close(fd);
}

