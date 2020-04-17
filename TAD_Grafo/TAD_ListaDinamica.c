#include <stdio.h>
#include <stdlib.h>

struct adjacente {
    int vertice;
    struct adjacente* proxAdj;
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
        novoAdjacente->vertice = novo;
        novoAdjacente->proxAdj = NULL;
        return novoAdjacente;
    }
    return NULL;
}

int buscaListaAdj(Lista* L, int buscado) {
    adjacente* aux = L->primeiro;
    while(aux) {
        if (aux->vertice == buscado)
            return 1;
    }
    return 0;
}

int insereVertice(Lista* L, int novo) {
    adjacente* novoAdjacente;
    adjacente* aux;
    adjacente* ant;

    if((novoAdjacente = criaAdjacente(novo))) {
        if(listaAdjVazia(L)) {
            L->primeiro = novoAdjacente;
            L->ultimo = novoAdjacente;
        } else {
            if (L->primeiro->vertice > novo) {
                novoAdjacente->proxAdj = L->primeiro;
                L->primeiro = novoAdjacente;
            } else {
                if(L->ultimo->vertice < novo) {
                    L->ultimo->proxAdj = novoAdjacente;
                    L->ultimo = novoAdjacente;
                } else {
                    ant = aux = L->primeiro;
                    while (aux) {
                        if (aux->vertice > novo)
                            break;
                        ant = aux;
                        aux = aux->proxAdj;
                    }
                    ant->proxAdj = novoAdjacente;
                    novoAdjacente->proxAdj = aux;
                }
            }
        }
        L->tamanho++;
        return 1;
    }
    return 0;
}

int removeVertice(Lista* L, int x) {
    adjacente* aux;
    adjacente* ant;

    if (listaAdjVazia(L))
        return -1;

    ant = NULL;
    aux = L->primeiro;
    if (aux->vertice == x) {
        L->primeiro = L->primeiro->proxAdj;
    } else {
        ant = aux;
        while(aux) {
            if(aux->vertice == x)
                break;
            ant = aux;
            aux = aux->proxAdj;
        }
        ant->proxAdj = aux->proxAdj;
    }
    if (aux->proxAdj == NULL)
        L->ultimo = ant;
    L->tamanho--;
    free(aux);
    return x;
}

void finalizaListaAdj(Lista* L) {
    while(L->primeiro)
        removeVertice(L, L->primeiro->vertice);
}

void imprimeListaAdj(Lista* L) {
    adjacente* aux = L->primeiro;
    while (aux) {
        printf("--->>[%d]", aux->vertice);
        aux = aux->proxAdj;
    }
    printf("\n");
}
