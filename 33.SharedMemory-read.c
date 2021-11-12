#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
    int fd;
    char *addr;
    struct stat len;

    fd=shm_open("/shm_1", O_RDONLY,0);
    if(fd==-1)
    {
        printf("Error creating shm\n");
        perror("shm_open_error:\n");
        exit(-1);
    }

    fstat(fd,&len);
    addr=mmap(NULL,len.st_size,PROT_READ,MAP_SHARED,fd,0);
    if(addr==MAP_FAILED)
    {
        perror("nmap_error:\n");
        exit(-1);
    }
    printf("\nRead data from shared memory - %s\n",addr);
    exit(0);

}

