#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

static void *threadFunc(void *arg)
{
    char *s=(char *)arg;
    printf("\nthreadFunc: %sprinted in thread pid = %d\n",s,getpid());
    (void)sleep(5);
    printf("\nthreadFunc: exiting now\n");
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t t1;
    void *res;
    int s;

    s=pthread_create(&t1,NULL,threadFunc,"Hello Thread\n");
    if(s!=0)
        perror("Thread Create eror\n");
    printf("Main thread: Message from main(), pid = %d",getpid());
    sleep(3);
    printf("\nMain Thread: after sleep 3 sec\n");
   // exit(0); //is you use it will exit the main thread without waiting for the thread which its created for its execution
    pthread_exit(0); //using this will wait for the thread to finish its execution after, main function completed its execution
}
