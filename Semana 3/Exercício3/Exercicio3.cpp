#include <stdio.h>
#include <stdlib.h>

int ** criaMatriz(int m, int n);
void leiaMatriz(int **mat, int m, int n);
int somaMatriz(int **mat, int m, int n);
int* colunaMatriz(int ** mat, int m, int n, int ncoluna);
void liberaMatriz(int **mat, int nlinha);
void imprimeMatriz(int **mat, int m, int n);
void imprimeVetor (int *vet, int n);
void imprimeMenu();

int main() {
    int** matriz = NULL;
    int m = 0, n = 0;
    int op = -1;

    while(op != 5){
        imprimeMenu();
        printf("|=| Insira tua escolha:"); scanf("%d", &op);
        switch (op) {
            case 0:
                printf("|=| Criar nova matriz |==============================|\n");
                if(matriz != NULL){
                    printf("|=| Matriz ja foi inicializada, liberando ela\n");
                    liberaMatriz(matriz, m);
                    m = 0;
                    n = 0;
                }
                while(m <= 0){
                    printf("|=| Insira o numero de linhas:"); scanf("%d", &m);
                    if(m <= 0){
                        printf("|=| Valor invalido\n");
                    }
                }
                while(n <= 0){
                    printf("|=| Insira o numero de colunas:"); scanf("%d", &n);
                    if(m <= 0){
                        printf("|=| Valor invalido\n");
                    }
                }
                matriz = criaMatriz(m,n);
                if(matriz == NULL){
                    printf("|=| Um erro foi encontrado, tente novamente\n");
                }
                break;
            case 1:
                printf("|=| Realizar leitura dos elementos |=================|\n");
                if(matriz != NULL){
                    leiaMatriz(matriz, m, n);
                }else{
                    printf("|=| Crie uma matriz antes!\n");
                }
                break;
            case 2:
                printf("|=| Fornecer soma dos elementos |====================|\n");
                if(matriz != NULL){
                    printf("|=| Soma de [%d]x[%d] = %d\n", m, n, somaMatriz(matriz, m, n));
                }else{
                    printf("|=| Crie uma matriz antes!\n");
                }
                break;
            case 3:
                printf("|=| Imprimir coluna |================================|\n");
                if(matriz != NULL){
                    int sel = -1;
                    while(sel < 0 || sel > n){
                        printf("|=| Insira a coluna:"); scanf("%d", &sel);
                    }
                    int *vet = colunaMatriz(matriz,m,n,sel);
                    imprimeVetor(vet,n);
                }else{
                    printf("|=| Crie uma matriz antes!\n");
                }
                break;
            case 4:
                printf("|=| Imprimir matriz |================================|\n");
                if(matriz != NULL){
                    imprimeMatriz(matriz, m, n);
                }else{
                    printf("|=| Crie uma matriz antes!\n");
                }
                break;
            case 5:
                printf("|=| Saindo do programa!\n");
                break;
            default:
                printf("|=| Entrada invalida!");
                break;
        }

    }


    return 0;
}
void imprimeMenu(){
    printf("|==================[ Exercicio 03 ]==================|\n");
    printf("|=| [0] - Criar nova matriz |========================|\n");
    printf("|=| [1] - Realizar leitura dos elementos |===========|\n");
    printf("|=| [2] - Fornecer soma dos elementos |==============|\n");
    printf("|=| [3] - Imprimir coluna |==========================|\n");
    printf("|=| [4] - Imprimir matriz |==========================|\n");
    printf("|=| [5] - Sair |=====================================|\n");
    printf("|====================================================|\n");


}
int** criaMatriz(int m, int n){
    int** matriz;

    matriz = (int **)malloc(m*sizeof (int*));

    if(matriz == NULL){
        printf("|=| Erro! Ocorreu ume erro de alocamento");
        return NULL;
    }

    for(int i = 0; i < m; i++){
        matriz[i] = (int*) malloc(n*sizeof(int));
    }

    return matriz;
}
void leiaMatriz(int **mat, int m, int n){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            int k;
            printf("|=| [%d][%d]Insira o valor desejado =>",i,j); scanf("%d", &k);
            mat[i][j] = k;
        }
    }
}
int somaMatriz(int **mat, int m, int n){
    int acc = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            acc = acc + mat[i][j];
        }
    }
    return acc;
}
int* colunaMatriz(int **mat, int m, int n, int ncoluna){
    int *returnMat;
    returnMat = (int*) malloc(sizeof (int) * n);

    for(int i = 0; i < m; i++){
        if(i == ncoluna){
            for(int j = 0; j < n; j++){
                returnMat[j] = mat[ncoluna][j];
            }
        }
    }
    return returnMat;
}
void liberaMatriz(int **mat, int nlinha){
    for(int i = 0; i < nlinha; i++){
        free(mat[i]);
    }
    free(mat);
}
void imprimeMatriz(int **mat, int m, int n){

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n;j++){
            printf("[%d]", mat[i][j]);
        }
        printf("\n");
    }
}
void imprimeVetor(int *vet, int n){
    printf("|=| ");
    for(int j = 0; j < n; j++){
        //*(a + b) => *(b + a), logo em principio a[b] => b[a], aqui acabei querendo testar isso
        //Aparentemente é funcional, embora a IDE reclame.
        printf("[%d]", j[vet]);
    }
    printf("\n");
}