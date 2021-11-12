/*  Unnamed semaphores are also know as memor based semaphores, which are variable of type sem_t
    are stored in memory allocated by application.
 *  The semaphor is made available to the processes or threads that use it by placing it in an area of
    memory thay they share.
 *  NOTE: Named semaphore was present in file system similar to regular file, where as a un-named semaphore
    does not exist, rather on volatile memory like RAM.
 *  Same opreations are use as Named semaphore.
 *  The sem_init(): Function initialized a semaphor and informs the system of whether the semaphore will be
    wil be shared between processes or between the threads of a single process.
 *  The sem_destroy(sem): function destroys a semaphore
 *  sem_init() and sem_destroy() cant be used on names semaphores.
 *
 *  int sem_init(sem_t * sem, int pshared,unsigned int value)
 *  returns 0 on success or -1 on error.
 *  The pshared argument indicates whether the semaphore is to be shared between threads or between process.
    If pshared is 0, then the semaphore is to be shared between the threads of the calling process.
    If pshared is nonzero, then the semaphore is to be shared between processes.
    value: It is the number of threads or processes that can enter the critical section.
 *   
 *  int sem_destroy(sem_t *sem)
 *  returns 0 on succes or -1 on error.
 */

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>

static int glob=0;
sem_t sem;

static void *threadFunc(void *arg)
{
    int loc,j,ret;
    int loop=10000;

    printf("\nthreadFunc %s running\n",(char*)arg);
    ret=sem_wait(&sem);

    printf("\nsemaphore availed in %s\n",(char*)arg);
    if(ret!=0)
        perror("semaphore with error:");
        
     for(j=0;j<loop;j++)
    {
        loc=glob;
        loc++;
        glob=loc;

    }
    ret=sem_post(&sem);

    if(ret!=0)
        perror("Semaphore post error:");

    printf("\nthreadFunc end for %s\n",(char*)arg);
    return NULL;

}

int main(int argc, char *argv[])
{
    pthread_t t1,t2,t3;
    int looops,s;
    s=pthread_create(&t1,NULL,threadFunc,"thr1");
    if(s!=0)
        perror("pthread_create_error:");
    s=pthread_create(&t2,NULL,threadFunc,"thr2");
    if(s!=0)
        perror("pthread_create_error:");
    s=pthread_create(&t3,NULL,threadFunc,"thr3");
    if(s!=0)
        perror("pthread_create_error:");

    if(sem_init(&sem,0,1)==-1)
    {
        perror("Error During sem_init\n");
        exit(1);
    }

    s=pthread_join(t1,NULL);
    if(s!=0)
        perror("pthread_create_error:");

    s=pthread_join(t2,NULL);
    if(s!=0)
        perror("pthread_create_error:");

    s=pthread_join(t3,NULL);
    if(s!=0)
        perror("pthread_create_error:");

    sem_destroy(&sem);
    printf("\nValue of glob after both thread running is %d\n",glob);
    exit(0);


}







