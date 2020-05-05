import java.util.Queue;

void BFS(int v0) {

    int u;

    Queue<Integer> F = new Queue<>();

    for (u = 0; u < n; u++) {
        if (u != v0) {
            cor[u] = 'b';
            d[u] = 100;
            p[u] = -1;
        }
    }

    cor[v0] = 'c';
    d[v0] = 0;
    p[v0] = -1;
    F.enqueue(v0);

    while


}