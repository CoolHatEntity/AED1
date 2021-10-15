#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Optei por seguir com uma solucao que permite entradas
 * repetidas na arvore, cada celula possui dois campos,
 * a Chave e a Contagem, onde o valor aumenta ou diminui
 * baseado no numero de repeticoes desta chave em questao
 * */

typedef struct Registry{
    long int Key;
    unsigned int Count;
}Registry;

typedef struct Node{
    Registry *Reg;
    struct Node *pLeft, *pRight;
}Node;

//Insere um novo um nodo, caso seja repetida, aumenta o Count em 1
void BST_INSERT(Node **nodo, long int chave);

//Possui tres modos
// 1 - Retorna o nodo com a chave especificada se ele existir
// 2 - Retorna o menor nodo (Usado apenas internamente)
// 3 - Retorna o maior nodo (Usado apenas internamente)
Node* BST_FIND(Node *nodo, int modo,long int chave);

//Encontra um nodo para resposição
Node* BST_NEXT(Node *nodo);

//Remove um nodo, caso tenha repeticao, diminui o Count em 1 ao inves de remover
void BST_REMOVE(Node **nodo, long int chave);

//Limpa a arvore
void BST_PURGE_TREE(Node **head);

//Limpa um nodo especifico
void BST_PURGE_NODE(Node **nodo);

//Lista os registros e sua contagem de diferentes formas
// 1 - Lista de forma crescente
// 2 - Lista de forma decrescente
// 3 - Lista o maior
// 4 - Lista o menor
void BST_LIST(Node *nodo, int modo);

int main() {
    Node *nodo = NULL;
    int op = -1;
    while(op != 5){
        printf("|=============================================|\n");
        printf("|=================[Exercicio]=================|\n");
        printf("|=[0]| Inserir folha\n");
        printf("|=[1]| Buscar folha \n");
        printf("|=[2]| Mostrar arvore\n");
        printf("|=[3]| Deleter folha\n");
        printf("|=[4]| Limpar arvore\n");
        printf("|=[5]| Sair\n");
        printf("|=============================================|\n");
        printf("|====| Insira a operacao:"); scanf("%d", &op);
        switch (op) {
            case 0:{
                long int chave = -1;
                printf("|=| Insira a chave:"); scanf("%ld", &chave);
                BST_INSERT(&nodo, chave);
                break;
            }
            case 1:{
                long int chave = -1;
                printf("|=| Insira a chave:"); scanf("%ld", &chave);
                Node *result = BST_FIND(nodo, 1, chave);
                if(result != NULL){
                        printf("|=| %ld[%d]", result->Reg->Key, result->Reg->Count);
                }
                break;
            }
            case 2:{
                int modo = -1;
                long int chave = -1;
                printf("|=============================================|\n"
                              "|=| 1 - Lista de forma crescente\n"
                              "|=| 2 - Lista de forma decrescente\n"
                              "|=| 3 - Lista o maior\n"
                              "|=| 4 - Lista o menor\n"
                              "|=============================================|\n");

                while(modo < 1 || modo > 4){
                    printf("|=| Insira o modo:"); scanf("%d", &modo);
                }
                BST_LIST(nodo, modo);
                break;
            }
            case 3:{
                long int chave = -1;
                printf("|=| Insira a chave:"); scanf("%ld", &chave);
                BST_REMOVE(&nodo, chave);
                break;
            }
            case 4:
                BST_PURGE_TREE(&nodo);
                break;
            case 5:
                printf("|=| Saindo do programa");
                BST_PURGE_TREE(&nodo);
                break;
        }
    }

    BST_INSERT(&nodo, 5);

    BST_INSERT(&nodo, 3);
    BST_INSERT(&nodo, 2);
    BST_INSERT(&nodo, 4);
    BST_INSERT(&nodo, 1);
    BST_INSERT(&nodo, 7);
    BST_INSERT(&nodo, 6);
    BST_INSERT(&nodo, 8);

    printf("|=| "); BST_LIST(nodo, 1); printf("\n");
    printf("|=| "); BST_LIST(nodo, 2); printf("\n");
    BST_LIST(nodo, 3);printf("\n");
    BST_LIST(nodo, 4);printf("\n");

    Node *result = (Node *) BST_FIND(nodo, 1, 9);
    if(result != NULL){
        printf("|=| %ld || %p\n", result->Reg->Key, result);
        if(result == nodo){
            printf("|=| E igual!\n");
        }else{
            printf("|=| Nao e igual!\n");
        }
    }

    //BST_REMOVE(&nodo, 1);
    //BST_REMOVE(&nodo, 8);
    BST_REMOVE(&nodo, 5);

    //BST_REMOVE(&nodo, 5);

    printf("|=| "); BST_LIST(nodo, 1);printf("\n");

    BST_PURGE_TREE(&nodo);

    return 0;
}

void BST_INSERT(Node **nodo, long int chave){
    if(*nodo == NULL){
        *nodo = (Node*) malloc(sizeof (Node));
        if((*nodo) == NULL){
            printf("|=| Erro de alocamento!\n");
            exit(0);
        }

        //Atribui os valores para o nodo
        (*nodo)->Reg = (Registry*) malloc(sizeof (Registry));
        (*nodo)->Reg->Key = chave;
        (*nodo)->Reg->Count = 1;
        (*nodo)->pLeft = NULL; (*nodo)->pRight = NULL;
        return;
    }else{
        if(chave < (*nodo)->Reg->Key){
            BST_INSERT(&(*nodo)->pLeft , chave);
            return;

        }else if(chave > (*nodo)->Reg->Key){
            BST_INSERT(&(*nodo)->pRight, chave);
            return;

        }else if(chave == (*nodo)->Reg->Key){
            (*nodo)->Reg->Count++;
            return;
        }
    }
}

