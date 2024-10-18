#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200

typedef struct TreeNode {
    int weight;              // 노드의 가중치
    char ch;                // 노드의 문자
    struct TreeNode* left;  // 왼쪽 자식
    struct TreeNode* right; // 오른쪽 자식
} TreeNode;

typedef struct {
    TreeNode* ptree;        // 트리 노드 포인터
    int key;                // 가중치
} element;

typedef struct {
    element heap[MAX_ELEMENT]; // 히프 배열
    int heap_size;             // 히프 크기
} HeapType;

// 생성 함수
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h) {
    h->heap_size = 0;
}

void swap(element* a, element* b) {
    element temp = *a;
    *a = *b;
    *b = temp;
}

void display(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%2d ", h->heap[i].key);
    }
    printf("\n");
}

void resortminHeap(HeapType* h, int i) {
    int smallest = i;       // 현재 노드
    int left = 2 * i;      // 왼쪽 자식 노드
    int right = 2 * i + 1; // 오른쪽 자식 노드

    if (left <= h->heap_size && h->heap[left].key < h->heap[smallest].key) {
        smallest = left;
    }

    if (right <= h->heap_size && h->heap[right].key < h->heap[smallest].key) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&h->heap[i], &h->heap[smallest]);
        resortminHeap(h, smallest);
    }
}

void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);
    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item; // 새로운 노드 삽입
}

element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1]; // 최소값 저장
    temp = h->heap[(h->heap_size)--]; // 마지막 노드 가져오기
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
            child++;
        if (temp.key < h->heap[child].key) break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp; // 힙 재구성
    return item;
}

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    node->weight = left->weight + right->weight;
    node->ch = '\0'; // 내부 노드이므로 문자 없음
    return node;
}

int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// 허프만 코드 출력 함수
void printCodes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1; // 왼쪽 자식에 대해 0 설정
        printCodes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0; // 오른쪽 자식에 대해 1 설정
        printCodes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        for (int i = 0; i < top; i++) {
            printf("%d ", codes[i]); // 각 코드 출력
        }
        printf("\n");
    }
}

// 허프만 트리 생성 함수
TreeNode* buildHuffmanTree(HeapType* heap) {
    while (heap->heap_size > 1) {
        element e1 = delete_min_heap(heap);
        element e2 = delete_min_heap(heap);

        TreeNode* x = make_tree(e1.ptree, e2.ptree);
        element combinedElement;
        combinedElement.key = e1.key + e2.key;
        combinedElement.ptree = x;
        insert_min_heap(heap, combinedElement);
        printf("/// %d + %d -> %d \n", e1.key, e2.key, combinedElement.key);
        display(heap);
    }

    element finalElement = delete_min_heap(heap);
    TreeNode* root = finalElement.ptree;
    free(heap);
    return root;
}

void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    HeapType* heap = create();
    init(heap);

    for (int i = 0; i < size; i++) {
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        node->ch = characters[i]; // 문자 설정
        node->weight = frequencies[i]; // 빈도수 설정
        node->left = node->right = NULL; // 자식 노드는 NULL
        element e = { node, node->weight };
        insert_min_heap(heap, e); // 히프 배열에 노드 삽입
        display(heap);
    }

    // Build min heap
    for (int i = heap->heap_size / 2; i >= 1; i--) {
        resortminHeap(heap, i);
       
    }

    TreeNode* root = buildHuffmanTree(heap);
    int arr[MAX_ELEMENT];
    printCodes(root, arr, 0);
}

// main 함수 정의
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    GenerateHuffmanCodes(characters, frequencies, size);

    return 0; // 프로그램 종료
}
