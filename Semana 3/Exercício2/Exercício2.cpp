#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa{
    char nome[30];
    int idade;
    int altura;
    struct Pessoa *proximo;
}Pessoa_t;

void listaPessoa(Pessoa_t* pessoa_head){

    int i = 0;
    Pessoa_t* pessoa = pessoa_head;
    while(pessoa != NULL){
        printf("|===[%d]===========================|\n", i);
        printf("    |=| Nome => %s\n",pessoa->nome);
        printf("    |=| Idade => %d\n",pessoa->idade);
        printf("    |=| Altura => %d\n",pessoa->altura);
        printf("\n");
        i++;
        pessoa = pessoa->proximo;
    }
}

void inserePessoa(Pessoa_t** pessoa_head, char nome[30], int idade, int altura){
    Pessoa_t* pessoa = (Pessoa_t*) malloc(sizeof(Pessoa_t));

    pessoa->idade = idade;
    pessoa->altura = altura;
    strcpy(pessoa->nome, nome);
    pessoa->proximo = (*pessoa_head);
    (*pessoa_head) = pessoa;

}

void removePessoa(Pessoa_t** pessoa_head,int posicao){
    int i = 0;
    Pessoa_t* pessoa = (*pessoa_head);
    Pessoa_t* anterior = NULL;
    if(pessoa != NULL && 0 == posicao){
        *pessoa_head = pessoa->proximo;
        free(pessoa);
        return;
    }
    while(pessoa != NULL && i != posicao){
        anterior = pessoa;
        pessoa = pessoa->proximo;
        i++;
    }

    if(pessoa == NULL){
        printf("|=| Pessoa nao encontrada!\n");
    }
    anterior->proximo = pessoa->proximo;
    free(pessoa);

}

void imprimeTela(){
    printf("|============================|\n");
    printf("|=| [0] Inserir pessoa\n");
    printf("|=| [1] Listar pessoas\n");
    printf("|=| [2] Remover pessoas\n");
    printf("|=| [3] Sair\n");
    printf("|============================|\n");
}

int main() {
    Pessoa_t *pessoa_head = NULL;

    int op = 0;
    char nome[30];
    int altura;
    int idade;


    bool deveSair = false;
    while(!deveSair){
        imprimeTela();
        printf("|=| Insira a operacao:");
        scanf("%d", &op);
        printf("\n");
        switch (op)
        {
            case 0: {
                int tamanho = 0;
                printf("|============================|\n");
                printf("|=| Inserir novos nomes\n");
                while (true) {
                    printf("|=| Insira o tamanho:");
                    scanf("%d", &tamanho);
                    if ((tamanho > 0)) {
                        break;
                    }else{
                        printf("|=| Entrada inválida\n");
                    }
                }
                printf("|=| Iniciando\n");

                for(int i = 0; i < tamanho; i++){
                    printf("|=|[%d] Insira o nome:", i);   scanf(" %[^\n]", nome);
                    printf("|=|[%d] Insira a idade:", i);  scanf("%d", &idade);
                    printf("|=|[%d] Insira a altura:", i); scanf("%d", &altura);
                    inserePessoa(&pessoa_head, nome, idade, altura);
                }
                break;
            }
            case 1: {
                if(pessoa_head != NULL){
                    printf("|============================|\n");
                    printf("|=| Lista de pessoas\n");
                    listaPessoa(pessoa_head);
                }else{
                    printf("|=| Insira pelo menos uma pessoa antes\n");
                }
                break;
            }
            case 2: {
                if(pessoa_head != NULL){
                    printf("|============================|\n");
                    printf("|=| Remover pessoas\n");
                    int rem = -1;
                    printf("|=| Insira o indice dejeado:"); scanf("%d", &rem);
                    if(rem >= 0){
                        removePessoa(&pessoa_head, rem);
                    }else{
                        printf("|=| Entrada inválida\n");
                    }
                }else{
                    printf("|=| Insira pelo menos uma pessoa antes\n");
                }
                break;
            }
            case 3: {
                deveSair = true;
                break;
            }
            default: {
                printf("|=| Operacao errada\n");
                break;
            }
        }
    }

    return 0;
}
