#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep and fork
#include <sys/wait.h>

int test (){
    return 1;
}

// fd is the file descriptor of the pipe
void wait_s(){
    int time = 0;
    printf("Je dodo %ds\n",time);
    sleep(time); 
}

void pere(pid_t id_son){
    int statu;
    //wait 1s and kill the son
    sleep(1);
    kill(id_son, SIGKILL);
    wait(&statu); //look how the son terminated his life
    if(WIFEXITED(statu)){ // test if his son has lived a normal life
        printf("je l'ai pas tué\n");
    }
    else{
        printf("je l'ai tué mais j'aurais pas du\n");
    }

}

// Fork create a new process that is the same as the father but in a different memory
int main(void)
{
    pid_t pid; // fork return value
    pid = fork();

    //verifie that the fork is well done
    if (pid == -1)
    {
        printf("fork gone wrong\n");
        return 1;
    }

    printf("Fork done\n");

    // fork return 0 in the son process
    if (pid == 0)
    {
        wait_s();
    }
    // fork return the id of the son in the father process
    else if (pid > 0)
    {
        pere(pid);
    }
    return(0);
}