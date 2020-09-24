package entidades;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Grafo {

    public LinkedList<Vertice> V;

    public Grafo() {
        V = new LinkedList<>();
    }

    public Vertice buscaVertice(Vertice aux) {
        for (Vertice v : V)
            if (v.equals(aux))
                return v;
        return null;
    }

    public void insereVertice(Vertice u) {
        if (!V.contains(u)) { // para não inserir vértices iguais
            V.add(u);
            Collections.sort(V); // mantém os vértices ordenados
        }
    }

    public void insereAresta(Vertice u, Vertice v, double peso, boolean ehBidirecionada) {
        u = buscaVertice(u);
        v = buscaVertice(v);
        Aresta uv = new Aresta(u, v, peso);
        u.getAdj().add(uv);
        Collections.sort(u.getAdj());

        if (ehBidirecionada) {
            Aresta vu = new Aresta(v, u, peso);
            v.getAdj().add(vu);
            Collections.sort(v.getAdj());
        }
    }

    public void imprimeListaAdj() {
        for (Vertice u : V)
            System.out.println("[" + u.getRotulo() + "(" + u.d + ")" + "] → " + u.getAdj());
    }
    
    /* Algoritmo que inicializa os valores d e p de cada vértice, para posterior execução do Dijkstra, Bellman-Ford */
    private void inicializaGrafo(Vertice v0) {
        /* Inicialização dos vértices */
        for (Vertice v : V) {
            v.d = Double.POSITIVE_INFINITY; // setando "infinito"
            v.p = null;
        }
        v0.d = 0.0;  
    }
    
    private void relaxaAresta(Aresta uv) {

        Vertice u = uv.origem;
        Vertice v = uv.destino;
        if (v.d > u.d + uv.peso) {
            v.d = u.d + uv.peso;
            v.p = u;        
        }
    }
        
    /* Algoritmo que, após o cálculo das estimativas, usando Dijkstra, Bellman-Ford etc., efetivamente
    calculará o menor caminho de um vértice origem até um vértice destino */
    private String caminhoMinimo(Vertice vD) {
      
        Vertice aux = vD;
        if (aux.p == null) // vD não é acessível a partir de v0
            return "";
        
        String caminho = "";
        while (aux.p != null) { // laço que permite construir o caminho de trás para frente
            caminho = String.format(" --> %s(%.1f)", aux.rotulo.toString(), aux.d) + caminho;
            aux = aux.p;
        }
        caminho = String.format("%s(%.1f)", aux.rotulo.toString(), aux.d) + caminho;
        return caminho;
        
    }

    public void buscaEmLargura() {

        LinkedList<Vertice> abertos = new LinkedList<>(); // Fila
        abertos.addLast(V.get(0)); // insere no final
        List<Vertice> fechados = new ArrayList<>(); // já avaliados

        while (!abertos.isEmpty()) {
            Vertice u = abertos.poll(); // remove no início
            Iterator<Aresta> uAdj = u.getAdj().iterator();
            while (uAdj.hasNext()) {
                Aresta uv = uAdj.next();
                Vertice v = uv.getDestino();
                if (!abertos.contains(v) && !fechados.contains(v))
                    abertos.addLast(v);
            }
            System.out.println(u.getRotulo());
            fechados.add(u);
        }
    }

    /*Algoritmo de Dijkstra: 
        para grafos:
            - Direcionados (dígrafos) ou não;
            - Apenas arestas de custo positivo.
     */
    public String algDijkstra(Vertice v0, Vertice vD) {

        LinkedList<Vertice> abertos = new LinkedList<>();
        LinkedList<Vertice> fechados = new LinkedList<>();

        inicializaGrafo(v0);
        
        abertos.addLast(v0);

        while (!abertos.isEmpty()) 
        {   
            Vertice u = null;
            double menorDistancia = Double.POSITIVE_INFINITY;

            /* Descobrindo o vértice com menor estimativa */
            for (Vertice v : abertos) {
                if (v.d < menorDistancia) {
                    menorDistancia = v.d;
                    u = v;
                }
            }

            /* Fechando o vértice u, pois sua estimativa é a menor */
            abertos.remove(u);
            fechados.add(u);

            Iterator<Aresta> uAdj = u.getAdj().iterator(); // "percorredor" de listas

            while (uAdj.hasNext()) 
            {
                Aresta uv = uAdj.next();
                Vertice v = uv.destino;
                if (!fechados.contains(v)) {
                    relaxaAresta(uv);
                    if (!abertos.contains(v)) {
                        abertos.addLast(v);
                    }
                }
            }
        }
        
        return caminhoMinimo(vD);
        
    }
    
    private boolean temCicloNegativo() {
        
        LinkedList<Vertice> aux = (LinkedList<Vertice>) V.clone(); // cópia de todos os vértices, pois todos serão relaxados

        while (!aux.isEmpty()) {
            Vertice u = aux.poll();
            Iterator<Aresta> uAdj = u.getAdj().iterator(); // "percorredor" de listas
            while (uAdj.hasNext()) {
                Aresta uv = uAdj.next();
                Vertice v = uv.destino;
                if (u.d + uv.peso < v.d) {
                    System.out.println(u.d + " + " + uv.peso + " < " + v.d);
                    return true;
                }
            }
        }
        return false;
    }
    
    
    /*Algoritmo de Bellman-Ford: 
        para grafos:
            - Direcionados (dígrafos);
            - Arestas de custo positivo ou negativo.
     */
    public String algBellmanFord(Vertice v0, Vertice vD) {
        
        LinkedList<Vertice> abertos = new LinkedList<>();
        
        inicializaGrafo(v0);
        
        for (int it = 1; it < V.size(); it++) { // iterações
            
            abertos = (LinkedList<Vertice>) V.clone(); // cópia de todos os vértices, pois todos serão relaxados
            abertos.remove(v0); // remoção do v0 de origem
            abertos.addFirst(v0); // reinserindo de maneira que ele seja o primeiro
            
            while (!abertos.isEmpty()) {
                Vertice u = abertos.poll();
                
                Iterator<Aresta> uAdj = u.getAdj().iterator(); // "percorredor" de listas

                while (uAdj.hasNext()) {

                    Aresta uv = uAdj.next();
                    Vertice v = uv.destino;
                    relaxaAresta(uv);
                }
            }            
        }
        
        return caminhoMinimo(vD);
    
    }
    
}
