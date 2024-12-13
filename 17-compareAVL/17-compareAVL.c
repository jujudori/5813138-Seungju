#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 2000  // 작업 반복 횟수 설정

// 전역 변수 선언
int compareCount ;  // 비교 횟수 추적
int searchCount ;   // 탐색 횟수 추적
int A, B;
// 노드 구조체 정의 (AVL 트리와 BST에서 사용할 노드 구조체)
typedef struct Node {
    int key;            // 노드의 키
    struct Node* left, *right; // 자식 노드
    int height;         // 노드의 높이 (AVL 트리에서 사용)
} Node;

// 노드 생성 함수
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));  // 새 노드 메모리 할당
    node->key = key;  // 키 초기화
    node->left = node->right = NULL;  // 자식 노드는 NULL
    node->height = 1;  // 높이는 1로 초기화 (새 노드는 트리의 리프)
    return node;
}

// 노드의 높이 반환
int getHeight(Node* node) {
    if (node == NULL)
        return 0;  // NULL 노드는 높이가 0
    return node->height;  // 노드가 NULL이 아니면 높이 반환
}

// 균형 인수 계산 (왼쪽 서브트리의 높이 - 오른쪽 서브트리의 높이)
int getBalance(Node* node) {
    if (node == NULL)
        return 0;  // NULL 노드의 균형 인수는 0
    return getHeight(node->left) - getHeight(node->right);  // 왼쪽 - 오른쪽 높이
}

// 오른쪽 회전 (AVL 트리에서 균형을 맞추기 위한 회전)
Node* rotateRight(Node* y) {
    Node* x = y->left;  // 왼쪽 자식 노드
    Node* T2 = x->right;  // x의 오른쪽 자식

    // 회전 수행
    x->right = y;
    y->left = T2;

    // 높이 업데이트
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x;  // 회전 후 새로운 루트 반환
}

// 왼쪽 회전 (AVL 트리에서 균형을 맞추기 위한 회전)
Node* rotateLeft(Node* x) {
    Node* y = x->right;  // 오른쪽 자식 노드
    Node* T2 = y->left;  // y의 왼쪽 자식

    // 회전 수행
    y->left = x;
    x->right = T2;

    // 높이 업데이트
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));

    return y;  // 회전 후 새로운 루트 반환
}

// 최소값 노드 찾기 (AVL 트리 삭제에 사용)
Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;  // 왼쪽으로 계속 내려가면 최소값을 찾을 수 있음
    return current;
}

// AVL 트리 삽입 함수
Node* insertAVL(Node* root, int key) {
    if (root == NULL)
        return createNode(key);  // 루트가 NULL이면 새 노드 생성

    // 트리 삽입 (이진 탐색 트리처럼)
    if (key < root->key)
        root->left = insertAVL(root->left, key);  // 왼쪽 서브트리에 삽입
    else if (key > root->key)
        root->right = insertAVL(root->right, key);  // 오른쪽 서브트리에 삽입
    else
        return root;  // 중복 키는 삽입하지 않음

    // 높이 업데이트
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    // 균형 인수 계산
    int balance = getBalance(root);

    // 균형을 맞추기 위한 회전 (네 가지 경우)
    // LL, RR, LR, RL 케이스 처리
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;  // 트리 반환
}

// BST 삽입 함수 (단순한 이진 탐색 트리 삽입)
Node* insertBST(Node* root, int key) {
    if (root == NULL)
        return createNode(key);  // 루트가 NULL이면 새 노드 생성

    // 트리 삽입 (이진 탐색 트리처럼)
    if (key < root->key)
        root->left = insertBST(root->left, key);  // 왼쪽 서브트리에 삽입
    else if (key > root->key)
        root->right = insertBST(root->right, key);  // 오른쪽 서브트리에 삽입
    else
        return root;  // 중복 키는 삽입하지 않음

    return root;
}

