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

typedef struct ThreadNode ThreadTree;

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

void madeThreads(TreeNode* root, ThreadNode** prev, ThreadNode** troot) {
    if (root == NULL) return;


    madeThreads(root->left, prev, troot);


    ThreadNode* current = newThreadNode(root->data);
    if (*troot == NULL) {
        *troot = current
    }


    if (*prev != NULL) {
        if ((*prev)->right == NULL) {
            (*prev)->right = current;
            (*prev)->isThread = TRUE;
        }
    }

    *prev = current;


    madeThreads(root->right, prev, troot);
}

ThreadNode* GenerateThreadTree(TreeNode* root) {
    ThreadNode* root = NULL;
    ThreadNode* prev = NULL;
    madeThreads(root, &prev, &root);
    return root;
}

ThreadNode* find_successor(ThreadNode* p) {
    if (p->isThread) {
        return p->right;
    }

    p = p->right;
    while (p != NULL && p->left != NULL) {
        p = p->left;
    }
    return p;
}

void ThreadTreeInOrder(ThreadNode* t) {
    if (t == NULL) return 0;


    while (t->left) {
        t = t->left;
    }
    do {
        printf("%2d", t->data);
        t = find_successor(t);
    } while (t);
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

    ThreadTree* troot = GenerateThreadTree(root);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    freetree(root);
    freethread(troot);

    return 0;
}
