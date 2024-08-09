#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[]){
    int p2c[5];
    int c2p[5];
    if(pipe(p2c) < 0){
        printf("pipe");
        exit(-1);
    }
    if(pipe(c2p) < 0){
        printf("pipe");
        exit(-1);
    }//创建失败
    int pid = fork();//判断子父进程
    if(pid == 0){
        // child
        char buf[10];
        read(p2c[0], buf, 10);
        printf("%d: received ping\n", getpid());
        write(c2p[1], "ping", strlen("ping"));
    }else if(pid > 0){
        // parent
        write(p2c[1], "pong", strlen("pong"));
        char buf[10];
        read(c2p[0], buf, 10);
        printf("%d: received pong\n", getpid());
    }
    close(p2c[0]);close(p2c[1]);
    close(c2p[0]);close(c2p[1]);
    exit(0);
}