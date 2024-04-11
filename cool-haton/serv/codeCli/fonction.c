#include <stdio.h>
#include "fonction.h"

int min(int* liste, int taille_liste){
    int val_min = liste[0];
    for(int i=1; i<taille_liste; i++){
        if(val_min > liste[i])
            val_min = liste[i];
    }
    return val_min;
}

int max(int* liste, int taille_liste){
    while(1){
        continue;
    }
    return 1;
}