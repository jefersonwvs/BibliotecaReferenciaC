package entities;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Graph {

    public LinkedList<Vertex> V; // V: conjunto de vértices

    public Graph() {
        V = new LinkedList<>();
    }

    /* Retorna a referência a um objeto já existente */
    public Vertex searchVertex(Vertex aux) {
        for (Vertex v : V)
            if (v.equals(aux))
                return v;
        return null;
    }

    public void addVertex(Vertex u) {
        if (!V.contains(u)) { // para não inserir vértices iguais
            V.add(u);
            Collections.sort(V); // mantém os vértices ordenados
        }
    }

    public void addEdge(Vertex u, Vertex v, double w, boolean isUndirected) {
        u = searchVertex(u);
        v = searchVertex(v);
        Edge uv = new Edge(u, v, w);
        u.adj.add(uv);
        Collections.sort(u.adj);

        if (isUndirected) { // quer dizer que é bidirecionada
            Edge vu = new Edge(v, u, w);
            v.adj.add(vu);
            Collections.sort(v.adj);
        }
    }

    public void printAdjList() {
        V.forEach((u) -> {
            System.out.println("[" + u.label + "(" + u.d + ")" + "] → " + u.adj);
        });
    }
    
    public void printVertex() {
        for (Vertex u : V)
            System.out.println("[" + u.label + "(" + u.d + ")" + "]");
    }
    
    
    /* ALGORITMOS EM GRAFOS */
    
    
    
    /* Algoritmo que inicializa os valores d e p de cada vértice, para posterior execução do Dijkstra, Bellman-Ford */
    private void initializeSingleSource(Vertex s) { // source: origem
        /* Inicialização dos vértices */
        for (Vertex v : V) {
            v.d = Double.POSITIVE_INFINITY; // setando "infinito"
            v.p = null;
        }
        s.d = 0.0;  
    }
    
    public void BFS(Vertex s) {
        
        s = searchVertex(s); // buscando referência ao objeto s do grafo
        
        initializeSingleSource(s);
        
        LinkedList<Vertex> unvisited = new LinkedList<>(); // Fila para vértices não visitados
        List<Vertex> visited = new ArrayList<>(); // vértices já visitados
        
        unvisited.addLast(s); // insere no final

        while (!unvisited.isEmpty()) {
            Vertex u = unvisited.poll(); // remove no início
            Iterator<Edge> uAdj = u.adj.iterator();
            while (uAdj.hasNext()) {
                Edge uv = uAdj.next();
                Vertex v = uv.v;
                if (!(unvisited.contains(v) || visited.contains(v))) {
                    v.d = u.d + 1;
                    v.p = u;
                    unvisited.addLast(v);
                }
            }
            System.out.println(u.label + "(" + u.d + ")");
            visited.add(u);
        }
    }
    
    /*public void DFS(Vertex s) {
        
        s = searchVertex(s); // buscando referência ao objeto s do grafo
        
        initializeSingleSource(s);
        int t = 0;
        
        LinkedList<Vertex> unvisited = new LinkedList<>(); // Pilha para vértices não visitados
        List<Vertex> visited = new ArrayList<>(); // vértices já visitados
        
        t++;
        s.dt = t;
        unvisited.push(s); // insere no topo

        while (!unvisited.isEmpty()) {
            Vertex u = unvisited.pop(); // remove do topo
            Iterator<Edge> uAdj = u.adj.iterator();
            while (uAdj.hasNext()) {
                Edge uv = uAdj.next();
                Vertex v = uv.v;
                if (!(unvisited.contains(v) || visited.contains(v))) {
                    t++;
                    v.dt = t;
                    v.p = u;
                    unvisited.push(v);
                }
            }
            t++;
            u.ft = t;
            visited.add(u);
            System.out.println(u.label + "(" + u.dt + "," + u.ft + ")");
        }
    }*/
    
    private void relax(Edge uv) {

        Vertex u = uv.u;
        Vertex v = uv.v;
        if (u.d + uv.w < v.d) { // v.d > u.d + uv.peso
            v.d = u.d + uv.w;
            v.p = u;        
        }
    }
        
    /* Algoritmo que, após o cálculo das estimativas, usando Dijkstra, Bellman-Ford etc., efetivamente
    calculará o menor caminho de um vértice origem até um vértice destino */
    private String shortestPath(Vertex t) { // Target: alvo
      
        Vertex aux = t;
        if (aux.p == null) // vD não é acessível a partir de v0
            return "";
        
        String shortestPath = "";
        while (aux.p != null) { // laço que permite construir o caminho de trás para frente
            shortestPath = String.format(" --> %s(%.1f)", aux.label.toString(), aux.d) + shortestPath;
            aux = aux.p;
        }
        shortestPath = String.format("%s(%.1f)", aux.label.toString(), aux.d) + shortestPath;
        return shortestPath;
        
    }
    
    
    /* Método que descobre o vértice com menor estimativa de custo mínimo */
    private Vertex extractMin(LinkedList<Vertex> unvisited) {
        
        Vertex u = null;
        double menorDistancia = Double.POSITIVE_INFINITY;
        for (Vertex v : unvisited) {
            if (v.d < menorDistancia) {
                menorDistancia = v.d;
                u = v;
            }
        }
        return u;
    }

    /* Algoritmo de Dijkstra: 
        para grafos:
            - Direcionados (dígrafos) ou não;
            - Apenas arestas de custo positivo.
     */
    public String DijkstraAlg(Vertex s, Vertex t) {

        LinkedList<Vertex> unvisited = new LinkedList<>();
        LinkedList<Vertex> visited = new LinkedList<>();

        initializeSingleSource(s);
        
        unvisited.addLast(s);

        while (!unvisited.isEmpty()) 
        {   
            Vertex u = extractMin(unvisited); // Descobrindo o vértice com menor estimativa 
            
            /* Fechando o vértice u, pois sua estimativa é a menor */
            unvisited.remove(u);
            visited.add(u);

            Iterator<Edge> uAdj = u.adj.iterator(); // "percorredor" de listas

            while (uAdj.hasNext()) {
                
                Edge uv = uAdj.next();
                Vertex v = uv.v;
                if (!visited.contains(v)) {
                    relax(uv);
                    if (!unvisited.contains(v)) {
                        unvisited.addLast(v);
                    }
                }
            }
        }
        
        printVertex();
        System.out.println("");
        
        return shortestPath(t);
        
    }
    
    private boolean hasNegativeWeightCycle() {
        
        LinkedList<Vertex> aux = (LinkedList<Vertex>) V.clone(); // cópia de todos os vértices, pois todos serão relaxados

        while (!aux.isEmpty()) {
            Vertex u = aux.poll();
            Iterator<Edge> uAdj = u.adj.iterator(); // "percorredor" de listas
            while (uAdj.hasNext()) {
                Edge uv = uAdj.next();
                Vertex v = uv.v;
                if (u.d + uv.w < v.d) {
                    return true;
                }
            }
        }
        return false;
    }
    
    
    /* Algoritmo de Bellman-Ford: 
        para grafos:
            - Direcionados (dígrafos);
            - Arestas de custo positivo ou negativo.
    */
    public String BellmanFordAlg(Vertex s, Vertex t) {
        
        LinkedList<Vertex> unvisited = new LinkedList<>();
        
        initializeSingleSource(s);
        
        for (int it = 1; it <= V.size()-1; it++) { // iterações ( 1...|V|-1 )
            
            unvisited = (LinkedList<Vertex>) V.clone(); // cópia de todos os vértices, pois todos serão relaxados
            
            while (!unvisited.isEmpty()) {
                
                Vertex u = unvisited.poll();
                Iterator<Edge> uAdj = u.adj.iterator(); // "percorredor" de listas
                while (uAdj.hasNext()) {
                    Edge uv = uAdj.next();
                    relax(uv);
                }
            }
            System.out.println("Iteração " + it + ":");
            printVertex();
            System.out.println("");
        }
        
        if (hasNegativeWeightCycle())
            return "Ciclo negativo encontrado!";
        
        return shortestPath(t);
    
    }
    
}
