/* By default a thread is joinable, this means when it terminates, another
   can obtain its return value using pthread_join()
 * If a joinable thread is not joined by calling pthread_join, the the 
   terminated thread becomes a zombie thread, consuiming system memory resource
 * pthread_detach()- The system automatically cleans up terminated thread, no need
   of calling pthread_join
 * int pthread_detach(pthread_t thread);
   Returns 0 on success, or a positive error number on error
 
 * int pthread_cancel(pthread_t thread);
   Retruns 0 on success, or a positive error number on error
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define MAX 100
#define Detach 0 //In detach after going to threadFunc the control stays in threadfucn until it executes completely
#define Cancel 1 //In cancel after going to threadFunc the control comes back to the main thread


static void *threadFunc(void *arg)
{
    char *s=(char *)arg;
    int count=0;
    printf("Thread: threadFunc started\n");

#if Detach
    pthread_detach(pthread_self());
    for(count=0;count<MAX;count++);
#endif

#if Cancel
    while(1)
    {
        sleep(1);
        printf("\nthreadFunc: executing loop\n");
    }
          sleep(5);
#endif  
printf("\nThread: threadFunc exiting now\n");

}

int main(int argc, char *argv[])
{
    pthread_t t1_id;
    void *res;
    int s,count;
    s=pthread_create(&t1_id,NULL,threadFunc,NULL);
    printf("Main thread exiting now\n");
    if(s!=0)
        perror("pthread_create error\n");
#if Detach
    for(count=0;count<MAX;count++)
    {
        printf("Printing count = %d ",count);
        sleep(1);
    }
    pthread_exit(NULL);
#endif 

#if Cancel
    for(count=0;count<10;count++)
    {
        sleep(1);
        printf("\n Main thread count value = %d",count);
    }
    pthread_cancel(t1_id);
    printf("Main thread exiting now\n");
    pthread_exit(NULL);
#endif
}
