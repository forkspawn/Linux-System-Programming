/* A condition variable allows signalling from one thred to other thrad, about changes in the state
   of a share variable. Conditon Variables help to dfine the sequence of thread execution, for eg:
   In case of producer and consumer application, first the prouducer thread runs, and then the proudcer thread
   signals the consumer thread for further execution.
 * A condition variable the thread waiting for shared resource will be made to sleep, and as soon
   as it gets signal fro other thread, the thread wakes up and executes(like accessing/modifyiing shared resource).
 * A condition variable is always used in conjunction with a mutex.
 * Condition variable can be allocated statically or dynamically
 * pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
 * The principal of condition variable is 'signal' and 'wait'. 
 * The 'signal' operation is a notification to one or more waitng signals threads that a share variable state has changed.
   The 'wait' operation is the method of blockng until such a notification is received from other thread.
 * 
 * int pthread_cond_signal(pthread_cond_t * cond)
 * int pthread_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
 * All return 0 on success, or a positive error number on error.
 * 
 * WORKING PRINCIPLE:
 * pthread_cond_wait
 * 1. The thread calling pthread_cond_wait unlocks mutex-M
 * 2. Blocks on the condition variable 'cond' to receive the signal from other thread
 * 3. As soon as it receives required signal, it further locks mutex-M.
 * Note: step1 and step2 is executed as a atomic operation.
 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t myConVar= PTHREAD_COND_INITIALIZER;
int doneFlag=0;
char buf[100];

//Producer Thread
void * threadA(void *p)
{
    printf("\nthreadA scheduled first\n");
    sleep(1);
    pthread_mutex_lock(&my_mutex);
    printf("\nthreadA: critical section executes always first\n");

    //proudcer will produce data here
    sprintf(buf,"This is data buffer");
    doneFlag=1;
    pthread_cond_signal(&myConVar);
    pthread_mutex_unlock(&my_mutex);
}

#if 1
// consumer thread
void *threadB(void *p)
{
    printf("\nthreadB scheduled first\n");
    pthread_mutex_lock(&my_mutex);
    if(doneFlag==0)
        pthread_cond_wait(&myConVar,&my_mutex);
    //consumer will consumer data here
    printf("threadB: signal received from threadA, this is always executed after threadA critical section %d\n",doneFlag);
    printf("\n The buffer received from the producer thread is %s\n",buf);
    pthread_mutex_unlock(&my_mutex);

}
#endif


int main(int argc, char** argv)
{
    srand(time(0));
    pthread_t pthreadA;
    pthread_create(&pthreadA,NULL,threadA,NULL);
    pthread_t pthreadB;
    pthread_create(&pthreadB,NULL,threadB,NULL);
    pthread_join(pthreadA,NULL);
    pthread_join(pthreadB,NULL);
    printf("\n Main thead is exiting now\n");
    return(EXIT_SUCCESS);
}















