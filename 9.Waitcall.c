#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>

void main()
{
    int i=1;
    int val,pid,status,num;
    int *ptr=NULL;
    pid=fork();
    if(pid>0)
    {
        printf("Parent process is under blocking\n");
        num=wait(&status);
        printf("return wait -- %d\n",num);
        printf("status -- %d\n",status);

        if(WIFEXITED(status))
            printf("if parent %d\n",WEXITSTATUS(status));
        else
            printf("Else parent %d\n",WEXITSTATUS(status));
        if(WIFSIGNALED(status))
            printf("sig-parent %d\n",WTERMSIG(status));
        else
            printf("sig parent %d \n",WTERMSIG(status));
        printf("parent is terminated");
    }

    else
    {
        printf("new child process is created..\n");
        while(i)
        {
            
            printf("In child process with pid - %d\n",getpid()); //if you want to see normal termination of status,
                                                                //remove while and let it exit and convert it into status 
            sleep(3);
        }
        printf("Child process is terminated\n");
        exit(1);
    }
}
