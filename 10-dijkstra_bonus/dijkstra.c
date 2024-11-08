#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define MAX_ELEMENT 100
#define INF 1000000  // ���Ѵ븦 ��Ÿ���� ��� ��

// ��� ����ü: ���� ��ȣ�� ����ġ�� ����
typedef struct {
    int number;
    int weight;
} element;

// ���� ���� ����Ʈ�� ��� ����ü
typedef struct DListNode {
    element vertex;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

// ���� ����Ʈ ����� �׷��� ����ü
typedef struct {
    int num_of_vertex;  // ���� ��
    int num_of_edge;    // ���� ��
    DListNode adj_list[MAX_VERTICES];  // ���� ����Ʈ
} GraphListType;

// �� ��� ����ü: ���ͽ�Ʈ�� �˰��򿡼� ���� �� ���
typedef struct {
    int key;
    int start;
} heap_element;

// �ּ� �� ����ü: ���ͽ�Ʈ�� �˰��� ���Ǵ� �켱���� ť
typedef struct {
    heap_element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// ��� ��� �׷��� ����ü
typedef struct GraphType {
    int n;  // ���� ��
    int weight[MAX_VERTICES][MAX_VERTICES];  // ����ġ ���
} GraphType;

int found_sequence[MAX_VERTICES];  // �湮 ���� ��Ͽ� �迭
int sequence_idx = 0;  // �湮 ���� �ε���

// �湮 ���� ��� �Լ�
void found_order() {
    printf("Found Order: ");
    for (int i = 1; i <= 10; i++) {
        printf("%d ", found_sequence[i] + 1);
    }
    printf("\n");
}

// �湮 ���� ��� �Լ� (11�� �ε��� ����)
void found_list_order() {
    printf("Found Order: ");
    for (int i = 11; i < sequence_idx; i++) {
        printf("%d ", found_sequence[i] + 1);
    }
    printf("\n");
}

int distance[MAX_VERTICES];  // �ִ� �Ÿ� ���� �迭
int found[MAX_VERTICES];  // �湮 ���� ���� �迭

// �ּ� �Ÿ��� ���� ������ �����ϴ� �Լ�
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

// ���� ���� (�Ÿ��� �湮 �迭)�� ����ϴ� �Լ�
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

// ��� ��� ���ͽ�Ʈ�� �˰���
void shortest_path_martix(GraphType* g, int start) {
    int i, u, w;

    // �ʱ�ȭ
    for (i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }

    distance[start] = 0;  // ���� ������ �Ÿ� �ʱ�ȭ
    found_sequence[sequence_idx++] = start;
    found[start] = TRUE;

    print_status(g);

    // �ִ� �Ÿ� ��� ����
    for (i = 0; i < g->n - 1; i++) {
        u = choose(distance, g->n, found);
        if (u == -1) break;

        found[u] = TRUE;
        found_sequence[sequence_idx++] = u;

        // ���� ���� ������Ʈ
        for (w = 0; w < g->n; w++) {
            if (!found[w] && g->weight[u][w] != INF && distance[u] + g->weight[u][w] < distance[w]) {
                distance[w] = distance[u] + g->weight[u][w];
            }
        }
    }

    // �ʱ�ȭ �� �ٽ� �ݺ� (�ߺ��� �ڵ�)
    for (i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
    }
    found[start] = TRUE;
    distance[start] = 0;
    found_sequence[sequence_idx++] = start;

    for (i = 0; i < g->n - 1; i++) {
        print_status(g);
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        found_sequence[sequence_idx++] = u;

        for (w = 0; w < g->n; w++) {
            if (!found[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
        }
    }
    print_status(g);
    found_order();
}

int dist[MAX_VERTICES], prev[MAX_VERTICES];  // �ִ� �Ÿ� �� ��� �迭

// ���� ���� ����Ʈ �ʱ�ȭ
void init_Dlist(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

// ���� ���� ����Ʈ ��� ����
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

// �� ���� �� �ʱ�ȭ
HeapType* create_heap() {
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    if (!h) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    h->heap_size = 0;
    return h;
}

// �� �ʱ�ȭ
void init_heap(HeapType* h) {
    h->heap_size = 0;
}

// �� �޸� ����
void destroy_heap(HeapType* h) {
    free(h);
}

// �ּ� ���� ��� ����
void insert_min_heap(HeapType* h, heap_element item) {
    int i = ++h->heap_size;
    while (i > 1 && h->heap[i / 2].key > item.key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// �ּ� ������ �ּ� ��� ���� �� ��ȯ
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

// ���� ����Ʈ ����� �׷��� ���� �� �ʱ�ȭ
GraphListType* create_list_graph() {
    GraphListType* g = (GraphListType*)malloc(sizeof(GraphListType));
    if (!g) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    g->num_of_vertex = g->num_of_edge = 0;
    return g;
}

// ���� ����Ʈ �ʱ�ȭ
void init_list_graph(GraphListType* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        init_Dlist(&(g->adj_list[i]));
        g->adj_list[i].vertex.number = -1;
    }
}

// ���� ����
void insert_vertex_list_graph(GraphListType* g, int v) {
    if (g->adj_list[v].vertex.number == -1) {
        g->adj_list[v].vertex.number = v;
        g->num_of_vertex++;
    }
}

// ���� ����
void insert_edge_list_graph(GraphListType* g, int s, int e, int w) {
    insert_Dlist(&(g->adj_list[s]), (element) { e, w });
    insert_Dlist(&(g->adj_list[e]), (element) { s, w });
    g->num_of_edge++;
}

// ���� ��� �Լ� (�Ÿ��� �湮 �迭)
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
    // �ּ� ���� �����ϰ� �ʱ�ȭ�մϴ�.
    HeapType* h = create_heap();
    init_heap(h);

    // dist[]: �� ���������� �ִ� �Ÿ��� �����ϴ� �迭
    // prev[]: �� ������ ���� ������ �����ϴ� �迭 (�ִ� ��� ������)
    // found[]: �ش� ������ �̹� ó���Ǿ����� ���θ� ��Ÿ���� �迭
    for (int i = 0; i < g->num_of_vertex; i++) {
        dist[i] = INF;         // �ʱⰪ�� ���Ѵ�� ����
        prev[i] = -1;          // ���� ������ �����Ƿ� -1�� ����
        found[i] = FALSE;      // ���� ó������ �ʾ����Ƿ� FALSE
    }

    // ���� ������ �Ÿ� �ʱ�ȭ
    dist[start] = 0;

    // ���� ������ �ּ� ���� �ֽ��ϴ�.
    insert_min_heap(h, (heap_element) { .key = 0, .start = start });

    // ���� ���� ������ ����ؼ� ó���մϴ�.
    while (h->heap_size > 0) {
        // �ּ� ������ ���� �켱������ ���� ����(�ִ� �Ÿ�) ������
        heap_element element = delete_min_heap(h);
        int u = element.start;  // ���� ����

        // �̹� ó���� �����̸� �ǳʶٱ�
        if (found[u]) continue;

        // ���� u�� ó�� �Ϸ�� ǥ��
        found[u] = TRUE;

        // ���� u�� ó���� ������� ���� (������̳� ��� Ȯ�ο�)
        found_sequence[sequence_idx++] = u;

        // ���� ���¸� ��� (������)
        print_dijkstra_status(g);

        // ���� u�� ����� ��� ���� ���� v�� ���� �Ÿ� ������Ʈ
        for (DListNode* p = g->adj_list[u].rlink; p != &(g->adj_list[u]); p = p->rlink) {
            int v = p->vertex.number;   // ���� ���� v
            int weight = p->vertex.weight;  // ���� ����ġ

            // ���� ó������ �ʾҰ�, u�� ���ļ� v�� ���� ��ΰ� �� ª�ٸ� �Ÿ� ����
            if (!found[v] && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;  // �Ÿ� ����
                prev[v] = u;                // ��� ������ ���� ���� ���� ����
                // ���� ���� ���ŵ� ���� �ֱ�
                insert_min_heap(h, (heap_element) { .key = dist[v], .start = v });
            }
        }
    }

    // ���������� ó���� ������� ��� (������)
    found_list_order();

    // ����� �� �޸� ����
    destroy_heap(h);
}

int main(void) {
    // ��� �׷��� ���� �� ���ͽ�Ʈ�� ����
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
    printf("��� ��� ���ͽ�Ʈ�� \n");
    shortest_path_martix(&g, 0);

    // ���� ����Ʈ �׷��� ���� �� ���ͽ�Ʈ�� ����
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

    printf("\nMin-heap��� ���Ḯ��Ʈ ���ͽ�Ʈ��\n");
    dijkstra_sp(graph, 0);

    return 0;
}