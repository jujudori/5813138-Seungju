#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct	TreeNode* left, * right;
}TreeNode;

void GenerateArrayTree(int* tree) {

	int list[] = { 1,2,9,3,5,10,13,4,6,7,8,11,12,14,15 };
	for (int i = 0; i < 15; i++) {
		tree[i] = list[i];
	}

	for (int i = 0; i < 15; i++) {
		printf("%d ", tree[i]);
	}
	printf("\n");
}

void ArrayPreOrder(int* tree, int i, int size) {
	if (i < size) {
		printf("[%2d] ", tree[i]);
		ArrayPreOrder(tree, 2 * i + 1, size);
		ArrayPreOrder(tree, 2 * i + 2, size);
	}
}
void ArrayInOrder(int* tree, int i, int size) {
	if (i < size) {
		ArrayInOrder(tree, 2 * i + 1, size);
		printf("[%2d] ", tree[i]);
		ArrayInOrder(tree, 2 * i + 2, size);
	}

}
void ArrayPostOrder(int* tree, int i, int size) {
	if (i < size) {
		ArrayPostOrder(tree, 2 * i + 1, size);
		ArrayPostOrder(tree, 2 * i + 2, size);
		printf("[%2d] ", tree[i]);
	}
}


void ArrayOrders(int* tree, int size) {
	printf("\n전위순회");
	ArrayPreOrder(tree, 0, size);
	printf("\n중위순회");
	ArrayInOrder(tree, 0, size);
	printf("\n후위순회");
	ArrayPostOrder(tree, 0, size);
}

void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

	if (direction == 0) {
		node->left = newnode;
	}
	else if (direction == 1) {
		node->right = newnode;
	}

}
void GenerateLinkTree(TreeNode* root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);
	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);
	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);
	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);
	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);
	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);
	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);
}


void LinkPreOrder(TreeNode* root) {
	if (root != NULL) {
		printf("[%2d] ", root->data);
		LinkPreOrder(root->left);
		LinkPreOrder(root->right);
	}

}

void LinkInOrder(TreeNode* root) {
	if (root != NULL) {
		LinkInOrder(root->left);
		printf("[%2d] ", root->data);
		LinkInOrder(root->right);
	}
}
void LinkPostOrder(TreeNode* root) {
	if (root != NULL) {
		LinkPostOrder(root->left);
		LinkPostOrder(root->right);
		printf("[%2d] ", root->data);
	}
}

void LinkOrders(TreeNode* root) {
	printf("\n전위순회");
	LinkPreOrder(root);
	printf("\n중위순회");
	LinkInOrder(root);
	printf("\n후위순회");
	LinkPostOrder(root);
}


int main() {
	int arr[15];
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;

	GenerateArrayTree(arr);
	GenerateLinkTree(root);

	ArrayOrders(arr, 15);
	LinkOrders(root);


	free(root);

	return 0;
}
