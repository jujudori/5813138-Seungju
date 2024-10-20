#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct {
    int adj[MAX_NODES][MAX_NODES]; // 인접 행렬
    int numNodes; // 노드 수
} Graph;

// 스택 구조체
typedef struct {
    int items[MAX_NODES];
    int top;
} Stack;

// 스택 초기화
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비어있는지 확인
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택에 요소 추가
void push(Stack* s, int item) {
    if (s->top < MAX_NODES - 1) {
        s->items[++s->top] = item;
    }
}

// 스택에서 요소 제거
int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top--];
    }
    return -1; // 스택이 비어있으면 -1 반환
}

// 그래프 탐색 함수
void depthFirstSearch(Graph* g, int startNode, int targetNode) {
    bool visited[MAX_NODES] = { false }; // 방문한 노드 배열
    Stack stack;
    initStack(&stack);

    push(&stack, startNode);
    int visitedCount = 0; // 방문한 노드 수

    while (!isEmpty(&stack)) {
        int currentNode = pop(&stack);

        // 방문하지 않은 노드라면
        if (!visited[currentNode]) {
            visited[currentNode] = true; // 노드 방문 처리
            visitedCount++;
            printf("방문한 노드: %d\n", currentNode);

            // 목표 노드를 찾았을 경우
            if (currentNode == targetNode) {
                printf("목표 노드를 찾았습니다: %d\n", targetNode);
                printf("방문한 노드 수: %d\n", visitedCount);
                return;
            }

            // 인접한 노드 스택에 추가
            for (int i = 0; i < g->numNodes; i++) {
                if (g->adj[currentNode][i] == 1 && !visited[i]) {
                    push(&stack, i);
                }
            }
        }
    }
    printf("목표 노드를 찾지 못했습니다.\n");
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