Node* BST_FIND(Node *nodo, int modo,long int chave){
    if(nodo == NULL){
        printf("|=| Nao encontrado!\n");
        return NULL;
    }
    switch (modo){
        case 1:
            if(chave < nodo->Reg->Key){
                return BST_FIND(nodo->pLeft, 1, chave);
            }else if(chave > nodo->Reg->Key){
                return BST_FIND(nodo->pRight, 1,chave);
            }else if(chave == nodo->Reg->Key){
                return nodo;
            }else{
                printf("|=| Nao encontrado!\n");
                return NULL;
            }
        case 2:
            while(nodo->pLeft != NULL){
                nodo = nodo->pLeft;
            }
            return nodo;
        case 3:
            while(nodo->pRight != NULL){
                nodo = nodo->pRight;
            }
            return nodo;
        default:

            printf("|=| Modo invalido\n");
            return NULL;
    }
}


//Deve encontrar o maior valor no lado esquerdo
Node* BST_NEXT(Node *nodo){
    if(nodo == NULL){
        return NULL;
    }else{
        //Estava tendo alguns problemas com memory leaks, decidi deixar alguns
        //testes a mais por garantia
        if(nodo->pLeft != NULL){
            nodo = nodo->pLeft;
            if(nodo->pRight != NULL){
                nodo = BST_FIND(nodo, 3, 0);
            }
            return nodo;
        }else{
            return NULL;
        }
    }
}

void BST_REMOVE(Node **nodo, long int chave){
    if((*nodo) == NULL){
        return;
    }else if(chave < (*nodo)->Reg->Key){
        BST_REMOVE(&(*nodo)->pLeft, chave);
    }else if(chave > (*nodo)->Reg->Key){
        BST_REMOVE(&(*nodo)->pRight, chave);
    }else if(chave == (*nodo)->Reg->Key){
        if((*nodo)->Reg->Count > 1){
            (*nodo)->Reg->Count--;
            return;
        }else{
            if(((*nodo)->pLeft == NULL) && ((*nodo)->pRight != NULL)){
                Node *next = (*nodo)->pRight;

                (*nodo)->Reg->Key = next->Reg->Key;
                (*nodo)->Reg->Count = next->Reg->Count;
                (*nodo)->pLeft = next->pLeft;
                (*nodo)->pRight = next->pRight;


                BST_REMOVE(&next, next->Reg->Key);

                next = NULL;

                return;

            }else if(((*nodo)->pLeft != NULL) && ((*nodo)->pRight == NULL)){
                Node *next = (*nodo)->pLeft;

                (*nodo)->Reg->Key = next->Reg->Key;
                (*nodo)->Reg->Count = next->Reg->Count;
                (*nodo)->pLeft = next->pLeft;
                (*nodo)->pRight = next->pRight;

                BST_REMOVE(&next, next->Reg->Key);

                next = NULL;

                return;

            }else if(((*nodo)->pLeft == NULL) && ((*nodo)->pRight == NULL)){
                BST_PURGE_NODE(&(*nodo));
                return;
            }else if(((*nodo)->pLeft != NULL) && ((*nodo)->pRight != NULL)){
                Node *temp = BST_NEXT((*nodo));

                long int key = temp->Reg->Key;
                unsigned int count =  temp->Reg->Count;

                BST_REMOVE(&(*nodo), key);

                //Teria como me ajudar a entender porque usar a funcao deste jeito
                //faz um seg_fault acontecer?
                //BST_PURGE_NODE(&temp);

                (*nodo)->Reg->Key = key;
                (*nodo)->Reg->Count = count;

                return;
            }
        }
    }
}

void BST_PURGE_TREE(Node **head){
    if((*head) == NULL){
        printf("|=| Arvore vazia");
        return;
    }else{
        Node *left = NULL;
        Node *right = NULL;

        if((*head)->pLeft != NULL){ left = (*head)->pLeft;}
        if((*head)->pRight != NULL){ right = (*head)->pRight;}

        (*head)->Reg->Key = 0;
        (*head)->Reg->Count = 0;
        (*head)->pLeft = NULL;
        (*head)->pRight = NULL;

        free((*head)->Reg);
        free((*head));

        (*head) = NULL;

        if(left != NULL){ BST_PURGE_TREE(&left);}
        if(right != NULL){ BST_PURGE_TREE(&right);}
    }
}

void BST_PURGE_NODE(Node **nodo){
    (*nodo)->Reg->Key = 0;
    (*nodo)->Reg->Count = 0;
    (*nodo)->pLeft = NULL;
    (*nodo)->pRight = NULL;

    free((*nodo)->Reg);
    free((*nodo));

    (*nodo) = NULL;
}

void BST_LIST(Node *nodo, int modo){
    switch (modo) {
        case 1:
            if(nodo != NULL){
                if(nodo->pLeft != NULL){BST_LIST(nodo->pLeft, 1);}
                printf("%ld[%d] ", nodo->Reg->Key, nodo->Reg->Count);
                if(nodo->pRight != NULL){BST_LIST(nodo->pRight, 1);}
            }
            break;
        case 2:
            if(nodo != NULL){
                BST_LIST(nodo->pRight, 2);
                printf("%ld[%d] ", nodo->Reg->Key, nodo->Reg->Count);
                BST_LIST(nodo->pLeft, 2);
            }
            break;
        case 3:
            nodo = BST_FIND(nodo, 3, 0);
            printf("|=| %ld[%d] ", nodo->Reg->Key, nodo->Reg->Count);
            break;
        case 4:
            nodo = BST_FIND(nodo, 2, 0);
            printf("|=| %ld[%d] ", nodo->Reg->Key, nodo->Reg->Count);
            break;
        default:
            printf("|=| Modo invalido\n");
            break;
    }
}

