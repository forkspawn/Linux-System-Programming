/* MessageQueue are used to send messages between processes. Unlike Pipes and Fifo which are byte oriented
   IPC, where as MessageQueue is message oriented IPC.
 * Readers and writers communicated each other in units of packages. POSIX message queues permit each message
   to be assigned a priority. Priority allows high-priority messages to be queued ahead of low-priority messages.
 * MessageQueue: Entry in File system "/dev/mqueue"
 * MessageQueue Calls: mq_open(), mq_close(), mq_unlink(), mq_send(),mq_receive(), mq_setattr(), mq_getattr()
 * mq_open: Function creates a new message queue or opens an existing queue, returning a message queue descriptor
            for use in later calls.
 * mq_receive: function reads a message from a queue.
 * mq_send: function writes a message to a queue.
 * mq_close: function closes a message queue that the process previously opened.
 * mq_unlink: function removes a message queue name and marks the queue for deletion when all processes 
              have closed it.
 *
 * mqd_t mq_open(const char *name, int offlag)
 * mqd_t mq_open(const char *name, int offlag, mode_t mode, struct mq_attr *attr);
 * Returns a message queue descriptor on success or mqd_t -1 on error.
 * Note: The name should always start with '/'
 * Eg: /my_queue
 *
 * strctu mq_attr
 * {
 *      long mq_flags;
 *      long mq_maxmsg;
 *      long mq_msgsize;
 *      long mq_curmsgs: //Number of messages currently in queue
 * }
 *  
 * int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
 * returns 0 on success or -1 on error
 *
 * ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
 * returns number of bytes in received message on success or -1 on error.
 * ----------use -lrt as a flag to compile eg: gcc filename.c -lrt-----------
 */

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
    size_t msg_len;

    if(argc<3)
    {
        fprintf(stderr,"Usage: %s <Quename> <message>\n",argv[0]);
        return 1;
    }

    queue=mq_open(argv[1],O_WRONLY|O_CREAT, 0660,NULL);
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

    printf("\n Message queue mg_maxmasg = %d, mq_msgsize is = %d\n",(int)attrs.mq_maxmsg,(int)attrs.mq_msgsize);

    msg_len = strlen(argv[2]);
    if((long)msg_len>attrs.mq_msgsize)
    {
        fprintf(stderr,"Your message is too long for the queue\n");
        mq_close(queue);
        return -1;
    }

    if(mq_send(queue,argv[2],strlen(argv[2]),0)==-1)
    {
        perror("mq_send");
        mq_close(queue);
        return -1;
    }
    return 0;


}





