#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[32];
    int idade;
}Pessoa;

typedef struct{
    Pessoa *pessoa;
    struct TipoFila *proximo;
}TipoFila;

typedef struct{
    TipoFila *primeiro;
    TipoFila *ultimo;
}Fila;

Pessoa* criaPessoa();
Fila *RESET(Fila *fila);
void PUSH(Fila *fila, Pessoa *pessoa);
int POP(Fila *fila);
void imprimeFila(Fila *fila);

int main (){
    //Pessoa_lista *head = NULL;
    Fila *fila = (Fila*) malloc(sizeof (Fila));
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    int op = -1;
    while(op != 4){
        printf("|==============================================|\n");
        printf("|================[Exercicio 01]================|\n");
        printf("|=[0]| Inserir Pessoa\n");
        printf("|=[1]| Deletar Pessoa \n");
        printf("|=[2]| Listar Pessoas\n");
        printf("|=[3]| Limpar Pessoas\n");
        printf("|=[4]| Sair\n");
        printf("|==============================================|\n");
        printf("|====| Insira a operacao:"); scanf("%d", &op);
        switch (op) {
            case 4:
                printf("|=| Saindo do programa");
                free(fila);
                break;
            case 0: {
                Pessoa *pessoa = criaPessoa();
                PUSH(fila, pessoa);
                break;
            }
            case 1: {
                POP(fila);
                break;
            }
            case 2:
                imprimeFila(fila);
                break;
            case 3:
                RESET(fila);
                break;
            default:
                printf("|=| Insira uma opcao valida\n");
                break;
        }
    }

    return 0;
}

Pessoa* criaPessoa(){
    Pessoa *pessoa = (Pessoa*) malloc(sizeof (Pessoa));
    printf("|=| Insira o nome:");   scanf("%s", pessoa->nome);
    printf("|=| Insira a idade:");  scanf("%d", &pessoa->idade);

    return pessoa;
}

Fila *RESET(Fila *fila){
    TipoFila *nodo;
    if(fila->primeiro == NULL){
        printf("|=| Insira uma pessoa antes!\n");
        return 0;
    }else{
        int i = 1;
        nodo = fila->primeiro;
        while(nodo->proximo != NULL){
            i++;
            nodo = nodo->proximo;
            POP(fila);
        }
        POP(fila);

        fila->primeiro = NULL;
        fila->ultimo = NULL;

        printf("|=| Foram removidas %d entradas!\n", i);
    }
    return fila;
}

void PUSH(Fila *fila, Pessoa *pessoa){
    TipoFila *nodo;
    nodo = (TipoFila*) malloc(sizeof (TipoFila));
    nodo->pessoa = pessoa;
    nodo->proximo = NULL;

    if(fila->ultimo != NULL){
        fila->ultimo->proximo = nodo;
    }else{
        fila->primeiro = nodo;
    }

    fila->ultimo = nodo;
}

int POP(Fila *fila) {
    TipoFila *nodo;
    if(fila->primeiro == NULL){
        printf("|=| Insira uma pessoa antes!\n");
        return 0;
    }else{
        nodo = fila->primeiro;
        fila->primeiro = fila->primeiro->proximo;

        if(fila->primeiro == NULL){
            fila->ultimo = NULL;
        }

        free(nodo);
        return 1;
    }
}

void imprimeFila(Fila *fila){
    TipoFila *nodo;

    if(fila->primeiro == NULL){
        printf("|=| Insira uma pessoa antes!\n");
    }else{
        int i = 0;
        for(nodo = fila->primeiro; nodo != NULL; nodo = nodo->proximo){
            printf("|===[%d]========================================|\n", i);
            printf("|=| Nome: %s\n", nodo->pessoa->nome);
            printf("|=| Idade: %i\n", nodo->pessoa->idade);
            i++;
        }
    }
}

