#include <stdio.h>
#include <stdlib.h>

struct celula {
    int info;
    struct celula* prox;
};
typedef struct celula celula;

struct fila {
    struct celula* primeiro;
    struct celula* ultimo;
    int tamanho;
};
typedef struct fila Fila;

int main() {

    Fila F;

    inicializarFila(&F);                // printf("%p, %p, %d\n", F.primeiro, F.ultimo, F.tamanho);
    //printf("%d\n", filaVazia(&F));

    enfileirar(&F, 5);
    imprimeFila(&F);
    enfileirar(&F, 15);
    imprimeFila(&F);
    enfileirar(&F, 3);
    imprimeFila(&F);
    enfileirar(&F, 0);
    imprimeFila(&F);
    enfileirar(&F, -7);
    imprimeFila(&F);

    finalizarFila(&F);


    /*desenfileirar(&F);
    imprimeFila(&F);
    desenfileirar(&F);
    imprimeFila(&F);
    desenfileirar(&F);
    imprimeFila(&F);
    desenfileirar(&F);
    imprimeFila(&F);
    desenfileirar(&F);
    imprimeFila(&F);*/

    printf("%p, %p, %d\n", F.primeiro, F.ultimo, F.tamanho);


    printf("\n");
    return 0;
}

void inicializarFila(Fila* F) {
    F->primeiro = NULL;
    F->ultimo = NULL;
    F->tamanho = 0;
}

void finalizarFila(Fila* F) {
    while(!filaVazia(F))
        desenfileirar(F);
}

int filaVazia(Fila* F) {
    if (!F->tamanho)    //F->tamanho != 0
        return 1;
    return 0;
}

celula* criaCelula(int novaInfo) {
    celula* novaCelula;
    if ((novaCelula = malloc(sizeof(celula)))) {
        novaCelula->info = novaInfo;
        novaCelula->prox = NULL;
        return novaCelula;
    }
    return NULL;
}

void enfileirar(Fila* F, int novaInfo) {
    celula* novaCelula;
    if (novaCelula = criaCelula(novaInfo)) {
        if (filaVazia(F)) {
            F->primeiro = novaCelula;
            F->ultimo = novaCelula;
        } else {
            F->ultimo->prox = novaCelula;
            F->ultimo = novaCelula;
        }
        F->tamanho++;
    }
}

void imprimeFila(Fila* F) {
    celula* aux = F->primeiro;
    while (aux) {
        printf("<<---[%3d]", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

void desenfileirar(Fila* F) {
    celula* removido;
    if (!filaVazia(F)) {
        removido = F->primeiro;
        F->primeiro = removido->prox;
        F->tamanho--;
        free(removido);
        if (filaVazia)
            F->ultimo = NULL;
    }
}
