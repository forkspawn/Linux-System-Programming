#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

void main(int argc, char *argv[])
{
    int fd=0,fd1=0,ret,ret1;
    char buf[10];
    if(argc!=3)
    {	
    printf("Enter Source Destination File Names\n ");
    printf("Invalind Input \n");
    exit(0);
    }

    fd=open(argv[1],O_RDWR); //read
    fd1=open(argv[2],O_RDWR); //write

    if(fd<0)
    {
        printf("Failed to open the file \n");
        exit(1);
    }
    printf("Returned fd value = %d \n",fd);

    if(fd1<0)
    {
        printf("Failed to open the file \n");
        exit(1);

    }
        
   while((ret=read(fd,buf,10))!=0) //cat operation to read to the end of the file
   {
        if(ret<0)
        {
            printf("Failed to read data from file\n");
            exit(2);
        }
     ret1=write(fd1,buf,10);
     if(ret1<0)
     {
        printf("Write has done\n");
        exit(3);
     }
  //   buf[ret]='\0'; //to get printed on nicely
  //   printf("%s\n",buf);
}
    close(fd);
    close(fd1);

}
