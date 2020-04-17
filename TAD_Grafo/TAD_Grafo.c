#include <stdio.h>
#include <stdlib.h>
#include "TAD_ListaDinamica.c"
#include "TAD_FilaDinamica.c"

//#define TAM 6

typedef Lista* GrafoL;       //Grafo como lista de Adjacências
typedef int** GrafoM;   //Grafo como matriz de Adjacências

int insereAresta(Lista*, int);
int removeAresta(Lista*, int);
void BFS(GrafoL, int, int);
void finalizaListaAdj(Lista*);

int main()
{
    GrafoL Glista;
    GrafoM Gmatriz;
    int TAM, i, j, v0;

    TAM = 6;

    Glista = (Lista*)malloc(TAM*sizeof(Lista));
    for (i = 0; i < TAM; i++)
        inicializarListaAdj(&Glista[i]);

    Gmatriz = (int**)malloc(TAM*sizeof(int*));
    for (i = 0; i < TAM; i++)
        Gmatriz[i] = (int*)malloc(TAM*sizeof(int));

    insereAresta(&Glista[0], 1);
    Gmatriz[0][1] = 1;
    insereAresta(&Glista[0], 2);
    Gmatriz[0][2] = 1;

    insereAresta(&Glista[1], 0);
    Gmatriz[1][0] = 1;
    insereAresta(&Glista[1], 2);
    Gmatriz[1][2] = 1;

    insereAresta(&Glista[2], 0);
    Gmatriz[2][0] = 1;
    insereAresta(&Glista[2], 1);
    Gmatriz[2][1] = 1;
    insereAresta(&Glista[2], 3);
    Gmatriz[2][3] = 1;

    insereAresta(&Glista[3], 2);
    Gmatriz[3][2] = 1;
    insereAresta(&Glista[3], 4);
    Gmatriz[3][4] = 1;
    insereAresta(&Glista[3], 5);
    Gmatriz[3][5] = 1;

    insereAresta(&Glista[4], 3);
    Gmatriz[4][3] = 1;
    insereAresta(&Glista[4], 5);
    Gmatriz[4][5] = 1;

    insereAresta(&Glista[5], 3);
    Gmatriz[5][3] = 1;
    insereAresta(&Glista[5], 4);
    Gmatriz[5][4] = 1;

    printf("Lista de Adjacencias do grafo G: \n");
    for(i = 0; i < TAM; i++) {
        printf("[%d]---", i);
        imprimeListaAdj(&Glista[i]);
    }

    printf("\nMatriz de Adjacencias do grafo G: \n");
    for(i = 0; i < TAM; i++) {
        for(j = 0; j < TAM; j++) {
            if (Gmatriz[i][j] != 1)
                Gmatriz[i][j] = 0;
            printf("%d ", Gmatriz[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < TAM; i++)
        free(Gmatriz[i]);
    free(Gmatriz);


    printf("\nBFS - Breadth-First Search (Busca em Largura): \n");
    printf("Digite o vertice de origem para a BFS (0 - %d): ", TAM-1);
    scanf("%d", &v0);

    printf("  v: vertice\n");
    printf("  d: distancia da origem\n");
    printf("  p: predecessor\n");
    printf("[(v), d,  p]\n");
    BFS(Glista, TAM, v0);

    for(i = 0; i < TAM; i++) {    // finaliza o grafo
        finalizaListaAdj(&Glista[i]);
        //printf("%p, %p, %d\n", Glista[i].primeiro, Glista[i].ultimo, Glista[i].tamanho);
    }
    free(Glista);
    return 0;
}

int insereAresta(Lista* L, int novo) {
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

int removeAresta(Lista* L, int x) {
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
        removeAresta(L, L->primeiro->vertice);
}

/*
    DESCRIÇÃO
    Percurso em grafo, que, partindo de um dado vértice, acessa os demais.
    Baseado na coloração:
        - Branco (b): vértice ainda não visitado
        - Cinza (c): vértice sendo visitado, isto é, acessando seus vértices adjacentes
        - Preto (p): vértice completamente visitado
    PARAMÊTROS
        G[]=vetor de vértices e suas respectivas listas de adjacências
        v0=vértice de origem
*/
void BFS(GrafoL G, int TAM, int v0) {

    int u;

    char c[TAM];                    // vetor de cores
    int p[TAM];                     // vetor de predecessores
    int d[TAM];                     // vetor de distâncias de cada vértice em relação à origem

    Fila Q;                         // fila para armazenar e ordenar a maneira de exploração dos vértices do grafo

    Lista *uAdj;                     // ponteiro auxiliar para acessar sem complicações, iteração a iteração, a lista de adjacências de cada vértice
    adjacente *v;                    // ponteiro auxiliar para percorrer e acessar cada vértice adjacente a um dado vértice

    /*Inicialização*/
    for(u = 0; u < TAM; u++) {          // Para cada u pertencente ao conjunto de vértices
        if (u != v0) {                  // excluindo-se o vértice de origem
            c[u] = 'b';                     // pinte-o de branco - ainda não visitado
            d[u] = 100;                     // distância desconhecida
            p[u] = -1;                      // predecessor desconhecido
        }
    }

    c[v0] = 'c';                        //pintura de cinza, pois está sendo visitado;
    d[v0] = 0;                          //distância do vértice a ele mesmo
    p[v0] = -1;                         //-1 indica que não tem predecessor
    inicializarFila(&Q);                //fila que guarda os vértices acessíves a partir de v0. Como se trata de una fila,
    enfileirar(&Q, v0);                 //  o primeiro a entrar será o primeiro a ser explorado

    while (!filaVazia(&Q)) {            //enquanto a fila não está vazia
        u = desenfileirar(&Q);          //acesso ao primeiro vértice (u) da fila
        uAdj = &G[u];                   //facilitando o acesso, através de um auxiliar, à lista de adjacências de u
        for(v = uAdj->primeiro; v != NULL; v = v->proxAdj) {    //laço para acessar todos os vértices (v) adjacentes a u
            if (c[v->vertice] == 'b') {                         //condição para não visitar vértices que já estão na fila, isto é, aqueles que talvez já tenham sido acessados através de outro vértice.
                c[v->vertice] = 'c';                            //coloração que indica que ele será enfileirado
                p[v->vertice] = u;                              //registra o antecessor de v
                d[v->vertice] = d[u] + 1;                       //registra a distância de v0 a v
                enfileirar(&Q, v->vertice);                     //enfileirando v
            }
        }
        c[u] = 'p';                                     //vértice visitado. Em outras palavras, todos os seus adjcentes foram colocados na fila, para serem visitados
        printf("[(%d), %d, %2d]\n", u, d[u], p[u]);
    }
    finalizarFila(&Q);                                  //garantia de esvaziamento da fila
}
