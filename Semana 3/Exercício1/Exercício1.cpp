#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[30];
    int idade;
    int altura;
}Pessoa;

Pessoa* alocaPessoa(Pessoa* ptr, int quantidade){
    if(ptr == NULL){
        ptr = (Pessoa*)malloc(quantidade * sizeof(Pessoa));
    }else{
        ptr = (Pessoa*)realloc(ptr, ((quantidade) * sizeof(Pessoa)));
    }
    return ptr;
}

void listaPessoa(Pessoa* pessoa, int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("|===[%d]===========================|\n", i);
        printf("    |=| Nome => %s\n",pessoa[i].nome);
        printf("    |=| Idade => %d\n",pessoa[i].idade);
        printf("    |=| Altura => %d\n",pessoa[i].altura);
        printf("\n");
    }
}

void inserePessoa(Pessoa* pessoa, char nome[30], int idade, int altura, int posicao){
    strcpy(pessoa[posicao].nome, nome);
    pessoa[posicao].idade = idade;
    pessoa[posicao].altura = altura;
}

Pessoa* removePessoa(Pessoa* pessoa, int quantidade, int posicao){
    Pessoa* temp = NULL;
    temp = alocaPessoa(temp, quantidade - 1);
    //int c;
    for(int i = 0; i < posicao; i++){
        inserePessoa(temp, pessoa[i].nome, pessoa[i].idade, pessoa[i].altura, i);
        //printf("->%d\n", i);
    }

    for(int i = posicao; i < quantidade - 1; i++){
        int index = i + 1;
        inserePessoa(temp, pessoa[index].nome, pessoa[index].idade, pessoa[index].altura, i);
        //printf("->%d\n", i+ 1);
    }
    //listaPessoa(temp, quantidade - 1);
    pessoa = alocaPessoa(pessoa, quantidade - 1);

    for(int i = posicao; i < quantidade - 1; i++){
        inserePessoa(pessoa, temp[i].nome, temp[i].idade, temp[i].altura, i);
        //printf("->%d\n", i+ 1);
    }

    free(temp);
    return pessoa;
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
    Pessoa *pessoa = NULL;
    int tamanho = 0;
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
                int temp_tamanho = tamanho;
                printf("|============================|\n");
                printf("|=| Inserir novos nomes\n");
                while (true) {
                    printf("|=| Insira o tamanho:");
                    scanf("%d", &temp_tamanho);
                    if ((temp_tamanho > tamanho) && (temp_tamanho != 0)) {
                        break;
                    }else{
                        printf("|=| Entrada inválida\n");
                    }
                }
                if(pessoa == NULL){
                    printf("|=| Iniciando\n");
                    pessoa = alocaPessoa(pessoa, temp_tamanho);

                    for(int i = 0; i < temp_tamanho; i++){
                        printf("|=|[%d] Insira o nome:", i);   scanf(" %[^\n]", nome);
                        printf("|=|[%d] Insira a idade:", i);  scanf("%d", &idade);
                        printf("|=|[%d] Insira a altura:", i); scanf("%d", &altura);
                        inserePessoa(pessoa, nome, idade, altura, i);
                    }
                }else{
                    pessoa = alocaPessoa(pessoa, tamanho + temp_tamanho);
                    for(int i = tamanho; i < temp_tamanho; i++){
                        printf("|=|[%d] Insira o nome:", i);   scanf(" %[^\n]", nome);
                        printf("|=|[%d] Insira a idade:", i);  scanf("%d", &idade);
                        printf("|=|[%d] Insira a altura:", i); scanf("%d", &altura);
                        inserePessoa(pessoa, nome, idade, altura, i);
                    }
                }
                tamanho = temp_tamanho;
                break;
            }
            case 1: {
                if(pessoa != NULL){
                    printf("|============================|\n");
                    printf("|=| Lista de pessoas\n");
                    listaPessoa(pessoa, tamanho);
                }else{
                    printf("|=| Insira pelo menos uma pessoa antes\n");
                }
                break;
            }
            case 2: {
                if(pessoa != NULL){
                    printf("|============================|\n");
                    printf("|=| Remover pessoas\n");
                    int rem = -1;
                    while(rem < 0 || rem > tamanho){
                        printf("|=| Insira o indice dejeado:"); scanf("%d", &rem);
                        if(rem < 0 || rem > tamanho){
                            printf("|=| Insira um valor válido\n");
                        }
                    }
                    printf("|=| %s - <== Foi removido!\n", pessoa[rem].nome);
                    pessoa = removePessoa(pessoa, tamanho, rem);
                    tamanho--;
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
