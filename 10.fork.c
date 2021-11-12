#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	int stat,i=0;
	printf("Executing\n");
	int ret;
	ret=fork();
	if(ret==-1)
		printf("Failed\n");
	if(ret)
	{
		printf("In parent\n");
//		wait(&stat);
	}
	else
	{
//		while(1)
		{
			printf("In Child\n");
			sleep(1);
			wait(&stat);
			printf("After wait\n");
		}
	}
	printf("Exiting now\n");

}






