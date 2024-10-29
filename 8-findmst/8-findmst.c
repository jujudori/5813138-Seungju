#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

void set_init(int n) {

    if (n > MAX_VERTICES) { return;  }
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}
int set_find(int curr)
{
    if (curr < 0 || curr >= MAX_VERTICES) {
        return -1; 
    }

    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1) {
        curr = parent[curr];
    }
    return curr;
}

void set_union(int a, int b)
{
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

struct Edge
{
    int start, end, weight;
};

typedef struct GraphType
{
    int n; 
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

void graph_init(GraphType* g)
{
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++)
    {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

void insert_edge(GraphType* g, int start, int end, int w)
{
    if (g->n < 2 * MAX_VERTICES) { 
        g->edges[g->n].start = start;
        g->edges[g->n].end = end;
        g->edges[g->n].weight = w;
        g->n++;
    }
    else {
        printf("Error: Maximum edges exceeded.\n");
    }
}
int compare(const void* a, const void* b)
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}


void QuickKruskal(GraphType* g)
{
    int edge_accepted = 0;	               	
    int uset, vset;			          
    struct Edge e;

    set_init(MAX_VERTICES); 
    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    printf("Quick Based kruskal  \n");
    int i = 0;
    while (edge_accepted < (g->n - 1) && i < g->n) 
    {
        e = g->edges[i];
        uset = set_find(e.start);	       
        vset = set_find(e.end);		        
        if (uset != vset)                  
        {
            printf("edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);	       
        }
        i++;
    }
}

typedef struct MinHeap {
    struct Edge* edges;
    int size;
} MinHeap;

void init_min_heap(MinHeap* h, struct Edge edges[], int edge_count) {//최소힙 처음 값 설정
    h->edges = (struct Edge*)malloc(edge_count * sizeof(struct Edge));
    for (int i = 0; i < edge_count; i++) {
        h->edges[i] = edges[i];
    }
    h->size = edge_count;
}

void minHeap_sort(MinHeap* h, int i) {//최소힙기반 정렬 
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->edges[left].weight < h->edges[smallest].weight)
        smallest = left;
    if (right < h->size && h->edges[right].weight < h->edges[smallest].weight)
        smallest = right;
    if (smallest != i) {
        struct Edge temp = h->edges[i];
        h->edges[i] = h->edges[smallest];
        h->edges[smallest] = temp;
        minHeap_sort(h, smallest);
    }
}

struct Edge extract_min(MinHeap* h) {
    struct Edge min = h->edges[0];
    h->edges[0] = h->edges[--(h->size)];
    minHeap_sort(h, 0);// 루트로 시작해서 재정렬하도록 minheap sort 호출
    return min;//최소값 반환
}

void build_min_heap(MinHeap* h) {
    for (int i = h->size / 2 - 1; i >= 0; i--) {
        minHeap_sort(h, i); //minheap기반 정렬
    }
}

void MinHeapKruskal(GraphType* g, int vertex_count) {
    MinHeap heap;
    init_min_heap(&heap, g->edges, g->n);
    build_min_heap(&heap);

    int edge_accepted = 0;
    set_init(vertex_count);

    printf("MinHeap Based Kruskal\n");
    while (edge_accepted < (vertex_count - 1) && heap.size > 0) {
        struct Edge e = extract_min(&heap);//최소값이 정점이 됨
        int uset = set_find(e.start);
        int vset = set_find(e.end);
        if (uset != vset) {
            printf("edge (%d, %d) selected %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
    }

    free(heap.edges);
}


GraphType* GenerateGraph(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);

    return g;
}

int main(void)
{
    GraphType* g;
    g = GenerateGraph();
    QuickKruskal(g); 
    MinHeapKruskal(g, 11);

    free(g);
    return 0;
}
