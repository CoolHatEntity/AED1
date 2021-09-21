#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[32];
    int idade;
}Pessoa;

typedef struct Lista{
    Pessoa* pessoa;
    struct Lista* proximo;
}Lista;

Pessoa* criaPessoa();
void push(Lista **lista, int pos, int fim); //Deve receber posicao, e head;
void pop(Lista **lista,int pos, int fim); //Apenas remove o elemento, reorganizando a lista depois
void reset(Lista **lista); //Remove todos os elementos
int getElement(Lista *lista, char nome[32]); //Retorna a posicao dado um nome
void printPessoa(Pessoa *pessoa, int pos); // Imprime a pessoa, dada a pessoa e a posicao
void printList(Lista *lista); //Imprime a lista;

int main (){
    //Pessoa_lista *head = NULL;
    Lista* lista = NULL;
    int fim = 0;


    int op = -1;
    while(op != 5){
        printf("|==============================================|\n");
        printf("|================[Exercicio 01]================|\n");
        printf("|=[0]| Inserir Pessoa\n");
        printf("|=[1]| Deletar Pessoa por posicao\n");
        printf("|=[2]| Deletar Pessoa por nome\n");
        printf("|=[3]| Listar Pessoas\n");
        printf("|=[4]| Limpar Pessoas\n");
        printf("|=[5]| Sair\n");
        printf("|==============================================|\n");
        printf("|====| Insira a operacao:"); scanf("%d", &op);
        switch (op) {
            case 5:
                printf("|=| Saindo do programa");
                break;
            case 0: {
                int pos = 0;
                while(pos < 0 || pos > fim){
                    printf("|=| Insira a posicao desejada:"); scanf("%s", &pos);
                }
                push(&lista, pos, fim);
                fim++;
                break;
            }
            case 1: {
                int pos = 0;
                while(pos < 0 || pos > fim){
                    printf("|=| Insira a posicao desejada:"); scanf("%s", &pos);
                }
                pop(&lista,pos, fim);
                break;
            }
            case 2: {
                char input[32];
                printf("|=| Insira o nome desejado:"); scanf("%s", &input);
                getElement(lista, input);
                break;
            }
            case 3:
                printList(lista);
                break;
            case 4:
                reset(&lista);
                fim = 0;
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

void push(Lista **lista, int pos, int fim){
    if(*lista == NULL){
        *lista = (Lista*)malloc(sizeof (Lista));
        (*lista)->pessoa = criaPessoa();
        (*lista)->proximo = NULL;
    }else if(pos == fim){
        Lista *proximo = (Lista*)malloc(sizeof(Lista));
        Lista *novo = (Lista*)malloc(sizeof(Lista));
        novo->pessoa = criaPessoa();
        novo->proximo = NULL;

        while(proximo != NULL){
            proximo = proximo->proximo;
        }
        proximo->proximo = novo;

    }else{
        Lista *anterior = (Lista*)malloc(sizeof(Lista));
        Lista *proximo = (*lista);
        int i = 0;
        while(proximo->proximo != NULL && i != pos){
            anterior = proximo;
            proximo = proximo->proximo;
            i++;
        }
        Lista *novo = (Lista*)malloc(sizeof(Lista));
        novo->proximo = proximo;
        novo->pessoa = criaPessoa();
        anterior->proximo = novo;
    }
}

void pop(Lista **lista,int pos, int fim){
    if((*lista)->proximo == NULL){
        (*lista)->pessoa->idade = 0;
        strcpy((*lista)->pessoa->nome, "\0");
        (*lista) = NULL;
        free((*lista));
    }else if(pos == fim){
        Lista *proximo = (*lista);
        Lista *anterior = (Lista*) malloc(sizeof(Lista));

        while(proximo != NULL){
            anterior = proximo;
            proximo = proximo->proximo;
        }
        anterior->proximo = NULL;

        proximo->pessoa->idade = 0;
        strcpy(proximo->pessoa->nome, "\0");
        proximo = NULL;
        free(proximo);
    }else{
        Lista *proximo = (*lista);
        Lista *anterior = (Lista*) malloc(sizeof(Lista));

        int i = 0;
        while((proximo->proximo != NULL) && (pos != i)){
            anterior = proximo;
            proximo = proximo->proximo;
            i++;
        }

        anterior->proximo = proximo->proximo;

        proximo->pessoa->idade = 0;
        strcpy(proximo->pessoa->nome, "\0");
        proximo = NULL;
        free(proximo);
    }
}

void reset(Lista **lista){
    if((*lista)->proximo == NULL){
        (*lista)->pessoa->idade = 0;
        strcpy((*lista)->pessoa->nome, "\0");
        (*lista) = NULL;
        free((*lista));

    }else{
        Lista *proximo = (*lista);
        Lista *anterior = (Lista*) malloc(sizeof(Lista) );

        while(proximo != NULL){
            anterior = proximo;

            anterior->proximo = NULL;
            anterior->pessoa->idade = 0;
            strcpy(anterior->pessoa->nome, "\0");
            free(anterior);

            proximo = proximo->proximo;
        }
        free(lista);
    }

}

int getElement(Lista *lista, char nome[32]){
    //Ele retornara a primeira ocorrencia do nome, para evitar complicacoes desnecessarias
    int c = 0;
    int i = 0;
    int pos = -1;
    Lista *temp = lista;

    while(temp != NULL){
        if(strcmp(temp->pessoa->nome, nome) == 0){
            pos = i;
            break;
        }
        temp = temp->proximo;
        i++;
    }

    if((c >= 0)){
        return pos;
    }else{
        //Retornar -1 significa que achou ninguem
        return -1;
    }
}

void printPessoa(Pessoa* pessoa, int pos){
    printf("|===[%d]========================================|\n", pos);
    printf("    |=| Nome => %s\n", pessoa->nome);
    printf("    |=| Idade => %d\n", pessoa->idade);
}

void printList(Lista *lista){
    int i = 0;
    Lista *temp = lista;
    while(temp != NULL){
        printPessoa(temp->pessoa, i);
        temp = temp->proximo;
        i++;
    }
}
