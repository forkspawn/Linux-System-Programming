#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<semaphore.h>
#include<unistd.h>

int main()
{
    int ret,sval;
    unsigned int value;
    sem_t *sem;

    sem = sem_open("/sem1",O_RDWR);

    if(sem==SEM_FAILED)
    {
        perror("sem_open_error:\n");
        return -1;
    }
    else
        printf("\nsem_open success\n");

   // sem_post(sem);
    sem_getvalue(sem,&sval);
    printf("\nbefore sem_wait semaphore value = %d\n",sval);

    ret= sem_wait(sem);
    
    printf("\nProcess2: executing critical section");
    sleep(10);
    printf("\nret = %d\n",ret);
    printf("\n process 2 semaphore value is = %d\n",sval);
    sem_post(sem);

    printf("\nProcess 2 executed critical section\n");
//    sem_unlink("/sem1");


}
