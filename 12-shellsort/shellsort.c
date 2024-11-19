#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 
#define ARRAY_SIZE 100 // 배열 크기 정의


int comparisons = 0;    // 단일 실행에서의 비교 횟수
int moves = 0;          // 단일 실행에서의 이동 횟수
int comparisonCount, moveCount; // 여러 실행에서의 총 비교 및 이동 횟수

// 랜덤 숫자를 배열에 채우는 함수
void generateRandomNumbers(int list[]) {
    for (int i = 0; i < 100; i++) {
        list[i] = rand() % 1000; // 0~999 사이의 난수를 생성
    }
}

// 배열의 내용을 출력하는 함수
void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]); // 배열 요소 출력
    }
    printf("\n");
}

// 셸 정렬 함수
void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount) {
    int gap, i, j, temp;

    // 비교 및 이동 횟수 초기화
    *comparisonCount = 0;
    *moveCount = 0;

    // 20번 반복하여 평균 성능을 계산
    for (int try = 0; try < 20; try++) {
        moves = 0; comparisons = 0; // 각 반복에서의 비교 및 이동 횟수 초기화

        if (gapType == 2) { // 갭을 n/2로 감소시키는 방식
            for (gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) { // 갭 크기를 절반씩 줄임
                for (i = gap; i < ARRAY_SIZE; i++) {
                    temp = array[i]; // 현재 값을 임시 저장
                    moves++; // 이동 발생
                    for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                        array[j] = array[j - gap]; // 큰 값을 한 칸 뒤로 이동
                        comparisons++; // 비교 발생
                        moves++; // 이동 발생
                    }
                    array[j] = temp; // 올바른 위치에 삽입
                    moves++; // 이동 발생
                }
                // 첫 번째 실행 시, 각 갭에서의 상태 출력
                if (try == 0) {
                    printf("Gap %d:\n", gap);
                    for (int i = 0; i < 20; i++) {
                        printf("%2d ", array[i]); // 첫 20개의 요소만 출력
                    }
                    printf("...\n");
                }
            }
            if (try == 0) {
                printf("sorted shell array gap=2 : ");
                printArray(array); // 정렬 결과 출력
            }
        }
        else if (gapType == 3) { // 갭을 n/3로 감소시키는 방식
            for (gap = ARRAY_SIZE / 3; gap > 0; gap /= 3) { // 갭 크기를 1/3로 줄임
                for (i = gap; i < ARRAY_SIZE; i++) {
                    temp = array[i]; // 현재 값을 임시 저장
                    moves++; // 이동 발생
                    for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                        array[j] = array[j - gap]; // 큰 값을 한 칸 뒤로 이동
                        comparisons++; // 비교 발생
                        moves++; // 이동 발생
                    }
                    array[j] = temp; // 올바른 위치에 삽입
                    moves++; // 이동 발생
                }
                // 첫 번째 실행 시, 각 갭에서의 상태 출력
                if (try == 0) {
                    printf("Gap %d:\n", gap);
                    for (int i = 0; i < 20; i++) {
                        printf("%2d ", array[i]); // 첫 20개의 요소만 출력
                    }
                    printf("...\n");
                }
            }
            if (try == 0) {
                printf("sorted shell array gap= 3 : ");
                printArray(array); // 정렬 결과 출력
            }
        }

        *comparisonCount += comparisons; // 비교 횟수 누적
        *moveCount += moves; // 이동 횟수 누적

        // 배열을 다시 랜덤하게 생성하여 초기화
        generateRandomNumbers(array);
    }
}

// 삽입 정렬 함수
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int i, j, key;

    // 비교 및 이동 횟수 초기화
    *comparisonCount = 0;
    *moveCount = 0;

    // 20번 반복하여 평균 성능 계산
    for (int try = 0; try < 20; try++) {
        moves = 0; comparisons = 0; // 각 반복에서의 비교 및 이동 횟수 초기화

        for (i = 1; i < ARRAY_SIZE; i++) {
            key = array[i]; // 현재 값을 저장
            moves++; // 이동 발생
            for (j = i - 1; j >= 0 && array[j] > key; j--) {
                array[j + 1] = array[j]; // 큰 값을 한 칸 뒤로 이동
                comparisons++; // 비교 발생
                moves++; // 이동 발생
            }
            array[j + 1] = key; // 올바른 위치에 삽입
            moves++; // 이동 발생
        }

        // 첫 번째 실행 시 결과 출력
        if (try == 0) {
            printf("sorted Insertion array : ");
            printArray(array); // 정렬 결과 출력
        }

        *comparisonCount += comparisons; // 비교 횟수 누적
        *moveCount += moves; // 이동 횟수 누적

        // 배열을 다시 랜덤하게 생성하여 초기화
        generateRandomNumbers(array);
    }
}

int main() {
	int array[ARRAY_SIZE];
    int shell2[ARRAY_SIZE];
    int shell3[ARRAY_SIZE];
    int insertion[ARRAY_SIZE];

    srand((unsigned int)time(NULL));
	generateRandomNumbers(array);


	// Shell Sort
    for (int i = 0; i < ARRAY_SIZE; i++) {
        shell2[i] = array[i];
        shell3[i] = array[i];
        insertion[i] = array[i];
    }

    printf("Shell Sort (n/2):\n");
    doShellSort(shell2, 2, &comparisonCount, &moveCount);
	printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount/20, moveCount/20);
    
    
	printf("Shell Sort (n/3):\n");
    doShellSort(shell3, 3, &comparisonCount, &moveCount);
	printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount/20, moveCount/20);

 //Insertion Sort – 보너스(보너스 풀지 않는 경우 하단 없어도 됨)

    printf("Insertion Sort:\n");
    doInsertionSort(insertion, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount/20, moveCount/20);
	return 0;
}