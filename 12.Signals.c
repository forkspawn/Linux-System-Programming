#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

static void signal_handler(int signo)
{
    printf("Signal number is = %d \n",signo);
    if(signo==SIGINT)
        printf("Caught Sigint\n");
    else if(signo==SIGTERM)
        printf("Caught Sigterm!\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    printf("\n Process ID is = %d\n",getpid());
        if(signal(SIGINT,signal_handler)==SIG_ERR)
        {
            fprintf(stderr,"Cannot handle SIGHUP!\n");
            exit(-1);
        }
        if(signal(SIGTERM,signal_handler)==SIG_ERR)
        {
            fprintf(stderr,"Cannot handle Sigterm\n");
            exit(-1);
        }
        while(1)
        {
            printf("In while with pid = %d\n",getpid());
            sleep(2);
        }
}
