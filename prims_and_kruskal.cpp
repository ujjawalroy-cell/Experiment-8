#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 9999

struct Edge {
    int u, v, weight;
};

// ---------- PRIM'S ALGORITHM ----------
void prim(int graph[MAX][MAX], int n) {
    int visited[MAX] = {0};
    int edges = 0;
    int total = 0;

    visited[0] = 1;

    printf("\nPrim's MST:\n");

    while (edges < n - 1) {
        int min = INF;
        int u = -1, v = -1;

        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                for (int j = 0; j < n; j++) {
                    if (!visited[j] && graph[i][j] != 0 &&
                        graph[i][j] < min) {

                        min = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u == -1)
            break;

        printf("%c - %c : %d\n",
               'A' + u, 'A' + v, min);

        total += min;
        visited[v] = 1;
        edges++;
    }

    printf("Total MST Weight = %d\n", total);
}

int parent[MAX];

int find(int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = find(parent[x]);
}

void unionSet(int a, int b) {
    a = find(a);
    b = find(b);

    parent[a] = b;
}


// ---------- KRUSKAL'S ALGORITHM ----------

void kruskal(struct Edge edges[], int V, int E) {

    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {

            if (edges[j].weight > edges[j + 1].weight) {

                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int count = 0;
    int total = 0;

    printf("\nKruskal's MST:\n");

    for (int i = 0; i < E && count < V - 1; i++) {

        int u = edges[i].u;
        int v = edges[i].v;

        if (find(u) != find(v)) {

            printf("%c - %c : %d\n",
                   'A' + u,
                   'A' + v,
                   edges[i].weight);

            total += edges[i].weight;

            unionSet(u, v);
            count++;
        }
    }

    printf("Total MST Weight = %d\n", total);
}


int main() {

    int V = 5;

    int graph[MAX][MAX] = {0};

    // A-B = 2
    graph[0][1] = graph[1][0] = 2;

    // A-C = 6
    graph[0][2] = graph[2][0] = 6;

    // A-D = 5
    graph[0][3] = graph[3][0] = 5;

    // B-D = 3
    graph[1][3] = graph[3][1] = 3;

    // C-D = 1
    graph[2][3] = graph[3][2] = 1;

    // D-E = 4
    graph[3][4] = graph[4][3] = 4;

    // C-E = 7
    graph[2][4] = graph[4][2] = 7;


    // Edges for Kruskal
    struct Edge edges[] = {
        {0, 1, 2},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 3},
        {2, 3, 1},
        {3, 4, 4},
        {2, 4, 7}
    };

    int E = 7;

    prim(graph, V);

    kruskal(edges, V, E);

    return 0;
}
