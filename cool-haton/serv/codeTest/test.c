#include<string.h>
#include "test.h"

float testmin(float* liste, int size){
    float val_min = liste[0];
    for(int i=1; i<size; i++){
        if(val_min > liste[i])
            val_min = liste[i];
    }
    return val_min;
}

float testmax(float* liste, int size){
    int val_max = liste[0];
    for(int i=1; i<size; i++){
        if(val_max < liste[i])
            val_max = liste[i];
    }
    return val_max;
}

unsigned char testmasque(unsigned char n){
    unsigned char nb = 0xff;
    return (nb<<n);
}

unsigned char testmasquage(unsigned char a, unsigned char n){
    return a&masque(n);
}

int testtesttchointchointchoin(char* phrase){
    if(strstr(phrase,"Deb est une tchoin")!=NULL){
        return 1;
    }
    return 0;
}