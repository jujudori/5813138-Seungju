#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct	TreeNode* left, * right;
}TreeNode;

typedef TreeNode* element;

typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;


void init(LinkedStackType* s)
{
	s->top = NULL;
}

int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

int is_full(LinkedStackType* s)
{
	return 0;
}

void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

element pop(LinkedStackType* s) {
	if (is_empty(s)) return NULL;
	StackNode* temp = s->top;
	TreeNode* node = temp->data;
	s->top = temp->link;
	free(temp);
	return node;

}

void print_stack(LinkedStackType* s)
{
	for (StackNode* p = s->top; p != NULL; p = p->link)
		printf("%d->", p->data->data);  // implementation specific
	printf("NULL \n");
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

int GetSumOfNodes(TreeNode* root) {
	if (root == NULL) return 0;

	int sumnode = 0;
	LinkedStackType s;
	init(&s);
	TreeNode* current = root;

	while (current != NULL || !is_empty(&s)) {
		while (current != NULL) {
			push(&s, current);
			current = current->left;
		}
		current = pop(&s);
		sumnode += current->data;
		current = current->right;
	}

	return sumnode;
}


int GetNumberOfNodes(TreeNode* root) {
	if (root == NULL) return 0;

	int count = 0;
	LinkedStackType s;
	init(&s);
	TreeNode* current = root;

	while (current != NULL || !is_empty(&s)) {
		while (current != NULL) {
			push(&s, current);
			current = current->left;
		}
		current = pop(&s);
		count++;
		current = current->right;
	}

	return count;
}
GetHeightOfTree(TreeNode* root) {

	if (root == NULL) return 0;

	LinkedStackType s;
	init(&s);
	push(&s, root);
	int height = 0;

	while (!is_empty(&s)) {

		LinkedStackType temp;
		init(&temp);

		while (!is_empty(&s)) {
			TreeNode* current = pop(&s);
			if (current->left) push(&temp, current->left);
			if (current->right) push(&temp, current->right);
		}

		while (!is_empty(&temp)) {
			push(&s, pop(&temp));
		}

		height++;
	}

	return height;
}


GetNumberOfLeafNodes(TreeNode* root) {
	if (root == NULL) return 0;

	int count = 0;
	LinkedStackType s;
	init(&s);
	push(&s, root);

	while (!is_empty(&s)) {
		TreeNode* current = pop(&s);
		if (current->left == NULL && current->right == NULL) {
			count++;
		}
		if (current->right) push(&s, current->right);
		if (current->left) push(&s, current->left);
	}

	return count;
}


int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;

	GenerateLinkTree(root);

	printf("Sum of nodes : %d\n", GetSumOfNodes(root));
	printf("Number of nodes : %d\n", GetNumberOfNodes(root));
	printf("Height of Tree : %d\n", GetHeightOfTree(root));
	printf("Number of leaf nodes : %d", GetNumberOfLeafNodes(root));

	free(root);

	return 0;
}