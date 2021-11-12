/*
 *The pthread_join() function when called from main thread,
 waits for the specified thread to terminate.
 *If that thread has already terminated, pthread_join()
 returns immediately.
 *Retruns 0 on success, or a positive error number on eror
 *pthread_join is similar to waitpid()
 *The main use case of using pthread_join is that the main thread should
 wait for all threads it has created, and then only should terminate itself
 by the end.
 */

#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

#define MAX 100

static void *threadfunc(void *arg)
{
    char *s=(char *)arg;
    int count=0;
    printf("Thread: threadfunc started\n");
    for(count=0;count<MAX;count++);

    sleep(5);
    printf("\nThread: threadfunc exiting now\n");
    if(count<500)
    {
        return (void*) "count<500";
    }
    else
        return (void *) "count>500";
}

int main(int argc, char *argv[])
{
    pthread_t t1_id;
    void *res;
    int s;
    s=pthread_create(&t1_id,NULL,threadfunc,NULL);
    if(s!=0)
        perror("pthread_create error\n");
    printf("In Main thread\n");
#if 1
    s= pthread_join(t1_id,&res);
    if(s!=0)
        perror("pthread_join error\n");
    printf("Main thread: thread returned %s\n",(char*)res);
#endif

    printf("Main thread exiting now\n");
    pthread_exit(NULL);

}


