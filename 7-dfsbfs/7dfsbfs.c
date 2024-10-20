#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define STACK_SIZE 100
#define QUEUE_SIZE 100

typedef struct GraphNode {
    int vertex;
    struct GraphNode* next;
} GraphNode;

typedef struct {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

typedef struct {
    int items[STACK_SIZE];
    int top;
} Stack;

typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void init_stack(Stack* s) {
    s->top = -1;
}

int is_empty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int item) {
    if (s->top < STACK_SIZE - 1) {
        s->items[++(s->top)] = item;
    }
    else {
        fprintf(stderr, "Stack overflow\n");
    }
}

int pop(Stack* s) {
    if (!is_empty(s)) {
        return s->items[(s->top)--];
    }
    return -1;
}

void init_queue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

int is_empty_queue(Queue* q) {
    return q->front > q->rear;
}

void enqueue(Queue* q, int item) {
    if (q->rear < QUEUE_SIZE - 1) {
        q->items[++(q->rear)] = item;
    }
    else {
        fprintf(stderr, "Queue overflow\n");
    }
}

int dequeue(Queue* q) {
    if (!is_empty_queue(q)) {
        return q->items[(q->front)++];
    }
    return -1;
}

GraphType* create_list_graph() {
    return (GraphType*)malloc(sizeof(GraphType));
}

void init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
    }
}

void insert_vertex(GraphType* g) {
    if (g->n >= MAX_VERTICES) {
        fprintf(stderr, "overflow\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "vertex error\n");
        return;
    }

    // start -> end ���� �߰�
    GraphNode* new_node = (GraphNode*)malloc(sizeof(GraphNode));
    new_node->vertex = end;
    new_node->next = NULL;

    // ������������ ����
    if (g->adj_list[start] == NULL || g->adj_list[start]->vertex > end) {
        new_node->next = g->adj_list[start];
        g->adj_list[start] = new_node;
    }
    else {
        GraphNode* current = g->adj_list[start];
        while (current->next != NULL && current->next->vertex < end) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

    // end -> start ���� �߰�
    new_node = (GraphNode*)malloc(sizeof(GraphNode));
    new_node->vertex = start;
    new_node->next = NULL;

    if (g->adj_list[end] == NULL || g->adj_list[end]->vertex > start) {
        new_node->next = g->adj_list[end];
        g->adj_list[end] = new_node;
    }
    else {
        GraphNode* current = g->adj_list[end];
        while (current->next != NULL && current->next->vertex < start) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}


void print_adj_list(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* node = g->adj_list[i];
        printf("%d: ", i);
        while (node != NULL) {
            printf("%d -> ", node->vertex);
            node = node->next;
        }
        printf("NULL\n");
    }
}

void dfs_list(GraphType* g, int start, int goal) {
    Stack s;
    init_stack(&s);
    int visited_count = 0;


    push(&s, start);
    visited[start] = TRUE;
    printf("%d ", start);
    visited_count++;

    while (!is_empty(&s)) {
        int v = pop(&s);
        GraphNode* node = g->adj_list[v];

        int backtrack = TRUE;

        while (node != NULL) {
            int w = node->vertex;
            if (!visited[w]) {
                visited[w] = TRUE;
                printf("%d ", w);
                visited_count++;

                if (w == goal) {
                    printf("\n");
                    printf("Ž�� ����: %d\n", w);
                    printf("�湮�� ����� ��: %d\n", visited_count);
                    return;
                }
                push(&s, v);
                push(&s, w);
                backtrack = FALSE;
                break;
            }
            node = node->next;
        }

        if (backtrack) {
            printf("%d ", v);
        }
    }

    printf("��ǥ ��带 ã�� ���߽��ϴ�. �湮�� ��� ��: %d\n", visited_count);
}


void bfs_list(GraphType* g, int start, int goal) {
    Queue q;
    init_queue(&q);
    int visited_count = 0;

    // �湮 �迭 �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = FALSE;
    }

    enqueue(&q, start);
    visited[start] = TRUE;
    printf("%d ", start);
    visited_count++;

    while (!is_empty_queue(&q)) {
        int v = dequeue(&q);
        GraphNode* node = g->adj_list[v];

        while (node != NULL) {
            int w = node->vertex;
            if (!visited[w]) {
                visited[w] = TRUE;
                printf("%d ", w);
                visited_count++;

                if (w == goal) {
                    printf("\nŽ�� ����: %d\n", w);
                    printf("�湮�� ����� ��: %d\n", visited_count);
                    return;
                }
                enqueue(&q, w);
            }
            node = node->next;
        }

        printf("%d ", v);  // BFS���� ��Ʈ��ŷ �� ���� ��� ���
    }

    printf("\n��ǥ ��带 ã�� ���߽��ϴ�. �湮�� ��� ��: %d\n", visited_count);
}


void runUserInterface(GraphType* g) {
    int option;
    int start_node, goal_node;

    while (TRUE) {
        printf("-----------------------\n");
        printf(" 1=���� �켱 Ž��            \n");
        printf(" 2=�ʺ� �켱 Ž��            \n");
        printf(" 3= ����                 \n");
        printf("-----------------------\n");

        printf("�ɼ��� �����ϼ���: ");
        scanf("%d", &option);

        for (int i = 0; i < MAX_VERTICES; i++) {
            visited[i] = FALSE;
        }

        switch (option) {
        case 1:
            printf("�޴��Է� : 1\n");
            printf("���۹�ȣ�� Ž���� �� �Է� (0���� %d����): ", g->n - 1);
            scanf("%d %d", &start_node, &goal_node);
            dfs_list(g, start_node, goal_node);
            break;
        case 2:
            printf("�޴��Է� : 2\n");
            printf("���۹�ȣ�� Ž���� �� �Է� (0���� %d����): ", g->n - 1);
            scanf("%d %d", &start_node, &goal_node);
            bfs_list(g, start_node, goal_node);
            break;
        case 3:
            printf("���α׷��� �����մϴ�.\n");
            return;
        default:
            printf("�߸��� �ɼ��Դϴ�. �ٽ� �Է��ϼ���.\n");
            return;
        }
    }
}

int main(void) {
    GraphType* g;
    g = create_list_graph();
    init(g);

    for (int i = 0; i < 11; i++) {
        insert_vertex(g);
    }
    insert_edge(g, 0, 5);
    insert_edge(g, 0, 6);
    insert_edge(g, 0, 9);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 4);
    insert_edge(g, 5, 3);
    insert_edge(g, 5, 4);
    insert_edge(g, 5, 1);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 4);
    insert_edge(g, 6, 8);
    insert_edge(g, 9, 8);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 4, 3);
    insert_edge(g, 4, 1);
    insert_edge(g, 10, 7);
    insert_edge(g, 10, 8);
    insert_edge(g, 10, 1);
    insert_edge(g, 7, 4);
    insert_edge(g, 7, 1);


    runUserInterface(g);

    free(g);
    return 0;
}