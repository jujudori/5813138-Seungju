#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100
#define true 1
#define false 0
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

HeapType* create() {
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    
    return h;
}

void init_heap(HeapType* h) {
    h->heap_size = 0;
}

void destroy_heap(HeapType* h) {
    free(h);

}

int is_empty_heap(HeapType* h) {
    return (h->heap_size == 0);
}

int is_full_heap(HeapType* h) {
    return (h->heap_size == MAX_ELEMENT);
}

void display(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%2d ", h->heap[i].key);
    }
    printf("\n");
}
int insert_heap(HeapType* h, element item, int display_true) {
    int count = 0;
    int i = ++(h->heap_size);

    h->heap[i] = item;
 
    while (i != 1 && item.key > h->heap[i / 2].key) {

        h->heap[i] = h->heap[i / 2];
        if (display_true && i != 1 && item.key > h->heap[i / 2].key) {
            h->heap[i / 2] = item;
            display(h);  
            //generateheapƮ�� �����ÿ��� ����� ���� �����ϱ� ���Ͽ� �Ű����� �߰��Ͽ� true�Ͻ� ����Ҽ��ִ°����� �������
            //���� heap[i/2]���� [i]�� ����Ǹ�, [i]�� �� ���� ���� �ߺ����� ��µǱ⶧���� item������ �̸� �����صξ�
            //����ϴ� ������ ���ǹ� �߰�����.
        }

        count++;
        i /= 2;
    }
    h->heap[i] = item;
    if (display_true) {
        display(h);
    }
    i++;
    return count;  
}

element delete_heap(HeapType* h) {
    element item = h->heap[1];
    element temp = h->heap[h->heap_size--];
    int parent = 1;
    int child = 2;
    int count = 1;

    h->heap[parent] = temp;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++;
        }
        if (temp.key >= h->heap[child].key) break;
       
        element prev = h->heap[parent]; 
        //child ������ parent�� ����Ǿ� parent������ ���ư��⶧����  �����صδ°� ���ڴ� �����ؼ� prev ���
       
      
        h->heap[parent] = h->heap[child]; //child<parent�� �̵���
        h->heap[child] = prev; //prev�̿��Ͽ� child����
        display(h); //���
       
       

        parent = child;
      
        child *= 2;
 
        count++;
    }

    h->heap[parent] = temp;
    display(h);
    printf("��尡 �̵��� Ƚ��: %d\n", count);
    return item;
}

TreeNode* new_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL) return new_node(key);
    if (root->data > key) root->left = insert_node(root->left, key);
    else if (root->data < key) root->right = insert_node(root->right, key);
    return root;
}

TreeNode* generateMaxHeapTree(HeapType* h, int inputData[], int size) {
    TreeNode* root = NULL;

    for (int i = 0; i < size; i++) {
        root = insert_node(root, inputData[i]);
        element e = { inputData[i] };
        insert_heap(h, e,false); 
    }

    return root;
}




void level_order(HeapType* h) {
    if (h->heap_size == 0) return;

    int level = 1;
    int count = 0;
    int nodes_in_level = 1;

    
    printf("[%d] ", level);
    for (int i = 1; i <= h->heap_size; i++) {
        printf(" %d", h->heap[i].key);
        count++;

        if (count == nodes_in_level) {
            printf("\n");
            level++;
            printf("[%d] ", level);
            nodes_in_level *= 2;
            count = 0;
          
        }

   
    }
    if(count !=NULL)
    printf("\n");
}



void runUserInterface(HeapType* h, TreeNode* root,int size) {
    printf("-----------------------\n");
    printf(" i= ��� �߰�             \n");
    printf(" d= ��� ����            \n");
    printf(" p=������ ���         \n");
    printf(" c= ����                 \n");
    printf("-----------------------\n");

    element item;
    for (true;;) {
        char a;
        printf("�޴� �Է� : ");
        scanf_s(" %c", &a); 

        switch (a) {
        case 'i':
            printf("�߰� �� �� �Է� : ");
            scanf_s("%d", &item.key);
            printf("��� �̵� �� Ƚ�� : %d\n", insert_heap(h,item,true));
            continue;
        case 'd':
            delete_heap(h);
            continue;
        case 'p':
            printf("Ʈ�� ������ ���:\n");
            level_order(h);
            continue;
        case 'c':
            destroy_heap(h);
            break;
        
        defalut:
            printf("�����Դϴ�, �ٸ��� �Է��ϼ���");
            continue;
        }
    }
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 }; // Unordered
    int size = sizeof(inputData) / sizeof(inputData[0]);
    HeapType* h = create();
    init_heap(h);
    TreeNode* root = generateMaxHeapTree(h, inputData, size);
    runUserInterface(h, root,size);


    free(root);

    return 0;
}
