#include"kernel/types.h"
#include"user/user.h"
#include"stddef.h"

int 
main(int argc, char *argv[])
{
    int ptoc_fd[2], ctop_fd[2];
    pipe(ptoc_fd);
    pipe(ctop_fd);
    char buff[8];
    if(fork() == 0)
    {
        read(ptoc_fd[0],buff,4);
        printf("%d: received %s\n", getpid(),buff);
        write(ctop_fd[1],"pong",strlen("pong"));    
    }
    else{
        write(ptoc_fd[1],"ping",strlen("ping"));
        wait(NULL);
        read(ctop_fd[0],buff,4);    
        printf("%d: received %s\n",getpid(),buff);
    }
    exit(0);
}
