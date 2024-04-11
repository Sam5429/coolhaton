#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void dady(pid_t id, int* fd){
    char buff;
    read(fd[0],&buff,1);
    close(fd[0]);
    close(fd[1]);
    printf("je t'ai entendu fils : %c\n",buff);
}

void son(int* fd){
    char buff = 'a';
    write(fd[1],&buff,sizeof(buff)); //write in the pipe
    // close the file descriptor of the pipe
    close(fd[0]);
    close(fd[1]);
    printf("je t'ai écrit dady\n");
}

int main(){
    pid_t id; // store the son id's
    int fd[2]; // [0] read only / [1] write only
    
    if(pipe(fd)==-1){
        perror("pipe failed\n");
        return -1;
    }
    printf("pipe done\n");

    id = fork();

    if(id==-1){
        perror("fork failed\n");
        return -1;
    }
    printf("fork done\n");

    if(id == 0){
        son(fd);
    }
    if(id > 0){
        dady(id,fd);
    }



    return 0;
}