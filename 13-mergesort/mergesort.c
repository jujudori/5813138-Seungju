#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

int compare = 0, moves = 0; // �� �� �̵� Ƚ�� ī��Ʈ
int totalComparisons = 0, totalMoves = 0; // �� �� �� �̵� Ƚ��
int isFirst = 0;    // ù ��° ������ ���� ����
int rounds = 0;      // ���� �� ���� �������� Ƚ�� ����

#define min(a, b) ((a) < (b) ? (a) : (b))

void generateRandomNumbers(int list[]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        list[i] = rand() % 1000; // 0���� 999���� ���� ����
    }
}

void printArray(int array[]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// ���� �Լ�
void merge(int array[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1; // ���� �κ� �迭 ũ��
    int n2 = r - m;     // ������ �κ� �迭 ũ��
    int roundsInMerge = 0;  // ���� �������� ����� rounds ����

    // �ӽ� �迭 ����
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // ���ʰ� ������ �迭 ����
    for (i = 0; i < n1; i++) {
        L[i] = array[l + i];
        moves++;  // �̵� Ƚ�� ����
    }
    for (j = 0; j < n2; j++) {
        R[j] = array[m + 1 + j];
        moves++;  // �̵� Ƚ�� ����
    }

    // ���� ����
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {

     
        compare++;  // �� Ƚ�� ����
       
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
        moves++;  // �̵� Ƚ�� ����
    }

    // ���� ���� �迭 ����
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
        moves++;  // �̵� Ƚ�� ����

    }

    // ���� ������ �迭 ����
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
        moves++;  // �̵� Ƚ�� ����
    }

    // 10���� �ѹ��� �迭 ���� ���
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 0; i < 10; i++) // 0 ~ 9��° �� ���
            printf("%3d ", array[i]);
        printf("| ");
        for (int i = MAX_SIZE / 2 - 1; i < MAX_SIZE / 2 + 10; i++) // �߾�-1 ~ �߾�+10
            printf("%3d ", array[i]);
        printf("\n\n");
    }
    rounds++;
    // ���� �޸� ����
    free(L);
    free(R);


}

// ���� ���� �Լ�
void mergeSort(int arr[], int n)
{
    int curr_size;
    int left_start;
 
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
    {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
        {
           
            int mid = min(left_start + curr_size - 1, n - 1);

            int right_end = min(left_start + 2 * curr_size - 1, n - 1);

            merge(arr, left_start, mid, right_end);
        }
    }
}

int main() {
    int array[MAX_SIZE];
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 20; i++) {
        generateRandomNumbers(array);
        compare = 0;
        moves = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            mergeSort(array, MAX_SIZE - 1);  // ���� ���� ȣ��

            printf("Result:\n");
            printArray(array);
            isFirst++;
        }
        else {
            mergeSort(array, MAX_SIZE - 1);  // ���� ���� ȣ��
        }

        totalComparisons += compare;
        totalMoves += moves;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
