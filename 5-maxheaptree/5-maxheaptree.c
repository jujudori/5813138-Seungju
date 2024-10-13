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
            //generateheap트리 생성시에도 출력이 됨을 방지하기 위하여 매개변수 추가하여 true일시 출력할수있는것으로 만들었음
            //또한 heap[i/2]값이 [i]에 저장되면, [i]의 본 값이 날라가 중복으로 출력되기때문에 item변수에 미리 저장해두어
            //출력하는 것으로 조건문 추가했음.
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
     display(h);
    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++;
        }
        if (temp.key >= h->heap[child].key) break;
       
        element prev = h->heap[parent]; 
        //child 내용이 parent에 저장되어 parent내용이 날아가기때문에  저장해두는게 좋겠다 생각해서 prev 사용
       
      
        h->heap[parent] = h->heap[child]; //child<parent에 이동후
        h->heap[child] = prev; //prev이용하여 child저장
        display(h); //출력
       
       

        parent = child;
      
        child *= 2;
 
        count++;
    }

    h->heap[parent] = temp;
    display(h);
    printf("노드가 이동된 횟수: %d\n", count);
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
    printf(" i= 노드 추가             \n");
    printf(" d= 노드 삭제            \n");
    printf(" p=레벨별 출력         \n");
    printf(" c= 종료                 \n");
    printf("-----------------------\n");

    element item;
    for (true;;) {
        char a;
        printf("메뉴 입력 : ");
        scanf_s(" %c", &a); 

        switch (a) {
        case 'i':
            printf("추가 할 값 입력 : ");
            scanf_s("%d", &item.key);
            printf("노드 이동 된 횟수 : %d\n", insert_heap(h,item,true));
            continue;
        case 'd':
            delete_heap(h);
            continue;
        case 'p':
            printf("트리 레벨별 출력:\n");
            level_order(h);
            continue;
        case 'c':
            destroy_heap(h);
            break;
        
        defalut:
            printf("오류입니다, 바르게 입력하세요");
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
