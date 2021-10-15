#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registry{
    long int Data;
}Registry;

typedef struct Node{
    Registry *Reg;
    struct Node *next;
}Node;

Registry* criaReg();
void PUSH(Node **nodo);
void POP(Node **nodo);
void CLEAR(Node **nodo);
void LIST(Node *nodo);

int main() {
    Node *nodo = NULL;
    int op = -1;
    while(op != 4){
        printf("|=============================================|\n");
        printf("|=================[Questão 2]=================|\n");
        printf("|=[0]| Push\n");
        printf("|=[1]| Pop \n");
        printf("|=[2]| Clear\n");
        printf("|=[3]| Listar\n");
        printf("|=[4]| Sair\n");
        printf("|=============================================|\n");
        printf("|====| Insira a operacao:"); scanf("%d", &op);

        switch (op) {
            case 0:
                PUSH(&nodo);
                break;
            case 1:
                POP(&nodo);
                break;
            case 2:
                CLEAR(&nodo);
                break;
            case 3:
                LIST(nodo);
                break;
            case 4:
                CLEAR(&nodo);
                break;
            default:
                printf("|=| Entrada invalida\n");
                break;
        }
    }
}

Registry* criaReg(){
    Registry *ret_val = (Registry*)malloc(sizeof(Registry));
    printf("|=| Insira a chave:"); scanf("%ld", &ret_val->Data);

    return ret_val;
}

void PUSH(Node **nodo){
    if((*nodo) == NULL){
        (*nodo) = (Node*)malloc(sizeof (Node));
        (*nodo)->Reg = criaReg();
        (*nodo)->next = NULL;
    }else{
        PUSH(&(*nodo)->next);
        return;
    }
}

void POP(Node **nodo){
    if((*nodo) == NULL){
        return;
    }else{
        if((*nodo)->next == NULL){

            (*nodo)->Reg->Data = 0;

            free((*nodo)->Reg);
            free((*nodo));

            (*nodo)->Reg = NULL;
            (*nodo) = NULL;

        }else{
            POP(&(*nodo)->next);
            return;
        }
    }

}

void CLEAR(Node **node){
    if((*node) == NULL){
        return;
    }else{
        Node *next = (*node)->next;

        (*node)->next = NULL;
        (*node)->Reg->Data = 0;

        free((*node)->Reg);
        free((*node));

        (*node)->Reg = NULL;
        (*node) = NULL;

        CLEAR(&next);
    }
}

void LIST(Node *nodo){
    if(nodo == NULL){
        return;
    }else{
        printf("|=| %ld\n", nodo->Reg->Data);
        LIST(nodo->next);
        return;
    }
}