package entities;

import java.util.Objects;

/* Aresta (Edge) */
public class Edge implements Comparable<Edge>{
    
    Vertex u; // extremidade inicial da aresta
    Vertex v; // extremidade final da aresta
    double w; // weight: peso (ou custo da aresta)

    public Edge(Vertex u, Vertex v, double w) {
        this.u = u;
        this.v = v;
        this.w = w;
    }
    
    
    @Override
    public String toString() {
        return v.toString() + "(" + w + ")";
    }

    @Override
    public int compareTo(Edge t) {
        if (this.v.label < t.v.label)
            return -1;
        else {
            if (Objects.equals(this.v.label, t.v.label))
                return 0;
            return 1;
        }
    }
    
}
