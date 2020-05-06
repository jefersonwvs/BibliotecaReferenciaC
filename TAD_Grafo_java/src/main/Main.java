package main;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws InterruptedException {

	Scanner sc = new Scanner(System.in);

	int n = 6;
	Grafo g1 = new Grafo(n);

	g1.adicionaAresta(0, 2);
	g1.adicionaAresta(0, 1);
	g1.adicionaAresta(2, 3);
	g1.adicionaAresta(2, 1);
	g1.adicionaAresta(3, 4);
	g1.adicionaAresta(3, 5);
	g1.adicionaAresta(4, 5);
	System.out.println("Lista de adjacências do grafo g1: ");
	g1.imprimeGrafo();
	
	System.out.printf("\nBFS do grafo g1, iniciando no vértice (0-%d): ", n - 1);
	int v0 = sc.nextInt();
	System.out.println("[(v), d,  p]");
	g1.BFS(v0);
	
	System.out.println("\nDFS do grafo g1: ");
	g1.DFS();
	
	System.out.println("");
	System.out.print("Pontes no grafo g1: ");
	g1.pontes();
	
	Grafo g2 = new Grafo(4);
	g2.adicionaAresta(0, 1);
	g2.adicionaAresta(0, 2);
	g2.adicionaAresta(1, 2);
	g2.adicionaAresta(2, 3);
	System.out.println("");
	System.out.print("Pontes no grafo g2: ");
	g2.pontes();
	
	Grafo g3 = new Grafo(6);
	g3.adicionaAresta(0, 2);
	g3.adicionaAresta(0, 3);
	g3.adicionaAresta(0, 4);
	g3.adicionaAresta(4, 1);
	g3.adicionaAresta(1, 5);
	System.out.println("");
	System.out.print("Pontes no grafo g3: ");
	g3.pontes();

	sc.close();
    }

}
