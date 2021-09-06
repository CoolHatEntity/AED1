#include <stdio.h>
void atualizaChar(char *ponteiro, char novoChar) {
    *ponteiro = novoChar;
}
void atualizaInt(int *ponteiro, int novoInt){
    *ponteiro = novoInt;
}

void atuaizaFloat(float *ponteiro, float novoFloat){
    *ponteiro = novoFloat;
}

int main() {
    char c =  'a';
    char *pont_char = &c;

    int i = 3;
    int *pont_int = &i;

    float f = 3.14;
    float *pont_real = &f;
    
    printf("Antes => %d", i); atualizaInt(pont_int, 10); printf("/ Depois => %d\n", i);
    printf("Antes => %c", c); atualizaChar(pont_char, 'b'); printf("/ Depois => %c\n", c);
    printf("Antes => %f", f); atuaizaFloat(pont_real, 6.9); printf("/ Depois => %f\n", f);

    return 0;
}
