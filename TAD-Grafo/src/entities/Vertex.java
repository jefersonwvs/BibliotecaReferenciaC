package entities;

import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

/* Vértice (Vertex) */
public class Vertex implements Comparable<Vertex> {
    
    Character label; // rótulo do vértice
    List<Edge> adj; // lista de adjacências de V
    
    /* Para cálculo de caminho mínimo */
    double d; // d = distância (estimativa de caminho mínimo)
    Vertex p; // p = predecessor
    
    /* Para DFS */
    int dt; // dt: discovered time (tempo de descoberta)
    int ft; // ft: finished time (tempo de finalização)
        
    public Vertex(Character label) {
        this.label = label;
        adj = new LinkedList<>();
    }
    
    @Override
    public int compareTo(Vertex t) {
        if (this.label < t.label)
            return -1;
        else {
            if (Objects.equals(this.label, t.label))
                return 0;
            return 1;
        }
    }

    @Override
    public String toString() {
        return String.valueOf(label);
    }

    @Override
    public int hashCode() {
        int hash = 5;
        hash = 29 * hash + Objects.hashCode(this.label);
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Vertex other = (Vertex) obj;
        return Objects.equals(this.label, other.label);
    }
    
}
