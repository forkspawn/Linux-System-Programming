/* dup is different from open,as open creates a file object and dup just created an entry
 * in the fd table. and dup system call updates the cursor position */

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
void main()
{   
    
    int ret;
    char buf[20];
    int fd=open("text.txt",O_CREAT|O_RDWR,0660);
    if(fd<0)
    {
        printf("Open Error\n");
        exit(1);
    }
    int nfd=dup(fd);

    printf("fd= %d \n",fd);
    printf("nfd= %d \n",nfd);

    printf("Enter The String \n");
    scanf("%s",buf);
    write(fd,buf,strlen(buf));

    printf("Enter the string \n");
    scanf("%s",buf);
    write(nfd,buf,strlen(buf));

    close(nfd);
    ret=write(fd,buf,strlen(buf));
    printf("After closing nfd ret = %d\n",ret);
    close(fd);

    ret=write(fd,buf,strlen(buf));
    if(ret<0)
    {
        printf("Fail to perform write \n");
        exit(1);
    }
}
