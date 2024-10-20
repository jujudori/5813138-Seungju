#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct {
    int adj[MAX_NODES][MAX_NODES]; // ���� ���
    int numNodes; // ��� ��
} Graph;

// ���� ����ü
typedef struct {
    int items[MAX_NODES];
    int top;
} Stack;

// ���� �ʱ�ȭ
void initStack(Stack* s) {
    s->top = -1;
}

// ������ ����ִ��� Ȯ��
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// ���ÿ� ��� �߰�
void push(Stack* s, int item) {
    if (s->top < MAX_NODES - 1) {
        s->items[++s->top] = item;
    }
}

// ���ÿ��� ��� ����
int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top--];
    }
    return -1; // ������ ��������� -1 ��ȯ
}

// �׷��� Ž�� �Լ�
void depthFirstSearch(Graph* g, int startNode, int targetNode) {
    bool visited[MAX_NODES] = { false }; // �湮�� ��� �迭
    Stack stack;
    initStack(&stack);

    push(&stack, startNode);
    int visitedCount = 0; // �湮�� ��� ��

    while (!isEmpty(&stack)) {
        int currentNode = pop(&stack);

        // �湮���� ���� �����
        if (!visited[currentNode]) {
            visited[currentNode] = true; // ��� �湮 ó��
            visitedCount++;
            printf("�湮�� ���: %d\n", currentNode);

            // ��ǥ ��带 ã���� ���
            if (currentNode == targetNode) {
                printf("��ǥ ��带 ã�ҽ��ϴ�: %d\n", targetNode);
                printf("�湮�� ��� ��: %d\n", visitedCount);
                return;
            }

            // ������ ��� ���ÿ� �߰�
            for (int i = 0; i < g->numNodes; i++) {
                if (g->adj[currentNode][i] == 1 && !visited[i]) {
                    push(&stack, i);
                }
            }
        }
    }
    printf("��ǥ ��带 ã�� ���߽��ϴ�.\n");
}

int main() {
    Graph g = {
        .numNodes = 6,
        .adj = {
            {0, 1, 1, 0, 0, 0},
            {1, 0, 0, 1, 1, 0},
            {1, 0, 0, 0, 0, 1},
            {0, 1, 0, 0, 0, 1},
            {0, 1, 0, 0, 0, 0},
            {0, 0, 1, 1, 0, 0}
        }
    };

    int startNode = 0;
    int targetNode = 5;
    depthFirstSearch(&g, startNode, targetNode);

    return 0;
}
