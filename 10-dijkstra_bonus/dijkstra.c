#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define MAX_ELEMENT 100
#define INF 1000000  // 무한대를 나타내는 상수 값

// 요소 구조체: 정점 번호와 가중치를 저장
typedef struct {
    int number;
    int weight;
} element;

// 이중 연결 리스트의 노드 구조체
typedef struct DListNode {
    element vertex;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

// 인접 리스트 방식의 그래프 구조체
typedef struct {
    int num_of_vertex;  // 정점 수
    int num_of_edge;    // 간선 수
    DListNode adj_list[MAX_VERTICES];  // 인접 리스트
} GraphListType;

// 힙 요소 구조체: 다익스트라 알고리즘에서 사용될 힙 요소
typedef struct {
    int key;
    int start;
} heap_element;

// 최소 힙 구조체: 다익스트라 알고리즘에 사용되는 우선순위 큐
typedef struct {
    heap_element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// 행렬 방식 그래프 구조체
typedef struct GraphType {
    int n;  // 정점 수
    int weight[MAX_VERTICES][MAX_VERTICES];  // 가중치 행렬
} GraphType;

int found_sequence[MAX_VERTICES];  // 방문 순서 기록용 배열
int sequence_idx = 0;  // 방문 순서 인덱스

// 방문 순서 출력 함수
void found_order() {
    printf("Found Order: ");
    for (int i = 1; i <= 10; i++) {
        printf("%d ", found_sequence[i] + 1);
    }
    printf("\n");
}

// 방문 순서 출력 함수 (11번 인덱스 이후)
void found_list_order() {
    printf("Found Order: ");
    for (int i = 11; i < sequence_idx; i++) {
        printf("%d ", found_sequence[i] + 1);
    }
    printf("\n");
}

int distance[MAX_VERTICES];  // 최단 거리 저장 배열
int found[MAX_VERTICES];  // 방문 여부 저장 배열

// 최소 거리를 가진 정점을 선택하는 함수
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

// 현재 상태 (거리와 방문 배열)를 출력하는 함수
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

// 행렬 기반 다익스트라 알고리즘
void shortest_path_martix(GraphType* g, int start) {
    int i, u, w;

    // 초기화
    for (i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }

    distance[start] = 0;  // 시작 정점의 거리 초기화
    found_sequence[sequence_idx++] = start;
    found[start] = TRUE;

    print_status(g);

    // 최단 거리 계산 루프
    for (i = 0; i < g->n - 1; i++) {
        u = choose(distance, g->n, found);
        if (u == -1) break;

        found[u] = TRUE;
        found_sequence[sequence_idx++] = u;

        // 인접 정점 업데이트
        for (w = 0; w < g->n; w++) {
            if (!found[w] && g->weight[u][w] != INF && distance[u] + g->weight[u][w] < distance[w]) {
                distance[w] = distance[u] + g->weight[u][w];
            }
        }
    }

    // 초기화 후 다시 반복 (중복된 코드)
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

int dist[MAX_VERTICES], prev[MAX_VERTICES];  // 최단 거리 및 경로 배열

// 이중 연결 리스트 초기화
void init_Dlist(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

// 이중 연결 리스트 노드 삽입
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

// 힙 생성 및 초기화
HeapType* create_heap() {
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    if (!h) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    h->heap_size = 0;
    return h;
}

// 힙 초기화
void init_heap(HeapType* h) {
    h->heap_size = 0;
}

// 힙 메모리 해제
void destroy_heap(HeapType* h) {
    free(h);
}

// 최소 힙에 요소 삽입
void insert_min_heap(HeapType* h, heap_element item) {
    int i = ++h->heap_size;
    while (i > 1 && h->heap[i / 2].key > item.key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// 최소 힙에서 최소 요소 제거 및 반환
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

// 인접 리스트 방식의 그래프 생성 및 초기화
GraphListType* create_list_graph() {
    GraphListType* g = (GraphListType*)malloc(sizeof(GraphListType));
    if (!g) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    g->num_of_vertex = g->num_of_edge = 0;
    return g;
}

// 인접 리스트 초기화
void init_list_graph(GraphListType* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        init_Dlist(&(g->adj_list[i]));
        g->adj_list[i].vertex.number = -1;
    }
}

// 정점 삽입
void insert_vertex_list_graph(GraphListType* g, int v) {
    if (g->adj_list[v].vertex.number == -1) {
        g->adj_list[v].vertex.number = v;
        g->num_of_vertex++;
    }
}

// 간선 삽입
void insert_edge_list_graph(GraphListType* g, int s, int e, int w) {
    insert_Dlist(&(g->adj_list[s]), (element) { e, w });
    insert_Dlist(&(g->adj_list[e]), (element) { s, w });
    g->num_of_edge++;
}

// 상태 출력 함수 (거리와 방문 배열)
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
    // 최소 힙을 생성하고 초기화합니다.
    HeapType* h = create_heap();
    init_heap(h);

    // dist[]: 각 정점까지의 최단 거리를 저장하는 배열
    // prev[]: 각 정점의 이전 정점을 저장하는 배열 (최단 경로 추적용)
    // found[]: 해당 정점이 이미 처리되었는지 여부를 나타내는 배열
    for (int i = 0; i < g->num_of_vertex; i++) {
        dist[i] = INF;         // 초기값은 무한대로 설정
        prev[i] = -1;          // 이전 정점은 없으므로 -1로 설정
        found[i] = FALSE;      // 아직 처리되지 않았으므로 FALSE
    }

    // 시작 정점의 거리 초기화
    dist[start] = 0;

    // 시작 정점을 최소 힙에 넣습니다.
    insert_min_heap(h, (heap_element) { .key = 0, .start = start });

    // 힙이 비지 않으면 계속해서 처리합니다.
    while (h->heap_size > 0) {
        // 최소 힙에서 가장 우선순위가 높은 정점(최단 거리) 꺼내기
        heap_element element = delete_min_heap(h);
        int u = element.start;  // 꺼낸 정점

        // 이미 처리된 정점이면 건너뛰기
        if (found[u]) continue;

        // 정점 u를 처리 완료로 표시
        found[u] = TRUE;

        // 정점 u를 처리한 순서대로 저장 (디버깅이나 결과 확인용)
        found_sequence[sequence_idx++] = u;

        // 현재 상태를 출력 (디버깅용)
        print_dijkstra_status(g);

        // 정점 u와 연결된 모든 인접 정점 v에 대해 거리 업데이트
        for (DListNode* p = g->adj_list[u].rlink; p != &(g->adj_list[u]); p = p->rlink) {
            int v = p->vertex.number;   // 인접 정점 v
            int weight = p->vertex.weight;  // 간선 가중치

            // 아직 처리되지 않았고, u를 거쳐서 v로 가는 경로가 더 짧다면 거리 갱신
            if (!found[v] && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;  // 거리 갱신
                prev[v] = u;                // 경로 추적을 위해 이전 정점 갱신
                // 힙에 새로 갱신된 값을 넣기
                insert_min_heap(h, (heap_element) { .key = dist[v], .start = v });
            }
        }
    }

    // 최종적으로 처리된 순서대로 출력 (디버깅용)
    found_list_order();

    // 사용한 힙 메모리 해제
    destroy_heap(h);
}

int main(void) {
    // 행렬 그래프 생성 및 다익스트라 수행
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

    // 인접 리스트 그래프 생성 및 다익스트라 수행
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