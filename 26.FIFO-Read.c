#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int fd;
    char arr[60];

    char *myfifo="/tmp/myfifo";

    fd=open(myfifo,O_RDONLY);

    while(1)
    {
        read(fd,arr,60);
        printf("user1: %s\n",arr);
    }
    close(fd);
    return 0;
}





