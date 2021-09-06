#include <stdio.h>

void inicializaMatriz(float* c){
    float k = 1;
    for(int i =  0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            *(c + i*3 + j) = k;
            k++;
        }
    }
}

void imprimeMatriz(float* c){
    for(int i =  0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%f -> [%p]", *(c + i*3 + j),&*(c + i*3 + j));
        }
        printf("\n");
    }
}

int main() {
    float c[3][3];
    inicializaMatriz(c[0]);
    imprimeMatriz(c[0]);
    return 0;
}
