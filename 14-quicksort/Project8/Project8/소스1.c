#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define min(a, b) ((a) < (b) ? (a) : (b))

int totalComparisons = 0, totalMoveCount = 0; // �� �� �� �̵� Ƚ��
int isFirst = 0;    // ù ��° ������ ���� ����
int rounds = 0;      // ���� �� ���� �������� Ƚ�� ����
int comparisonCount = 0;
int moveCount = 0;

void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000; // 0���� 999���� ���� ����
    }
}

void printArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int array[], int l, int h) {
    int x = array[h]; // �ǹ� ��
    int i = (l - 1);  // �ǹ����� ���� ������ �� �ε���

    for (int j = l; j <= h - 1; j++) {
        comparisonCount++; // �� Ƚ�� ����
        if (array[j] <= x) {
            i++;
            if (i != j) { // ���� �ٸ� ���� ��ȯ
                swap(&array[i], &array[j]);
                moveCount += 3; // swap 1���� 3���� �̵� �߻�
            }
        }
    }
    if (i + 1 != h) { // �ǹ� ��ġ�� �̵�
        swap(&array[i + 1], &array[h]);
        moveCount += 3; // swap 1���� 3���� �̵� �߻�
    }

    return (i + 1); // �ǹ� ��ġ ��ȯ
}

void doQuickSort(int array[], int l, int h) {
    int* stack = (int*)malloc((h - l + 1) * sizeof(int));
    int top = -1;

    stack[++top] = l; // ���� ���� Ǫ��
    stack[++top] = h;
    rounds++; // ù ��° ���� ����� ����

    while (top >= 0) {
        h = stack[top--]; // ���� ���� ��
        l = stack[top--]; // ���� ���� ��
        moveCount += 2; // ���� �� �̵� ����

        int p = partition(array, l, h); // ���� �� �ǹ� ��ġ ��ȯ

        // �ǹ� ���� �κ� ���� ���� Ǫ��
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
            moveCount += 2; // ���� Ǫ�� �̵� ����
            rounds++; // ���ο� ���� ���� �߰�
        }

        // �ǹ� ������ �κ� ���� ���� Ǫ��
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
            moveCount += 2; // ���� Ǫ�� �̵� ����
            rounds++; // ���ο� ���� ���� �߰�
        }

        // �߰� ���� ���
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) // �迭�� 40~59��° �� ���
                printf("%d ", array[i]);
            printf("\n\n");
        }
        rounds++;
    }

    free(stack); // ���� �޸� ����
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);
            printf("Result\n");
            printArray(array);
            isFirst++;
        }
        else {
            doQuickSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;
}
