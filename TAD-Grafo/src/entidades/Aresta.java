package entidades;

import java.util.Objects;

public class Aresta implements Comparable<Aresta>{
    
    Vertice origem;
    Vertice destino;
    double peso;

    public Aresta() {
    }
   
    public Aresta(Vertice origem, Vertice destino, double peso) {
        this.origem = origem;
        this.destino = destino;
        this.peso = peso;
    }

    public Vertice getDestino() {
        return destino;
    } 

    public double getPeso() {
        return peso;
    }
    
    @Override
    public String toString() {
        return "(" + peso + ")"+destino.toString();
    }

    @Override
    public int compareTo(Aresta t) {
        if (this.destino.getRotulo() < t.destino.getRotulo())
            return -1;
        else {
            if (Objects.equals(this.destino.getRotulo(), t.destino.getRotulo()))
                return 0;
            return 1;
        }
    }
    
    
    
    

}
