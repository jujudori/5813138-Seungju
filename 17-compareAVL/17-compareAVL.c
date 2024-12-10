#include <stdlib.h>
#include <stdio.h>

#define SIZE 2000
int searchCount, compareCount;
int A, B; 

typedef struct Node {
    int key;
    struct Node* left, * right;
    int height;
} Node;

Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));
    nptr->key = key;
    nptr->right = nptr->left = (Node*)NULL;
    nptr->height = 1;
    return nptr;
}

int getHeight(Node* nptr) {
    if (nptr == (Node*)NULL) return 0;
    else return nptr->height;
}

int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T3 = x->right;

    x->right = y;
    y->left = T3;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));

    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;
}

Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));

    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;
}

Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* insertAVL(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (root->key == key) {
        compareCount++;  // 첫 번째 비교
        return root;
    }
    compareCount++;  // 두 번째 비교
    if (key < root->key) {
        root->left = insertAVL(root->left, key);
    }
    else {
        root->right = insertAVL(root->right, key);
    }

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) 
        ? getHeight(root->left) : getHeight(root->right));

    int balance = getHeight(root->left) - getHeight(root->right);

    // 회전 연산에서는 compareCount를 증가시키지 않음
    if (balance > 1) {
        if (key < root->left->key) {
            return rotateRight(root);
        }
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1) {
        if (key > root->right->key) {
            return rotateLeft(root);
        }
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* insertBST(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    compareCount++;  // 탐색 비교
    if (key < root->key) {
        root->left = insertBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = insertBST(root->right, key);
    }
    return root;
}

Node* deleteAVL(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (root->key == key) {
        compareCount++;  // 첫 번째 비교
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }
    else {
        compareCount++;  // 두 번째 비교
        if (key < root->key) {
            root->left = deleteAVL(root->left, key);
        }
        else {
            root->right = deleteAVL(root->right, key);
        }
    }

    if (root == NULL) {
        return NULL;
    }

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left) : getHeight(root->right));

    int balance = getHeight(root->left) - getHeight(root->right);

    // 회전 연산에서는 compareCount를 증가시키지 않음
    if (balance > 1) {
        if (getHeight(root->left->left) >= getHeight(root->left->right)) {
            return rotateRight(root);
        }
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1) {
        if (getHeight(root->right->right) >= getHeight(root->right->left)) {
            return rotateLeft(root);
        }
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* deleteBST(Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    compareCount++;  // 탐색 비교
    if (key < root->key) {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteBST(root->right, key);
    }
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

Node* searchAVL(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (root->key == key) {
        compareCount++;  // 첫 번째 비교
        return root;
    }
    compareCount++;  // 두 번째 비교
    if (key < root->key) {
        return searchAVL(root->left, key);
    }
    return searchAVL(root->right, key);
}

Node* searchBST(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (root->key == key) {
        compareCount++;  // 탐색 비교
        return root;
    }
    compareCount++;  // 탐색 비교
    if (key < root->key) {
        return searchBST(root->left, key);
    }
    else {
        return searchBST(root->right, key);
    }
}

Node* doAVLBatch(Node* root) {
    for (int i = 0; i < SIZE; i++) {
        A = rand() % 3; // 0: 삽입, 1: 삭제, 2: 탐색
        B = rand() % 1000;

        switch (A) {
        case 0:
            root = insertAVL(root, B);
            break;
        case 1:
            root = deleteAVL(root, B);
            break;
        case 2:
            searchCount++; // 탐색 횟수 증가
            searchAVL(root, B);
            break;
        }
    }
    return root;
}

Node* doBinaryBatch(Node* root) {
    for (int i = 0; i < SIZE; i++) {
        A = rand() % 3; // 0: 삽입, 1: 삭제, 2: 탐색
        B = rand() % 1000;

        switch (A) {
        case 0:
            root = insertBST(root, B);
            break;
        case 1:
            root = deleteBST(root, B);
            break;
        case 2:
            searchCount++; // 탐색 횟수 ���가
            searchBST(root, B);
            break;
        }
    }
    return root;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // AVL 트리 2000번 작업
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // 트리 메모리 해제
    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;

    // Binary Search Tree 2000번 작업
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}
