#include <stdio.h>
#include <stdlib.h>

struct celula {
    int info;
    struct celula* prox;
};
typedef struct celula celula;

struct pilha {
    celula* topo;
    int tamanho;
};
typedef struct pilha Pilha;

void inicializarPilha(Pilha*);
int pilhaVazia(Pilha*);
celula* criaCelula(int);
int empilhar(Pilha*, int);
int desempilhar(Pilha*);
int topoPilha(Pilha*);
void finalizarPilha(Pilha*);
void imprimePilha(Pilha*);

int main() {

    Pilha P;
    inicializarPilha(&P);
    printf("&Topo: %p - Tamanho: %d\n\n", P.topo, P.tamanho);

    empilhar(&P, 5);
    imprimePilha(&P);
        empilhar(&P, 4);
    imprimePilha(&P);
        empilhar(&P, 2);
    imprimePilha(&P);
    printf("%d\n", topoPilha(&P));

    /*desempilhar(&P);
    imprimePilha(&P);
        desempilhar(&P);
    imprimePilha(&P);
        desempilhar(&P);
    imprimePilha(&P);
        desempilhar(&P);
    imprimePilha(&P);*/

    finalizarPilha(&P);

    printf("Topo: %p - Tamanho: %d\n\n", P.topo, P.tamanho);

    return 0;
}

void inicializarPilha(Pilha* P) {
    P->topo = NULL;
    P->tamanho = 0;
}

int pilhaVazia(Pilha* P) {
    return !P->tamanho;
}

celula* criaCelula(int novo) {
    celula* novaCelula;
    if ((novaCelula = malloc(sizeof(celula)))) {
        novaCelula->info = novo;
        novaCelula->prox = NULL;
        return novaCelula;
    }
    return NULL;
}

int empilhar(Pilha* P, int novo) {
    celula* novaCelula = criaCelula(novo);
    if (novaCelula == NULL)
        return 0;   //não empilhado
    novaCelula->prox = P->topo;
    P->topo = novaCelula;
    P->tamanho++;
    return 1;
}

int desempilhar(Pilha* P) {
    celula* removido;
    int x;
    if (!pilhaVazia(P)) {
        removido = P->topo;
        P->topo = removido->prox;
        P->tamanho--;
        x = removido->info;
        free(removido);
        return x;
    }
    return -1;
}

int topoPilha(Pilha* P) {
    if(!pilhaVazia(P))
        return P->topo->info;
    return -1;
}

void finalizarPilha(Pilha* P) {
    while(!pilhaVazia(P))
        desempilhar(P);
}

void imprimePilha(Pilha* P) {
    celula* aux = P->topo;
    while (aux) {
        printf("[ %d ]\n", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}
