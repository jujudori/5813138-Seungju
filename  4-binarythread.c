#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left, * right;
    int isThread;
} ThreadNode;

ThreadNode* prev;

TreeNode* new_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->right = temp->left = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL)
        return new_node(key);

    if (root->data == key) return root;
    else if (root->data > key) root->left = insert_node(root->left, key);
    else root->right = insert_node(root->right, key);

    return root;
}

TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_node(root, inputData[i]);
    }
    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%2d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

ThreadNode* newThreadNode(int key) {
    ThreadNode* temp = (ThreadNode*)malloc(sizeof(ThreadNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    temp->isThread = FALSE;
    return temp;
}

ThreadNode* insert_Thread_node(ThreadNode* root, int key) {
    if (root == NULL)
        return newThreadNode(key);

    if (root->data == key) return root;
    else if (root->data > key) root->left = insert_Thread_node(root->left, key);
    else root->right = insert_Thread_node(root->right, key);


    return root;
}

ThreadNode* createThread(ThreadNode* root) {
    if (root != NULL) {
        createThread(root->left);

        if (prev != NULL && prev->right == NULL) {
            prev->right = root;
            prev->isThread = TRUE;
        }
        prev = root;

        createThread(root->right);
    }
}
ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* troot = NULL;
    for (int i = 0; i < size; i++) {
        troot = insert_Thread_node(troot, inputData[i]);

    }

    prev = NULL;
    createThread(troot);
    return troot;
}



ThreadNode* find_successor(ThreadNode* p) {

    ThreadNode* q = p->right;
    if (q == NULL || p->isThread == TRUE) return q;
    while (q->left != NULL) q = q->left;
    return q;
}

void ThreadTreeInOrder(ThreadNode* t) {
    ThreadNode* q;
    q = t;
    while (q->left != NULL) q = q->left;
    do {
        printf("%2d ", q->data);
        q = find_successor(q);

    } while (q);
}

void freetree(TreeNode* root) {
    if (root != NULL) {
        freetree(root->left);
        freetree(root->right);
        free(root);
    }
}

void freethread(ThreadNode* root) {
    if (root != NULL) {
        freethread(root->left);
        freethread(root->right);
        free(root);
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(inputData, size);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    freetree(root);
    freethread(troot);

    return 0;
}