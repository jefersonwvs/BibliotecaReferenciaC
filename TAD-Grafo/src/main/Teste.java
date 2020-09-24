package main;

import entidades.Grafo;
import entidades.Vertice;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Locale;

public class Teste {
    
    public static void main(String[] args) {
        
        Locale.setDefault(Locale.US);
        
        String caminho = "grafo6-bellmanford.txt";
        
        try {
            
            Grafo G = constroiGrafo(caminho);
            
            G.imprimeListaAdj();
            System.out.println("");
            System.out.println(G.algBellmanFord(G.buscaVertice(new Vertice('A')), G.buscaVertice(new Vertice('F'))));
            G.imprimeListaAdj();
            
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
         
    }
    
    
    public static Grafo constroiGrafo(String caminho) throws IOException {
        
        BufferedReader br = new BufferedReader(new FileReader(caminho));
        
        Grafo G = new Grafo();
        
        String linha = br.readLine();
        while (linha != null) {
            String[] campos = linha.split(" ");
            Vertice u = new Vertice(campos[0].charAt(0));
            G.insereVertice(u);
            if (campos.length == 3) {
                Vertice v = new Vertice(campos[1].charAt(0));
                double peso = Double.valueOf(campos[2]);
                G.insereVertice(v);
                G.insereAresta(u, v, peso, false);
            }
            linha = br.readLine();
        }        
        return G;
    }


}