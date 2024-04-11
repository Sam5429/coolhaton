/***********************************************************************************************
        Fichier main ou sont effectué tout les test qui vont figurer dans rapport
************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "codeTest/test.h"
#include "codeCli/fonction.h"

void error(char* msg){
    perror(msg);
    exit(-1);
}

int main(){

    // test max
    alarm(0.2);
    
    // test min


    // do son code (try the function)
    if(pid == 0){
        if(min(test, 2)==test_min(test, 2)){
            printf("test min réussi\n");
        }
    }
    // do dady code (kill son if to long)
    else if(pid > 0){
        int statu;
        sleep(0.2);
        kill(pid, SIGKILL);
        wait(&statu);
        if(WIFSIGNALED(statu)){
            printf("test min failed\n");
        }
    }

    pid = fork();
    if(pid == -1){
        error("fork failed\n");
    }

    if(pid == 0){
        if(max(test, 2)==test_max(test, 2)){
            printf("test max réussi\n");
        }
    }
    else if(pid > 0){
        int statu;
        sleep(0.2);
        kill(pid, SIGKILL);
        wait(&statu);
        if(WIFSIGNALED(statu)){
            printf("test max failed\n");
        }
    }
    return 0;
}