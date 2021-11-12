#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

static void signal_handler(int signo)
{
    if(signo==SIGUSR2)
        printf("Child: Caught SIGUSR2 in child\n");
}

int main(int argc, char *argv[])
{
    int i=0;
    printf("Child: Iam new process called by execl()\n");
    printf("Child: New program id = %d",getpid());

    if(signal(SIGUSR2,signal_handler)==SIG_ERR)
    {
        fprintf(stderr,"Cannot handle SIGUSR2\n");
        exit(-1);
    }

    for(i=0;i<argc;i++)
    {
        printf("\nChild: argc[%d] = %s \n",i,argv[i]);
    }
       
    sleep(2);
    printf("\nChild sending sigusr1 to parent\n");
    kill(getppid(),SIGUSR1); //this will send sigusr1 signal to kill the parent, which is caught by the parent and dispalced on the screen
    sleep(3);
    printf("Child: Exiting\n");
    return 0;

}
