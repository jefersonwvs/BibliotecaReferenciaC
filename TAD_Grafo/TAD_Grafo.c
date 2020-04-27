#include <stdio.h>
#include <stdlib.h>
#include "TAD_ListaDinamica.c"
#include "TAD_FilaDinamica.c"

/*Tipo estruturado para vértices de um grafo.*/
struct vertice {
    Lista listAdj; // lista de adjacência do vértice
    /* Propriedades usadas somente em algoritmos de busca */
    char cor;
    int d;  // distância da origem
    int p; // rotulo do predecessor
};
typedef struct vertice Vertice;

/*Tipo estruturado para um Grafo representado com listas */
struct grafo {
    Vertice* V; // Vetor de vértices
    int TAM;    // quantidade de vértices do grafo
};
typedef struct grafo GrafoL; //Grafo como lista de Adjacencias

typedef int** GrafoM;   //Grafo como matriz de Adjac�ncias

int insereAresta(Lista*, int);
int removeAresta(Lista*, int);
void BFS(GrafoL*, int);
void finalizaListaAdj(Lista*);

int main()
{
    GrafoL Glista;
    GrafoM Gmatriz;

    int TAM, i, j, v0;

    TAM = 6;

    /* Inicialização do grafo representado por lista */
    Glista.V = (Vertice*)malloc(TAM*sizeof(Vertice)); // alocando o vetor de vertices do grafo
    Glista.TAM = TAM;   // guardando o tamanho para não ser necessário passá-lo como argumento em funções e procedimentos
    for (i = 0; i < TAM; i++)
        inicializarListaAdj(&(Glista.V[i].listAdj));    // inicializando a lista de adjacências de cada vértice


    /* Inicialização do grafo representado por matriz */
    Gmatriz = (int**)malloc(TAM*sizeof(int*));
    for (i = 0; i < TAM; i++)
        Gmatriz[i] = (int*)malloc(TAM*sizeof(int));


    /* Inserindo as ligações entre os vértices. Em outras palavras, inserindo as arestas */
    insereAresta(&Glista.V[0].listAdj, 1);
    Gmatriz[0][1] = 1;
    insereAresta(&Glista.V[0].listAdj, 2);
    Gmatriz[0][2] = 1;

    insereAresta(&Glista.V[1].listAdj, 0);
    Gmatriz[1][0] = 1;
    insereAresta(&Glista.V[1].listAdj, 2);
    Gmatriz[1][2] = 1;

    insereAresta(&Glista.V[2].listAdj, 0);
    Gmatriz[2][0] = 1;
    insereAresta(&Glista.V[2].listAdj, 1);
    Gmatriz[2][1] = 1;
    insereAresta(&Glista.V[2].listAdj, 3);
    Gmatriz[2][3] = 1;

    insereAresta(&Glista.V[3].listAdj, 2);
    Gmatriz[3][2] = 1;
    insereAresta(&Glista.V[3].listAdj, 4);
    Gmatriz[3][4] = 1;
    insereAresta(&Glista.V[3].listAdj, 5);
    Gmatriz[3][5] = 1;

    insereAresta(&Glista.V[4].listAdj, 3);
    Gmatriz[4][3] = 1;
    insereAresta(&Glista.V[4].listAdj, 5);
    Gmatriz[4][5] = 1;

    insereAresta(&Glista.V[5].listAdj, 3);
    Gmatriz[5][3] = 1;
    insereAresta(&Glista.V[5].listAdj, 4);
    Gmatriz[5][4] = 1;


    /* Imprimindo o grafo representado por lista */
    printf("Lista de Adjacencias do grafo G: \n");
    for(i = 0; i < TAM; i++) {
        printf("[%d]---", i);
        imprimeListaAdj(&Glista.V[i].listAdj);
    }

    /* Imprimindo o grafo representado por matriz */
    printf("\nMatriz de Adjacencias do grafo G: \n");
    for(i = 0; i < TAM; i++) {
        for(j = 0; j < TAM; j++) {
            if (Gmatriz[i][j] != 1)
                Gmatriz[i][j] = 0;
            printf("%d ", Gmatriz[i][j]);
        }
        printf("\n");
    }


    /* Execução do algoritmo BFS*/
    printf("\nBFS - Breadth-First Search (Busca em Largura): \n");
    printf("Digite o vertice de origem para a BFS (0 - %d): ", TAM-1);
    scanf("%d", &v0);
    printf("  v: vertice\n");
    printf("  d: distancia da origem\n");
    printf("  p: predecessor\n");
    printf("[(v), d,  p]\n");
    BFS(&Glista, v0);
    imprimeCaminho(&Glista, 3, 1);


    /* Finalizando o grafo representado por matriz */
    for (i = 0; i < TAM; i++)
        free(Gmatriz[i]);
    free(Gmatriz);

    /* Finalizando o grafo representado por lista */
    for(i = 0; i < TAM; i++)
        finalizaListaAdj(&Glista.V[i].listAdj);
    free(Glista.V);

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
            if (L->primeiro->rot > novo) {
                novoAdjacente->proxAdj = L->primeiro;
                L->primeiro = novoAdjacente;
            } else {
                if(L->ultimo->rot < novo) {
                    L->ultimo->proxAdj = novoAdjacente;
                    L->ultimo = novoAdjacente;
                } else {
                    ant = aux = L->primeiro;
                    while (aux) {
                        if (aux->rot > novo)
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
    if (aux->rot == x) {
        L->primeiro = L->primeiro->proxAdj;
    } else {
        ant = aux;
        while(aux) {
            if(aux->rot == x)
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
        removeAresta(L, L->primeiro->rot);
}

/*
    DESCRICAO
    Percurso em grafo, que, partindo de um dado v�rtice, acessa os demais.
    Baseado na colora��o:
        - Branco (b): v�rtice ainda n�o visitado
        - Cinza (c): v�rtice sendo visitado, isto �, acessando seus v�rtices adjacentes
        - Preto (p): v�rtice completamente visitado
    PARAM�TROS
        G[]=vetor de v�rtices e suas respectivas listas de adjac�ncias
        v0=v�rtice de origem
*/
void BFS(GrafoL* G, int v0) {

    int u; // índice de cada vértice do Grafo. Exemplo: Dado o conjunto de vertices V = {v(u) | u = 0..3} = {v(0), v(1), v(2), v(3)}

    Fila Q; // fila para armazenar e ordenar a maneira de exploracao dos vertices do grafo

    Lista *uAdj; // ponteiro auxiliar para acessar sem complicacoes, iteracao a iteracao, a lista de adjacencias de cada vertice
    adjacente *vPtr;   // ponteiro auxiliar para percorrer a lista de adjacencias de cada vertice

    int v; // índice de cada vértice adjacente a u.

    // Inicializacao
    for(u = 0; u < G->TAM; u++) {          // Para cada u pertencente ao conjunto de vertices
        if (u != v0) {                  // excluindo-se o vertice de origem
            G->V[u].cor = 'b';                     // pinte-o de branco - ainda nao visitado
            G->V[u].d = 100;                     // distancia desconhecida (para Dijkstra)
            G->V[u].p= -1;                      // predecessor desconhecido
        }
    }

    G->V[v0].cor = 'c';                        //pintura de cinza, pois esta sendo visitado;
    G->V[v0].d = 0;                          //distancia do vertice a ele mesmo
    G->V[v0].p = -1;                         //-1 indica que nao tem predecessor
    inicializarFila(&Q);                //fila que guarda os vertices acessives a partir de v0. Como se trata de una fila,
    enfileirar(&Q, v0);                 //  o primeiro a entrar sera o primeiro a ser explorado

    while (!filaVazia(&Q)) {            //enquanto a fila nao esta vazia
        u = desenfileirar(&Q);          //acesso ao primeiro vertice (u) da fila
        uAdj = &(G->V[u].listAdj);                   //facilitando o acesso, atraves de um auxiliar, a lista de adjacencias de u
        for(vPtr = uAdj->primeiro; vPtr != NULL; vPtr = vPtr->proxAdj) {    //laco para acessar todos os v�rtices (v) adjacentes a u
            v = vPtr->rot;                                      //para ficar mais legivel.
            if (G->V[v].cor == 'b') {                         //condicao para nao visitar vertices que ja estao na fila, isto e, aqueles que talvez ja tenham sido acessados atraves de outro vertice.
                G->V[v].cor = 'c';                            //coloracao que indica que ele será enfileirado
                G->V[v].p = u;                              //registra o antecessor de v
                G->V[v].d = G->V[u].d + 1;                       //registra a dist�ncia de v0 a v
                enfileirar(&Q, v);                     //enfileirando v
            }
        }
        G->V[u].cor = 'p';                                     //v�rtice visitado. Em outras palavras, todos os seus adjcentes foram colocados na fila, para serem visitados
        printf("[(%d), %d, %2d]\n", u, G->V[u].d, G->V[u].p);
    }
    finalizarFila(&Q);                                  //garantia de esvaziamento da fila
}

void imprimeCaminho(GrafoL* G, int v0, int vD) {
    if (v0 == vD)
        printf("%d", v0);
    else {
        if (G->V[vD].p == -1)
            printf("Nao existe caminho de %d para %d\n", v0, vD);
        else {
            imprimeCaminho(G, v0, G->V[vD].p);
            printf("-%d", vD);
        }
    }
}
