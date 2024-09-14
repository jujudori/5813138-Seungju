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

// 초기화 함수
void init(LinkedStackType* s)
{
	s->top = NULL;
}
// 공백 상태 검출 함수
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}
// 포화 상태 검출 함수
int is_full(LinkedStackType* s)
{
	return 0;
}
// 삽입 함수
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
	printf("Push(%d)", item->data);
}

element pop(LinkedStackType* s) {
	if (is_empty(s)) return NULL;
	StackNode* temp = s->top;
	TreeNode* node = temp->data;
	s->top = temp->link;
	free(temp);
	printf("Pop(%d)", node->data);
	return node;

}

void print_stack(LinkedStackType* s)
{
	for (StackNode* p = s->top; p != NULL; p = p->link)
		printf("%d->", p->data->data);  // implementation specific
	printf("NULL \n");
}

void LinkInOrder(TreeNode* root) {

	LinkedStackType s;
	TreeNode* nptr = root;
	init(&s);

	while (nptr != NULL || !is_empty(&s)) {
		while (nptr != NULL) {
			push(&s, nptr);
			nptr = nptr->left;
		}
		nptr = pop(&s);
		printf("Visit(% 2d)\n", nptr->data);
		nptr = nptr->right;
	}
}
void LinkPreOrder(TreeNode* root) {

	LinkedStackType  s;
	TreeNode* nptr = root;
	init(&s);

	while (nptr != NULL || !is_empty(&s)) {
		while (nptr != NULL) {
			push(&s, nptr);
			printf("Visit(% 2d)\n", nptr->data);
			nptr = nptr->left;
		}
		nptr = pop(&s);
		nptr = nptr->right;
	}
}

void LinkPostOrder(TreeNode* root) {
	if (root == NULL) return;
	LinkedStackType s1, s2;
	init(&s1);
	init(&s2);

	push(&s1, root);

	while (!is_empty(&s1)) {
		TreeNode* node = pop(&s1);
		push(&s2, node);


		if (node->left != NULL) {
			push(&s1, node->left);
		}
		if (node->right != NULL) {
			push(&s1, node->right);
		}
	}


	while (!is_empty(&s2)) {
		TreeNode* node = pop(&s2);
		printf("Visit(% 2d)\n", node->data);
	}
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



void LinkOrders(TreeNode* root) {
	printf("\n전위순회");
	LinkPreOrder(root);
	printf("\n중위순회");
	LinkInOrder(root);
	printf("\n후위순회");
	LinkPostOrder(root);
	printf("\n");
}


int main() {
	int arr[15];
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;

	GenerateLinkTree(root);

	LinkOrders(root);

	free(root);

	return 0;
}