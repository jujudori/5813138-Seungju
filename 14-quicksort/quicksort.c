#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define min(a, b) ((a) < (b) ? (a) : (b))

int totalComparisons = 0, totalMoveCount = 0;
int isFirst = 0;    // 첫 번째 실행 여부
int rounds = 0;     // 현재 정렬 과정의 라운드 수
int comparisonCount = 0;
int moveCount = 0;

void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000; // 0~999 범위의 난수 생성
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
    int x = array[h]; // 피벗 값
    int i = (l - 1);  // 피벗보다 작은 구역의 끝 인덱스

    for (int j = l; j <= h - 1; j++) {
        comparisonCount++;
        if (array[j] <= x) {
            i++;
            if (i != j) { // 서로 다른 경우에만 교환
                swap(&array[i], &array[j]);
                moveCount += 3; // 교환 시 3번 이동 발생
            }
        }
    }
    if (i + 1 != h) { // 피벗 위치 조정
        swap(&array[i + 1], &array[h]);
        moveCount += 3;
    }

    return (i + 1); // 피벗의 최종 위치 반환
}

void doQuickSort(int array[], int l, int h) {
    int* stack = (int*)malloc((h - l + 1) * sizeof(int));
    int top = -1;

    stack[++top] = l; // 시작 구간 삽입
    stack[++top] = h;
  



    while (top >= 0) {

        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n\n");
        }
        rounds++;

        h = stack[top--]; // 상단 구간 꺼냄
        l = stack[top--];
        moveCount += 2;


        int p = partition(array, l, h); // 피벗 기준 분할

       
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
            moveCount += 2;
 
        }
        rounds++;
        // 오른쪽 구간 삽입
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
            moveCount += 2;
          
        }
    }

    free(stack); // 동적 메모리 해제
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
