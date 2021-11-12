#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

static void signal_handler(int signo)
{
    if(signo=SIGUSR1)
        printf("Parent: Caught SIGUSR1 in parent\n");
}

int main()
{
    pid_t cpid;
    int status=0;
    int num=5;
    cpid = fork();
    if(cpid==-1)
        exit(-1);
    if(cpid==0)
    {
        printf("Child: Before Exec\n");
        execl("./Signal","arg1","arg2",NULL);
        printf("This statement will not be printed\n");
    }
    else
    {
        if(signal(SIGUSR1,signal_handler)==SIG_ERR)
        {
            fprintf(stderr,"Cannot Handle SIGUSR1\n");
            exit(-1);
        }
        printf("\n Parent: Parent executing before wait(), child process created by parent is= %d\n",cpid);
        sleep(2);
        kill(cpid,SIGUSR2);
        cpid=wait(&status);
        printf("\nParent: wait() in parent done pid is = %d",getpid());
        printf("\nParent: cpid returned is = %d\n",cpid);
        printf("\nParent: status is =%d \n",status);
    }
    return 0;
}
