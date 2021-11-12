/* One of the main advantages of threads are that they can share information through global varibles
   i.e Data segment,heap segment
 * Programmer has to take care that multi-thread do not attempt to modify/read the same global variable
   at the same time.
 * Critical section is used to refer to a section of code that access a shared resource and whose execution
   should be atomic, else synchronization issues arise.
 * 
 * MUTEX: mutex is a type of lock(its data type is pthread_mutex_t) 
 * To avoid the problems that can occur when multiple threads try to access/modify the share variable
   we must use a mutex(short for mututal exclusion)
 * Mutex has two states: locked and unlocked
 * At any moment, at most one thread may hold the lock on a mutex, and hence only that thread can execute 
   the critical section. When a thread locks a mutex, it becomes owner of the mutex. Only the mutex owner can 
   unlock the mutex.
 * ALLOCATION: Statically or Dynamically at run time.
 * pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER
 * int pthread_mutex_lock(pthread_mutex_t *mutex);
 * int pthread_mutex_unlock(pthread_mutex_t *mutex);
 * Both return 0 on success, or a positive error number on error
 *
 * DEADLOCK: Someties a thread nees to simulataneously access two or more different shared resources,
   each of which is governed by a separate mutex.
 * Deadlock can also be caused, if a thread has already locked a mutex, and same thread is trying to 
   lock the same mutex again.
 * The simples way to avoid such deadlocks is to define mutex hierarchy, threads can lock the same set 
   of mutexes, they should always lock them in the same order.
 * Pthreads API provies two variants of the pthread_mutex_lock().
 * pthread_mutex_trylock() and pthread_mutex_timedlock().
 * pthread_mutex_trylock() is the same as pthread_mutex_lock, except that if the mutex is currently locked.
 * pthread_mutex_trylock() fails, returning the error EBUSY.
 */

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

static int glob=0;
static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

#define MUTEX 0 //put 1 to lock the global variable access 
#define NOMUTEX 1 // put 1 to see how the global variable changes with each execution

static void *threadFunc1(void *arg)
{
    int loc,j,ret;
    int loop=10000;
    printf("\n threadFunc1 exeucted first\n");

#if MUTEX
    ret=pthread_mutex_lock(&mtx);
    if(ret!=0)
        perror("pthread_mutex_lock");
    for(j=0;j<loop;j++)
    {
        loc=glob;
        loc++;
        glob=loc;

    }
    ret=pthread_mutex_unlock(&mtx);
    if(ret!=0)
        perror("pthread_mutex_unlock");
#endif

#if NOMUTEX
    for(j=0;j<loop;j++)
    {
        loc=glob;
        loc++;
        glob=loc;
    }
#endif
    return NULL;
}

static void *threadFunc2(void *arg)
{
    int loop=10000;
    int loc,j,ret;
    printf("\n threadFunc2 executed second\n");

#if MUTEX
    ret=pthread_mutex_lock(&mtx);
    if(ret!=0)
        perror("pthread_mutex_lock");
    for(j=0;j<loop;j++)
    {
        loc=glob;
        loc++;
        glob=loc;

    }
    ret=pthread_mutex_unlock(&mtx);
    if(ret!=0)
        perror("pthread_mutex_unlock");
#endif


#if NOMUTEX
    for(j=0;j<loop;j++)
    {
        loc=glob;
        loc++;
        glob=loc;
    }
#endif
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1,t2;
    int loops,s;
    s=pthread_create(&t1,NULL,threadFunc1,NULL);
    if(s!=0)
        perror("pthread_create");
    
    s=pthread_create(&t2,NULL,threadFunc2,NULL);
    if(s!=0)
        perror("pthread_create");
    
    s=pthread_join(t1,NULL);
    if(s!=0)
        perror("pthread_join of t1");
    
    s=pthread_join(t2,NULL);
    if(s!=0)
        perror("pthread_join of t2");

    printf("glob = %d\n",glob);
    exit(0);

}












