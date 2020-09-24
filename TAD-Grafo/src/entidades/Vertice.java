package entidades;

import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

public class Vertice implements Comparable<Vertice> {
    
    Character rotulo;
    List<Aresta> adj;
    
    /* para Dijkstra*/
    double d; // d = distância (estimativa)
    Vertice p; // p = predecessor
    
    public Vertice() {
        
    }
    
    public Vertice(Character rotulo) {
        this.rotulo = rotulo;
        adj = new LinkedList<>();
    }

    public Character getRotulo() {
        return rotulo;
    }

    public List<Aresta> getAdj() {
        return adj;
    }

    public void setEstimativa(double estimativa) {
        this.d = estimativa;
    }

    public void setPai(Vertice pai) {
        this.p = pai;
    }

    public double getEstimativa() {
        return d;
    }
    
    
    @Override
    public int compareTo(Vertice t) {
        if (this.rotulo < t.rotulo)
            return -1;
        else {
            if (Objects.equals(this.rotulo, t.rotulo))
                return 0;
            return 1;
        }
    }

    @Override
    public String toString() {
        return String.valueOf(rotulo);
    }

    @Override
    public int hashCode() {
        int hash = 5;
        hash = 29 * hash + Objects.hashCode(this.rotulo);
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
        final Vertice other = (Vertice) obj;
        if (!Objects.equals(this.rotulo, other.rotulo)) {
            return false;
        }
        return true;
    }
    
}
