package application;

import entities.Graph;
import entities.Vertex;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Locale;

public class App {
    
    public static void main(String[] args) {
        
        Locale.setDefault(Locale.US);
        
        String path = "grafos/grafo6-bellmanford.txt";
        
        try {
            
            Graph G = graphMaker(path);
            
            G.printAdjList();
            System.out.println("");
            System.out.println(G.BellmanFordAlg(G.searchVertex(new Vertex('A')), G.searchVertex(new Vertex('F'))));
            System.out.println("");
            
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
         
    }
    
    
    
    /*Método que constrói grafo a partir de um arquivo .txt */
    public static Graph graphMaker(String path) throws IOException {
        
        BufferedReader br = new BufferedReader(new FileReader(path));
        
        Graph G = new Graph();
        
        String line = br.readLine();
        while (line != null) {
            String[] fields = line.split(" ");
            Vertex u = new Vertex(fields[0].charAt(0));
            G.addVertex(u);
            if (fields.length == 3) {
                Vertex v = new Vertex(fields[1].charAt(0));
                double w = Double.valueOf(fields[2]);
                G.addVertex(v);
                G.addEdge(u, v, w, false);
            }
            line = br.readLine();
        }        
        return G;
    }


}