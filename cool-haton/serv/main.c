/***********************************************************************************************
        Fichier main ou sont effectué tout les test qui vont figurer dans rapport
************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>
#include "codeTest/test.h"
#include "codeCli/fonction.h"

FILE* rapport;
float tailleZizi[6] = {6.5, 10, 15, 20, 30, 100};

void error(char* msg){
    perror(msg);
    exit(-1);
}

/************************************************************************************************
                            Test de fonction du client : 
                                return 1 si ça fonctionne 
                                return 0 sinon
*************************************************************************************************/
int testMin(void){
    if(min(tailleZizi, sizeof(tailleZizi))==6.5){
        return 1;
    }
    return 0;
}

int testMax(void){
    if(max(tailleZizi, sizeof(tailleZizi))==100){
        return 1;
    }
    return 0;
}

int testFacto(void){
    if(factoriel(4)==24 && factoriel(7)==5040 && factoriel(10)==3628800){
        return 1;
    }
    return 0;
}

int testGolmon(void){
    if(strcmp("roman",golmon())==0){
        return 1;
    }
    return 0;
}

int testTchointchointchoin(void){
    char debTchoin[] = "Deb est une tchoin";
    char debPasTchoin[] = "Deb n'est pas une tchoin";
    if(tchointchointchoin(debTchoin)){
        if(!tchointchointchoin(debPasTchoin)){
            return 1;
        }
    }
    return 0;
}

int testMasque(void){
    if(masque(0)==255 && masque(8)==0 && masque(4)==240){
        return 1;
    }
    return 0;
}

int testMasquage(void){
    if(masquage(16,0)==16 && masquage(1,7)==0){
        return 1;
    }
    return 0;
}

void handle_alarm(int sig){
    fputs("time out\n", rapport);
    exit(0);
}

void testfct(int (*fct)(void), char* nomExo){
    signal(SIGALRM,handle_alarm);
    fputs(nomExo, rapport);
    if(fct()==1){
        fputs("passed\n", rapport);
    }
    else{
        fputs("failed\n", rapport);
    }
}

int main(){
    // rapport
    rapport = fopen("rapport","w");
    if(rapport==NULL)
        error("ERROR opening file\n");
    fputs("Rapport\nIl y a 5 exo si il ne sont pas tous afficher et que vous avez eu un time out alors c'est normale sinon recommencer\n\n", rapport);
    
    // set the time for the timer
    struct itimerval timer; // struc for the setitimer fct
    timer.it_value.tv_usec = 500000; // 0.5 secondes

    //test de la fonction min
    setitimer(ITIMER_REAL, &timer, NULL);
    testfct(testMin,"min - ");
    alarm(0);

    //test de la fonction max
    setitimer(ITIMER_REAL, &timer, NULL);
    testfct(testMax,"max - ");
    alarm(0);

    //test de la fonction factoriel
    setitimer(ITIMER_REAL, &timer, NULL);
    testfct(testFacto,"factoriel - ");
    alarm(0);

    //test de la fonction golmon
    setitimer(ITIMER_REAL, &timer, NULL);
    testfct(testGolmon,"golmon - ");
    alarm(0);

    //test de la fonction tchointchointchoin
    setitimer(ITIMER_REAL, &timer, NULL);
    testfct(testTchointchointchoin,"tchointchointchoin - ");
    alarm(0);

    //test de la fonction masque
    setitimer(ITIMER_REAL, &timer, NULL);
    testfct(testMasque,"masque - ");
    alarm(0);

    //test de la fonction masquage
    setitimer(ITIMER_REAL, &timer, NULL);
    testfct(testMasquage,"masquage - ");
    alarm(0);

    return 0;
}