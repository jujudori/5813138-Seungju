#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define min(a, b) ((a) < (b) ? (a) : (b))

int totalComparisons = 0, totalMoveCount = 0; // 총 비교 및 이동 횟수
int isFirst = 0;    // 첫 번째 실행을 위한 변수
int rounds = 0;      // 분할 및 병합 과정에서 횟수 세기
int comparisonCount = 0;
int moveCount = 0;

void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000; // 0부터 999까지 난수 생성
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
    int i = (l - 1);  // 피벗보다 작은 영역의 끝 인덱스

    for (int j = l; j <= h - 1; j++) {
        comparisonCount++; // 비교 횟수 누적
        if (array[j] <= x) {
            i++;
            if (i != j) { // 값이 다를 때만 교환
                swap(&array[i], &array[j]);
                moveCount += 3; // swap 1번당 3번의 이동 발생
            }
        }
    }
    if (i + 1 != h) { // 피벗 위치로 이동
        swap(&array[i + 1], &array[h]);
        moveCount += 3; // swap 1번당 3번의 이동 발생
    }

    return (i + 1); // 피벗 위치 반환
}

void doQuickSort(int array[], int l, int h) {
    int* stack = (int*)malloc((h - l + 1) * sizeof(int));
    int top = -1;

    stack[++top] = l; // 시작 구간 푸시
    stack[++top] = h;
    rounds++; // 첫 번째 분할 라운드로 간주

    while (top >= 0) {
        h = stack[top--]; // 종료 구간 팝
        l = stack[top--]; // 시작 구간 팝
        moveCount += 2; // 스택 팝 이동 포함

        int p = partition(array, l, h); // 분할 후 피벗 위치 반환

        // 피벗 왼쪽 부분 정렬 구간 푸시
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
            moveCount += 2; // 스택 푸시 이동 포함
            rounds++; // 새로운 분할 라운드 추가
        }

        // 피벗 오른쪽 부분 정렬 구간 푸시
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
            moveCount += 2; // 스택 푸시 이동 포함
            rounds++; // 새로운 분할 라운드 추가
        }

        // 중간 상태 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) // 배열의 40~59번째 값 출력
                printf("%d ", array[i]);
            printf("\n\n");
        }
        rounds++;
    }

    free(stack); // 스택 메모리 해제
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
