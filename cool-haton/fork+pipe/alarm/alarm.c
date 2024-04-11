#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void fctnull(int a){
    a = a + 5;
}

void fctvrmnull(int a){
    while(1){
        a += 1;
    }
}

int main(){
    double temps = alarm(0.2);
    printf("le truc va mourir dans %lfs\n",temps);
    temps = alarm(0);
    printf("enft non\n");
    temps = alarm(0.2);
    fctvrmnull(5);
    return 0;
}