// AVL 트리 삭제 함수
Node* deleteAVL(Node* root, int key) {
    if (root == NULL)
        return root;  // 노드가 NULL이면 그냥 반환

    // 트리 삭제 (이진 탐색 트리처럼)
    if (key < root->key)
        root->left = deleteAVL(root->left, key);
    else if (key > root->key)
        root->right = deleteAVL(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;  // 자식이 하나 또는 없으면 해당 자식을 대체

            if (temp == NULL) {
                temp = root;
                root = NULL;  // 노드를 삭제
            }
            else {
                *root = *temp;  // 자식 노드를 대체
            }

            free(temp);
        }
        else {
            // 두 자식이 모두 있을 경우 오른쪽 서브트리에서 최소값을 찾아 대체
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;  // 트리 비었으면 NULL 반환

    // 높이 업데이트
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    // 균형 인수 계산
    int balance = getBalance(root);

    // 균형을 맞추기 위한 회전
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// BST 삭제 함수 (단순한 이진 탐색 트리 삭제)
Node* deleteBST(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteBST(root->left, key);
    else if (key > root->key)
        root->right = deleteBST(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = getMinValueNode(root->right);
        root->key = temp->key;
        root->right = deleteBST(root->right, temp->key);
    }
    return root;
}

// AVL 트리 탐색 함수
Node* searchAVL(Node* root, int key) {

    if (root == NULL) { 
        compareCount++;
        return NULL;
    }

    compareCount++;// 현재 노드와의 비교 횟수 증가
    if (root->key == key) 
        return root;
    

    compareCount++;  // 왼쪽/오른쪽 자식 비교
    if (key < root->key) {
      
        return searchAVL(root->left, key);
    }
    else {
       
        return searchAVL(root->right, key);
    }
}

// BST 탐색 함수
Node* searchBST(Node* root, int key) {

    if (root == NULL) {
        compareCount++;
        return NULL;
    }
    compareCount++;// 현재 노드와의 비교 횟수 증가
    if (root->key == key){
      return root;
    }
    
    compareCount++;  
    if (key < root->key) // 왼쪽/오른쪽 자식 비교
    
        return searchBST(root->left, key);
    
    else 

        return searchBST(root->right, key);
    
}

// AVL 트리 작업 배치 수행
Node* doAVLBatch(Node* root) {
    searchCount = 0;
  

    for (int i = 0; i < SIZE; i++) {
        A = rand() % 3; // 0: 삽입, 1: 삭제, 2: 탐색
        B = rand() % 1000;  // 키 범위 설정

        switch (A) {
        case 0:
            root = insertAVL(root, B);  // 삽입
            break;
        case 1:
            root = deleteAVL(root, B);  // 삭제
            break;
        case 2:
            searchCount++;
            searchAVL(root, B);  // 탐색
            break;
        }

        A = B = 0;
    }
    return root;
}

// BST 작업 배치 수행
Node* doBinaryBatch(Node* root) {
    searchCount = 0;


    for (int i = 0; i < SIZE; i++) {
        int A = rand() % 3; // 0: 삽입, 1: 삭제, 2: 탐색
        int B = rand() % 1000;  // 키 범위 설정

        switch (A) {
        case 0:
            root = insertBST(root, B);  // 삽입
            break;
        case 1:
            root = deleteBST(root, B);  // 삭제
            break;
        case 2:
            searchCount++;
            searchBST(root, B);  // 탐색
            break;
        }
        A = B = 0;
    }
    return root;
}

// 트리 메모리 해제 함수
void freeTree(Node* root) {
    if (root == NULL)
        return;  // NULL이면 그냥 반환
    freeTree(root->left);  // 왼쪽 서브트리 해제
    freeTree(root->right);  // 오른쪽 서브트리 해제
    free(root);  // 현재 노드 해제
}

int main(int argc, char* argv[]) {
        Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;
    // 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);
    // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;
    // 과제에서 제시된 Binary Search Tree Batch를 수행한다.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);
    freeTree(root);
    return 0;
}