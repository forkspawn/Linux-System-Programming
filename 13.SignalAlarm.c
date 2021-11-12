#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void display_message(int s)
{
    printf("Generated Sigalarm\n");
    //signal(SIGALARM,SIG_IGN);
    //signal(SIGALARM,SIG_DFL);

    alarm(2); // without this statement display_message only executes for one time
}

int main(void)
{
    signal(SIGALRM,display_message);
    alarm(2); //this sends a SIGALARM every 2 seconds to signal which then executes display_message
    while(1)
    {
        
    }
}
