/*  POSIX Semaphores allows processed and thread to synchronize access to shared resources.
 *  Semaphores are used to execute the critical action(resouce share by different process/Thread) in
    an atomic manner. 
 *  Named semaphores- This semaphore has a name as specified in sem_open().
    /dev/shm
 *  Unnamed semaphores: This type of semaphore doesnt have a name, ir resides at an location in memory.
 *  Name Semaphores: sem_open,sem_post, sem_wait, sem_getvalue, sem_close, sem_unlink.
 *
 *  sem_t *sem_open(const char *name, int oflag);
 *  sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
 *
 *  ----------------->Link the program with -lpthread
 *
 *  sem_open: Function opens or creates a semaphore, initializes the semaphore and returns a handle
    for use in later calls.
    Value- is an usigned integer that specifies the initial value to be assigned to the new semaphore.
    When an child is created via fork(). it inherits references to all of the names semaphores that are
    open in its parent. After the fork(), the parent and child can use these semaphores to synchronize their actions.

 *  sem_close: Removes the calling process association with a semaphore that it opened previously.
    returns 0 on success or -1 on error.

 *  sem_unlink: fucntion removes a semaphore name and marks the semaphore for deletion when all process have closed it.
    returns 0 on succes,or -1 on error.
 *  
 *  Semaphores Operations:
 *  Posix semaphore is an integer that the system never allows to go below 0.
 *  The sem_post() and sem_wait() fucntions increment and decrement a semaphre value by exactly one.
 *  sem_post and sem_wait functions respectively increment and decrement a semaphore value.
 *
 *  If the semaphore currently has a value greater than 0, sem_wait returns immediately. If the value
    of the semaphore is currently 0, sem_wait blocks until the semaphore is decremented and sem_wait returns.
 *
 *  int sem_getvalue(sem_t *sem, int *sval): function retrives a semaphores current value.
 *  returns 0 on success, or -1 on error.
 *
 *  NOTE: Experiment with different processes by taking semaphore in it 
 */


#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<semaphore.h>
#include<unistd.h>

int main()
{
    int flags,sval;
    unsigned int value;
    sem_t *sem;

    sem = sem_open("/sem1",O_CREAT|O_RDWR,0660,1);

    if(sem==SEM_FAILED)
    {
        perror("sem_open_error:\n");
        return -1;
    }
    else
        printf("\nsem_open success\n");

    sem_getvalue(sem,&sval);
    printf("\nbefore sem_wait semaphore value = %d\n",sval);

    sem_wait(sem); //decrease the value
    sem_getvalue(sem,&sval);
    printf("\nAfter sem_wait semaphore value = %d",sval);
    
    printf("\nProcess1: executing critical section");
    sleep(10);
    sem_post(sem); //this increments the semaphore valu
    printf("\nCritical section executed\n");
    sem_getvalue(sem,&sval);
    printf("\n After sem_post semaphore value = %d\n",sval);


}































