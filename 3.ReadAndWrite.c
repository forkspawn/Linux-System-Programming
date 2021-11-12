#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

#define FILE "text.txt"
#define FILE1 "text1.txt"
void main()
{
    int fd=0,fd1=0,ret,ret1;
    char buf[10];

    fd=open(FILE,O_RDWR);
    fd1=open(FILE1,O_RDWR);

    if(fd<0)
    {
        printf("Failed to open the file \n");
        exit(1);
    }
    printf("Returned fd value = %d \n",fd);

   while((ret=read(fd,buf,1))!=0) //cat operation to read to the end of the file
   {
        if(ret<0)
        {
            printf("Failed to read data from file\n");
            exit(2);
        }
     ret1=write(fd1,buf,1);
    // printf("%d \n",ret1);
     buf[ret]='\0';
     printf("%s\n",buf);
}
    close(fd);
    close(fd1);

}
