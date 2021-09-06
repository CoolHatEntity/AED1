#include <stdio.h>
void inicializaMatriz(float* c , float k){
    for(int i =  0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            *(c + i*3 + j) = k;
        }
    }
}

void imprimeMatriz(float* c){
    for(int i =  0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("[%f]", *(c + i*3 + j));
        }
        printf("\n");
    }
}

int main() {
    float c[3][3];
    inicializaMatriz(c[0], 3);
    imprimeMatriz(c[0]);
    return 0;
}
