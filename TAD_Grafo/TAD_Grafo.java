
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Scanner;
import sun.misc.Queue;

public class Grafo {

	private int n; // número de vértices
	private LinkedList<Integer> adj[];

	/* Útil para a BFS e DFS */
	private char[] cor; // cor
	private int[] d; // distância da origem
	private int[] p; // predecessor

	/* Útil para a DFS */
	private int tempo;
	private int[][] temposDF; // tempos de descoberta[][0] e de finalização[][1] da visita do vértice

	public Grafo(int n) {
		this.n = n;
		adj = new LinkedList[n];
		for (int i = 0; i < n; i++)
			adj[i] = new LinkedList<>();
		cor = new char[n];
		d = new int[n];
		p = new int[n];
		tempo = 0;
		temposDF = new int[n][2];
	}

	// Adiciona aresta não direcionada (u,v)
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

	public void BFS(int v0) throws InterruptedException {

		int u;

		Queue<Integer> F = new Queue<>();

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
		F.enqueue(v0);

		while (!F.isEmpty()) {
			u = F.dequeue();
			Iterator<Integer> i = adj[u].listIterator();
			while (i.hasNext()) {
				int v = i.next();
				if (cor[v] == 'b') {
					cor[v] = 'c';
					p[v] = u;
					d[v] = d[u] + 1;
					F.enqueue(v);
				}
			}
			cor[u] = 'p';
			System.out.printf("[(%d), %d, %2d]\n", u, d[u], p[u]);
		}
	}

	/*
	 * public void DFS(int v0) { int u; for (u = 0; u < n; u++) { cor[u] = 'b'; p[u]
	 * = -1; } tempo = 0; for (u = 0; u < n; u++) DFS_visita(u); }
	 * 
	 * private void DFS_visita(int u) {
	 * 
	 * cor[u] = 'c'; tempo++; temposDF[u][0] = tempo;
	 * 
	 * Iterator<Integer> i = adj[u].listIterator(); while (i.hasNext()) { int v =
	 * i.next(); if (cor[v] == 'b') { cor[v] = 'c'; DFS_visita(v); } } cor[u] = 'p';
	 * tempo++; temposDF[u][1] = tempo; System.out.printf("[(%d), %d, %d]\n", u,
	 * temposDF[u][0], temposDF[u][1]); }
	 */

	public static void main(String[] args) throws InterruptedException {

		Scanner sc = new Scanner(System.in);

		int n = 6;
		Grafo G = new Grafo(n);

		G.adicionaAresta(0, 2);
		G.adicionaAresta(0, 1);
		G.adicionaAresta(2, 3);
		G.adicionaAresta(2, 1);
		G.adicionaAresta(3, 4);
		G.adicionaAresta(3, 5);
		G.adicionaAresta(4, 5);

		for (int i = 0; i < n; i++)
			System.out.println("[" + i + "] --> " + G.adj[i]);

		System.out.printf("BFS(0-%d): ", n - 1);
		int v0 = sc.nextInt();
		System.out.println("[(v), d,  p]");
		G.BFS(v0);

		sc.close();
	}

}
