#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define MAX_ELEMENT 100
#define INF 1000000

typedef struct {
    int number;
    int weight;
} element;

typedef struct DListNode {
    element vertex;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

typedef struct {
    int num_of_vertex;
    int num_of_edge;
    DListNode adj_list[MAX_VERTICES];
} GraphListType;

typedef struct {
    int key;
    int start;
} heap_element;

typedef struct {
    heap_element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int found_sequence[MAX_VERTICES];  // 방문 순서 기록용 배열
int sequence_idx = 0;

void found_order() {
    printf("Found Order: ");
    for (int i = 1; i < 11; i++) {
        printf("%d ", found_sequence[i] + 1);
    }
    printf("\n");
}

void found_list_order() {
    printf("Found Order: ");
    for (int i = 11; i < sequence_idx; i++) {
        printf("%d ", found_sequence[i] + 1);
    }
    printf("\n");
}

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;

    min = INF;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

void print_status(GraphType* g) {
    printf("distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    printf("\n");
    printf("found:    ");
    for (int i = 0; i < g->n; i++)
        printf("%2d ", found[i]);
    printf("\n\n");
}

void shortest_path_matrix(GraphType* g, int start) {
    int i, u, w;

    // distance[]와 found[] 배열 초기화
    for (i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }

    // 시작 노드의 거리 초기화
    distance[start] = 0;
    found[start] = TRUE;
    found_sequence[sequence_idx++] = start;

    print_status(g);  // 초기 상태 출력

    // Dijkstra 알고리즘 반복문
    for (i = 0; i < g->n - 1; i++) {
        // 시작 노드를 기준으로 거리 배열 업데이트
        for (w = 0; w < g->n; w++) {
            if (!found[w]) {
                distance[w] = g->weight[start][w];
            }
        }

        // 아직 방문하지 않은 노드 중 가장 작은 거리를 가진 노드 선택
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        found_sequence[sequence_idx++] = u;

        // 선택된 노드 u를 기준으로 인접 노드들의 거리 업데이트
        for (w = 0; w < g->n; w++) {
            if (!found[w] && distance[u] + g->weight[u][w] < distance[w]) {
                distance[w] = distance[u] + g->weight[u][w];
            }
        }

        print_status(g);  // 각 주요 업데이트 후 상태 출력
    }

    found_order();  // 방문한 노드들의 순서 출력
}

int dist[MAX_VERTICES], prev[MAX_VERTICES];
int found[MAX_VERTICES];

void init_Dlist(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

void insert_Dlist(DListNode* before, element data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    if (!newnode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newnode->vertex.number = data.number;
    newnode->vertex.weight = data.weight;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

HeapType* create_heap() {
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    if (!h) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    h->heap_size = 0;
    return h;
}

void init_heap(HeapType* h) {
    h->heap_size = 0;
}

void destroy_heap(HeapType* h) {
    free(h);
}

void insert_min_heap(HeapType* h, heap_element item) {
    int i = ++h->heap_size;
    while (i > 1 && h->heap[i / 2].key > item.key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

heap_element delete_min_heap(HeapType* h) {
    heap_element item = h->heap[1], temp = h->heap[h->heap_size--];
    int parent = 1, child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
            child++;
        if (temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

GraphListType* create_list_graph() {
    GraphListType* g = (GraphListType*)malloc(sizeof(GraphListType));
    if (!g) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    g->num_of_vertex = g->num_of_edge = 0;
    return g;
}

void init_list_graph(GraphListType* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        init_Dlist(&(g->adj_list[i]));
        g->adj_list[i].vertex.number = -1;
    }
}

void insert_vertex_list_graph(GraphListType* g, int v) {
    if (g->adj_list[v].vertex.number == -1) {
        g->adj_list[v].vertex.number = v;
        g->num_of_vertex++;
    }
}

void insert_edge_list_graph(GraphListType* g, int s, int e, int w) {
    insert_Dlist(&(g->adj_list[s]), (element) { e, w });
    insert_Dlist(&(g->adj_list[e]), (element) { s, w });
    g->num_of_edge++;
}

void print_dijkstra_status(GraphListType* g) {
    printf("distance: ");
    for (int i = 0; i < g->num_of_vertex; i++) {
        if (dist[i] == INF)
            printf(" * ");
        else
            printf("%2d ", dist[i]);
    }
    printf("\nfound:    ");
    for (int i = 0; i < g->num_of_vertex; i++) {
        printf("%2d ", found[i]);
    }
    printf("\n\n");
}


void dijkstra_sp(GraphListType* g, int start) {
    HeapType* h = create_heap();
    init_heap(h);

    for (int i = 0; i < g->num_of_vertex; i++) {
        dist[i] = INF;
        prev[i] = -1;
        found[i] = FALSE;
    }
    dist[start] = 0;
    insert_min_heap(h, (heap_element) { .key = 0, .start = start });

    while (h->heap_size > 0) {
        heap_element element = delete_min_heap(h);
        int u = element.start;

        if (found[u]) continue;
        found[u] = TRUE;
        found_sequence[sequence_idx++] = u;

        print_dijkstra_status(g);

        for (DListNode* p = g->adj_list[u].rlink; p != &(g->adj_list[u]); p = p->rlink) {
            int v = p->vertex.number;
            int weight = p->vertex.weight;

            if (!found[v] && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                insert_min_heap(h, (heap_element) { .key = dist[v], .start = v });
            }
        }
    }

    found_list_order();
    destroy_heap(h);
}

int main(void) {
    GraphListType* graph = create_list_graph();
    init_list_graph(graph);

    GraphType g = { 10,
    {{ 0,  3,  INF, INF, INF,   11,  12, INF,INF, INF},
    { 3,  0,  5, 4, 1,  7,  8, INF,INF, INF},
{ INF,  5,  0, 2,INF,   INF,  6, 5,INF, INF },
    { INF,  4,  2, 0, 13,  INF,  INF, 14,INF,16 },
{ INF,  1,  INF, 13, 0,   9,  INF, INF,18, 17 },
{ 1,  7,  INF, INF, 9,   0,  INF, INF,INF, INF},
{ 12, 8 , 6, INF, INF,  INF,  0,13,INF, INF},
{ INF,  INF,  5, 14, INF,   INF,  13, 0,INF, 15 },
{ INF,  INF,  INF, INF, 18,  INF,  INF, INF,0, 10, },
{ INF,  INF,  INF, 16, 17,  INF,  INF, 15,10, 0}}
    };
    printf("행렬 기반 다익스트라 \n");
    shortest_path_martix(&g, 0);


    for (int i = 0; i < 10; i++) {
        insert_vertex_list_graph(graph, i);
    }

    insert_edge_list_graph(graph, 0, 1, 3);
    insert_edge_list_graph(graph, 0, 5, 11);
    insert_edge_list_graph(graph, 0, 6, 12);
    insert_edge_list_graph(graph, 1, 2, 5);
    insert_edge_list_graph(graph, 1, 3, 4);
    insert_edge_list_graph(graph, 1, 4, 1);
    insert_edge_list_graph(graph, 1, 5, 7);
    insert_edge_list_graph(graph, 1, 6, 8);
    insert_edge_list_graph(graph, 2, 3, 2);
    insert_edge_list_graph(graph, 2, 6, 6);
    insert_edge_list_graph(graph, 2, 7, 5);
    insert_edge_list_graph(graph, 3, 4, 13);
    insert_edge_list_graph(graph, 3, 7, 14);
    insert_edge_list_graph(graph, 3, 9, 16);
    insert_edge_list_graph(graph, 4, 5, 9);
    insert_edge_list_graph(graph, 4, 7, 18);
    insert_edge_list_graph(graph, 4, 8, 17);
    insert_edge_list_graph(graph, 5, 8, 9);
    insert_edge_list_graph(graph, 6, 7, 13);
    insert_edge_list_graph(graph, 7, 8, 15);
    insert_edge_list_graph(graph, 8, 9, 10);

    printf("\nMin-heap기반 연결리스트 다익스트라\n");
    dijkstra_sp(graph, 0);

    return 0;
}
