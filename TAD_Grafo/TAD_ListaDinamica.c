#include <stdio.h>
#include <stdlib.h>

/* Tipo estruturado adaptado de celula, para representar um cada vertice adjacente a um outro  */
struct adjacente {
    int rot;  // rotulo
    struct adjacente* proxAdj; // proximo vertice adjacente
};
typedef struct adjacente adjacente;

struct lista {
    struct adjacente* primeiro;
    struct adjacente* ultimo;
    int tamanho;
};
typedef struct lista Lista;

/*int main() {

    Lista L;
    inicializarLista(&L);

    insereEmOrdem(&L, 4);
    imprimeLista(&L);
    removeEmOrdem(&L, 4);
    imprimeLista(&L);
    printf("%p, %p, %d\n", L.primeiro, L.ultimo, L.tamanho);


    insereEmOrdem(&L, 5);
    imprimeLista(&L);
    insereEmOrdem(&L, 6);
    imprimeLista(&L);
    insereEmOrdem(&L, 1);
    imprimeLista(&L);
    insereEmOrdem(&L, 2);
    imprimeLista(&L);
    insereEmOrdem(&L, 3);
    imprimeLista(&L);
    insereEmOrdem(&L, 0);
    imprimeLista(&L);
    insereEmOrdem(&L, 9);
    imprimeLista(&L);
    insereEmOrdem(&L, 8);
    imprimeLista(&L);
    insereEmOrdem(&L, 7);
    imprimeLista(&L);
    insereEmOrdem(&L, 4);
    imprimeLista(&L);

    removeEmOrdem(&L, 9);
    imprimeLista(&L);
    removeEmOrdem(&L, 0);
    imprimeLista(&L);
    removeEmOrdem(&L, 5);
    imprimeLista(&L);
    removeEmOrdem(&L, 3);
    imprimeLista(&L);
    removeEmOrdem(&L, 7);
    imprimeLista(&L);
    removeEmOrdem(&L, 2);
    imprimeLista(&L);
    removeEmOrdem(&L, 6);
    imprimeLista(&L);
    removeEmOrdem(&L, 4);
    imprimeLista(&L);
    removeEmOrdem(&L, 8);
    imprimeLista(&L);
    printf("%p\n", L.primeiro);
    removeEmOrdem(&L, 1);
    imprimeLista(&L);
    printf("%p, %p, %d\n", L.primeiro, L.ultimo, L.tamanho);

    insereEmOrdem(&L, 5);
    imprimeLista(&L);
    insereEmOrdem(&L, 6);
    imprimeLista(&L);
    insereEmOrdem(&L, 1);
    imprimeLista(&L);
    insereEmOrdem(&L, 2);
    imprimeLista(&L);
    insereEmOrdem(&L, 3);
    imprimeLista(&L);
    insereEmOrdem(&L, 0);
    imprimeLista(&L);

    removeEmOrdem(&L, 2);
    imprimeLista(&L);
    removeEmOrdem(&L, 6);
    imprimeLista(&L);
    removeEmOrdem(&L, 5);
    imprimeLista(&L);
    removeEmOrdem(&L, 3);
    imprimeLista(&L);
    removeEmOrdem(&L, 0);
    imprimeLista(&L);
    removeEmOrdem(&L, 1);
    imprimeLista(&L);
    printf("%p, %p, %d\n", L.primeiro, L.ultimo, L.tamanho);
    return 0;
}*/

void inicializarListaAdj(Lista* L) {
    L->primeiro = NULL;
    L->ultimo = NULL;
    L->tamanho = 0;
}

int listaAdjVazia(Lista* L) {
    return !L->tamanho;
}

adjacente* criaAdjacente(int novo) {
    adjacente* novoAdjacente;
    if ((novoAdjacente = malloc(sizeof(adjacente)))) {
        novoAdjacente->rot = novo;
        novoAdjacente->proxAdj = NULL;
        return novoAdjacente;
    }
    return NULL;
}

int buscaListaAdj(Lista* L, int buscado) {
    adjacente* aux = L->primeiro;
    while(aux) {
        if (aux->rot == buscado)
            return 1;
    }
    return 0;
}

void imprimeListaAdj(Lista* L) {
    adjacente* aux = L->primeiro;
    while (aux) {
        printf("--->>[%d]", aux->rot);
        aux = aux->proxAdj;
    }
    printf("--->>[\\]\n");
}
