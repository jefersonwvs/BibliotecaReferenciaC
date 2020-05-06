package main;

import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;

public class Grafo {

    /* Grafo representado como lista de adjacências */
    int n;
    LinkedList<Integer> adj[];

    /* Útil para a BFS e DFS */
    char[] cor; // cor
    int[] d; // distância da origem
    int[] p; // predecessor

    /* Útil para a DFS */
    int tempo; // marcador
    int[][] d_f; // tempos de descoberta[][0] e de finalização[][1] da visita do vértice
    
    /* Útil para pontes */
    int[] low;

    /*
     *
     * TAD
     *
     */
    Grafo(int n) {
	this.n = n;
	adj = new LinkedList[n];
	for (int i = 0; i < n; i++)
	    adj[i] = new LinkedList<>();
	cor = new char[n];
	d = new int[n];
	p = new int[n];
	tempo = 0;
	d_f = new int[n][2];
	low = new int[n];
    }
    
    public void adicionaAresta(int u, int v) {
	if (!adj[u].contains(v)) {
	    adj[u].add(v);
	    adj[v].add(u);
	    /* Mantém as listas de adjacências ordenadas lexicograficamente */
	    Collections.sort(adj[u]);
	    Collections.sort(adj[v]);
	}
    }

    public void removeAresta(int u, int v) {
	if (adj[u].contains(v)) {
	    adj[u].remove(v);
	    adj[v].remove(u);
	}
    }
    
    public void imprimeGrafo() {
	for(int i = 0; i < n; i++)
	    System.out.printf("[%d] ----> %s\n", i, adj[i]);
    }

    /* 
     *
     * Algoritmos em Grafos 
     *
     */
    void BFS(int v0) throws InterruptedException {

	int u;
	LinkedList<Integer> F = new LinkedList<>(); // Fila

	for (u = 0; u < n; u++) {
	    if (u != v0) {
		cor[u] = 'b';
		d[u] = 100; // para Dijkstra
		p[u] = -1;
	    }
	}

	cor[v0] = 'c';
	d[v0] = 0;
	p[v0] = -1; // não existe
	F.add(v0);

	while (!F.isEmpty()) {
	    u = F.poll();
	    Iterator<Integer> i = adj[u].listIterator();
	    while (i.hasNext()) {
		int v = i.next();
		if (cor[v] == 'b') {
		    cor[v] = 'c';
		    p[v] = u;
		    d[v] = d[u] + 1;
		    F.add(v);
		}
	    }
	    cor[u] = 'p';
	    System.out.printf("[(%d), %d, %2d]\n", u, d[u], p[u]);
	}
    }
    
    void DFS() {
	
	int u;
	
	for (u = 0; u < n; u++) {
	    cor[u] = 'b';
	    p[u] = -1;
	}
	
	tempo = 0;
	for (u = 0; u < n; u++) 
	    if (cor[u] == 'b')
		DFS_visita(u);
	
    }
    
    private void DFS_visita(int u) {
	
	cor[u] = 'c';
	tempo++;
	d_f[u][0] = tempo;  // tempo de descoberta
	
	Iterator<Integer> i = adj[u].listIterator();
	while(i.hasNext()) {
	    int v = i.next();
	    if (cor[v] == 'b') {
		p[v] = u;
		DFS_visita(v);
	    }
	}
	cor[u] = 'p';
	tempo++;
	d_f[u][1] = tempo;
	System.out.printf("%d(%d,%d)\n", u, d_f[u][0], d_f[u][1]);
    }
    
    // pontes() == DFS()
    void pontes() {
	
	int u;
	
	for (u = 0; u < n; u++) {
	    cor[u] = 'b';
	    p[u] = -1;
	}
	
	tempo = 0;
	for (u = 0; u < n; u++) 
	    if (cor[u] == 'b')
		pontesVisita(u);
	
    }
    
    private void pontesVisita(int u) {
	
	cor[u] = 'c';
	tempo++;
	d_f[u][0] = tempo;  // tempo de descoberta
	low[u] = tempo;
	
	Iterator<Integer> i = adj[u].listIterator();
	while(i.hasNext()) {
	    int v = i.next();
	    if (cor[v] == 'b') {
		p[v] = u; // pai (ou predecessor) de v
		pontesVisita(v);
		
		low[u] = Math.min(low[u], low[v]);
		
		if (low[v] > d_f[u][0])
		    System.out.print(u + "-" + v + "  ");
	    } else 
		if (v != p[u])
		    low[u] = Math.min(low[u], d_f[v][0]);
	}
    }

}
