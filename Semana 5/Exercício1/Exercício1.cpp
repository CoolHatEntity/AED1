#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Pessoa{
    char nome[32];
    int idade = 0;
    Pessoa *proximo = NULL;
}Pessoa_lista;

Pessoa_lista* criaPessoa();
void push(Pessoa_lista **head);
void pop(Pessoa_lista **head);
void limpaLista(Pessoa_lista **head);
bool temProximo(Pessoa_lista *pessoa);
void listaPessoa(Pessoa_lista *head);

int main (){
    Pessoa_lista *head = NULL;

    int op = -1;
    while(op != 4){
        printf("|==============================================|\n");
        printf("|================[Exercicio 01]================|\n");
        printf("|=[0]| Inserir Pessoa\n");
        printf("|=[1]| Deletar Pessoa\n");
        printf("|=[2]| Listar Pessoas\n");
        printf("|=[3]| Limpar Pessoas\n");
        printf("|=[4]| Sair\n");
        printf("|==============================================|\n");
        printf("|====| Insira a operacao:"); scanf("%d", &op);
        switch (op) {
            case 4:
                printf("|=| Saindo do programa");
                break;
            case 0:
                push(&head);
                break;
            case 1:
                pop(&head);
                break;
            case 2:
                listaPessoa(head);
                break;
            case 3:
                limpaLista(&head);
                break;
            default:
                printf("|=| Insira uma opcao valida\n");
                break;
        }
    }





    return 0;
}

Pessoa_lista* criaPessoa(){
    char nome[32];
    int idade;
    printf("|=| Insira o nome:"); scanf("%s", nome);
    printf("|=| Insira a idade:"); scanf("%d", &idade);

    Pessoa_lista *temp = (Pessoa_lista*)malloc(sizeof(Pessoa_lista));
    strcpy(temp->nome, nome);
    temp->idade = idade;

    return temp;
}
void push(Pessoa_lista **head){
    if(*head == NULL){
        *head = (Pessoa_lista*)malloc(sizeof (Pessoa_lista));
        (*head)= criaPessoa();
        (*head)->proximo = NULL;
    }else{
        Pessoa_lista *proximo = (Pessoa_lista*)malloc(sizeof (Pessoa_lista));
        proximo->idade = (*head)->idade;
        proximo->proximo = (*head)->proximo;
        strcpy(proximo->nome, (*head)->nome);

        (*head) = criaPessoa();
        (*head)->proximo = proximo;
    }
}
void pop(Pessoa_lista **head){
    if((*head)->proximo == NULL){
        (*head)->idade = 0;
        strcpy((*head)->nome, "\0");
        (*head) = NULL;
        free((*head));
    }else{
        Pessoa_lista *anterior = (Pessoa_lista*)malloc(sizeof (Pessoa_lista));
        Pessoa_lista *pessoa = (*head);
        while(pessoa->proximo != NULL){
            anterior = pessoa;
            pessoa = pessoa->proximo;
        }
        printf("|=| Removando: %s\n", pessoa->nome);
        pessoa->idade = 0;
        strcpy(pessoa->nome, "\0");
        pessoa = NULL;
        free(pessoa);
        anterior->proximo = NULL;
    }
}
void limpaLista(Pessoa_lista **head){
    if(head == NULL){
        pop(head);
    }else{
        Pessoa_lista *anterior = (Pessoa_lista*)malloc(sizeof (Pessoa_lista));
        Pessoa_lista *pessoa = (*head);
        while(pessoa != NULL){
            anterior = pessoa;
            pessoa = pessoa->proximo;

            anterior->idade = 0;
            anterior->proximo = NULL;
            strcpy(anterior->nome, "\0");
            anterior = NULL;
            free(anterior);
        }
        pop(head);
    }
}
bool temProximo(Pessoa_lista *pessoa){
    if(pessoa->proximo == NULL){
        return false;
    }else{
        return true;
    }
}
void listaPessoa(Pessoa_lista *head){
    int i = 0;
    if(head != NULL){
        Pessoa_lista *pessoa = head;
        while(pessoa != NULL){
            printf("|===[%d]========================================|\n", i);
            printf("    |=| Nome => %s\n", pessoa->nome);
            printf("    |=| Idade => %d\n", pessoa->idade);
            printf("    |=| Tem proximo? => %s\n", temProximo(pessoa)?"TRUE":"FALSE");
            i++;

            pessoa = pessoa->proximo;
        }
        printf("|==============================================|\n");
    }else{
        printf("|=| Insira alguem antes!\n");
        printf("|==============================================|\n");
    }
}