#include<fcntl.h>
#include<limits.h>
#include<mqueue.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>

int main(int argc, char **argv)
{ 
    mqd_t queue;
    struct mq_attr attrs;
    char *msg_ptr;
    ssize_t recvd;
    size_t t;

    if(argc<2)
    {
        fprintf(stderr,"Usage: %s <Quename> <message>\n",argv[0]);
        return 1;
    }

    queue=mq_open(argv[1],O_RDONLY|O_CREAT,S_IRUSR|S_IWUSR,NULL);
    if(queue == (mqd_t)-1)
    {
        perror("mq_open_error");
        return 1;
    }

    if(mq_getattr(queue,&attrs)==-1)
    {
        perror("mq_getattr_error");
        mq_close(queue);
        return -1;
    }

    msg_ptr=calloc(1,attrs.mq_msgsize);
    if(msg_ptr==NULL)
    {
        perror("calloc for msg_ptr\n");
        mq_close(queue);
        return 1;
    }


    recvd=mq_receive(queue, msg_ptr, attrs.mq_msgsize,NULL);
    if(recvd==-1)
    {
        perror("mq_receive");
        return -1;
    }

    printf("\n Received message in msg queue is %s",msg_ptr);
}
