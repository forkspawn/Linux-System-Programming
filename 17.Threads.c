#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

static void *threadFunc(void *arg)
{

	char *str =(char *) arg;
	printf("\n Threadfunc: arguments passed to thread are %s pid = %d \n",str,getpid());
	(void)sleep(20);
	printf("\n threadFunc: exiting now \n");
	return(0);

}

int main(int argc, char *argv[])
{
	pthread_t t1;
	int s;
	
	s=pthread_create(&t1,NULL,threadFunc,"Hello World");
	if(s!=0)
		perror("Thread create error");
	
	printf("\n Main thread: message from main(), pid =  %d \n",getpid());
	
//	sleep(5);
	printf("\n Main thread: exiting now \n");
	//	exit(0);
	pthread_exit(0);

}
 //execute with gcc thread.c -lpthread
