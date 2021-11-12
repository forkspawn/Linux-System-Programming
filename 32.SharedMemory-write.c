/*  Posix shared memory allows to share a mapped memory between unrealted processes.
 *  Entries are present in: /dev/shm
 *  Shared memory the fastest ipc mechanism, as no extra kernel data structures are involved.
    In other IPC, if data needs to be sent from say process 1 to process 2, then data from 
    process 1 user space to kernel space needs to be copied, then again from kernel space to user space
    of process 2 needs to be performed.
 *  To use POSIX shared memory object, we perform the following steps:
 *  1. Use the shm_open() function to open an object with a specified name.
       The shm_open() function is analogous to the open() system call.
       It either creates a new shared memory object or opens an existing one.
       shm_open() returns a file descriptor referring to the share memory.
       NOTE: The shared memory created newly is of lenght '0' bytes. 
 *  2. Define the length of shared memory.
 *  3. File descriptor obtained in the previous step is referenced in nmap()
       This maps the shared memory object into the process virtual address space.
       NOTE: Any read/write to process virtual memory, will be actually read/written from 
       shared memory(part of physical RAM memory).
 *  
 *  int shm_open(const char *name,int oflag, mode_t mode)
 *  returns file descriptor on success, or -1 on error.
 *
 *  int ftruncate(int fd, off_t length)
 *  fd is the file descriptor obtained from shm_open() and length is the requried length in bytes
 *  of shared memory.
 *
 *  void *nmap(void *addr, size_t lenght,int prot,int flags,int fd,off_t offset)
 *  
 *  addr: address of process virtual memory to which the shared memory is mapped, if 'addr' is NULL,
    then the kernel chooses the address at which to create the mapping.
 *  length: length of the created shared memory
 *  prot: describes the memory protection of mapping(PROT_READ for readand PROT_WRITE for write)
 *  flags: for shared memory flags use value 'MAP_SHARED' describing that the memory can be shared,
    i.e updates to this mapped memory is visible among process.
 *  fd: file descriptor from shm_opne()
 *  
 *  Returns: on success - The virtual memory of process, to which the shared memory is mapped.
 *           on error - The value MAP_FAILED(that is (void*)-1) is returned and errno is set
 *           to indicate the cause of the error.
 *----------->compile with -lrt
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    size_t len;
    char *addr;

    fd=shm_open("/shm_1", O_CREAT | O_RDWR,0660);
    if(fd==-1)
            {
                 printf("Error creating shm\n");
                 perror("shm_open_error:\n");
                 exit(-1);
              
            }
    printf("\n shm open success\n");
    len=strlen(argv[1]);
    if(ftruncate(fd,len)==-1)
    {
        perror("shm_open_error:\n");
        exit(-1);
    }

    printf("\nResized to %ld bytes\n",(long)len);
    addr=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(addr==MAP_FAILED)
    {
        perror("nmap_error:\n");
        exit(-1);
    }
    if(close(fd)==-1)
        perror("close");

    memcpy(addr,argv[1],len);
    exit(0);

}






