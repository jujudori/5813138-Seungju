#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

int compare = 0, moves = 0; // 비교 및 이동 횟수 카운트
int totalComparisons = 0, totalMoves = 0; // 총 비교 및 이동 횟수
int isFirst = 0;    // 첫 번째 실행을 위한 변수
int rounds = 0;      // 분할 및 병합 과정에서 횟수 세기

#define min(a, b) ((a) < (b) ? (a) : (b))

void generateRandomNumbers(int list[]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        list[i] = rand() % 1000; // 0부터 999까지 난수 생성
    }
}

void printArray(int array[]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 병합 함수
void merge(int array[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1; // 왼쪽 부분 배열 크기
    int n2 = r - m;     // 오른쪽 부분 배열 크기
    int roundsInMerge = 0;  // 병합 내에서만 사용할 rounds 변수

    // 임시 배열 생성
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // 왼쪽과 오른쪽 배열 복사
    for (i = 0; i < n1; i++) {
        L[i] = array[l + i];
        moves++;  // 이동 횟수 증가
    }
    for (j = 0; j < n2; j++) {
        R[j] = array[m + 1 + j];
        moves++;  // 이동 횟수 증가
    }

    // 병합 과정
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        compare++;  // 비교 횟수 증가
        rounds++;  // 병합 과정에서 비교 횟수 증가
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
        moves++;  // 이동 횟수 증가
    }

    // 남은 왼쪽 배열 복사
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
        moves++;  // 이동 횟수 증가
        rounds++;  // 병합 과정에서 추가된 값도 rounds++
    }

    // 남은 오른쪽 배열 복사
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
        moves++;  // 이동 횟수 증가
        rounds++;
    }

    // 10번에 한번만 배열 상태 출력
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 0; i < 10; i++) // 0 ~ 9번째 값 출력
            printf("%3d ", array[i]);
        printf("| ");
        for (int i = MAX_SIZE / 2 - 1; i < MAX_SIZE / 2 + 10; i++) // 중앙-1 ~ 중앙+10
            printf("%3d ", array[i]);
        printf("\n\n");
    }

    // 동적 메모리 해제
    free(L);
    free(R);


}

// 병합 정렬 함수
void mergeSort(int arr[], int n) {
    int curr_size;       // 현재 병합하는 부분 배열의 크기
    int left_start;      // 현재 병합하는 부분 배열의 시작 인덱스

    // 부분 배열의 크기를 1, 2, 4, ... 순으로 두 배씩 증가시켜 병합
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        // 부분 배열을 왼쪽에서 오른쪽으로 병합
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            // 현재 부분 배열의 중간 인덱스 계산
            // 왼쪽 배열의 끝 지점
            int mid = min(left_start + curr_size - 1, n - 1);

            // 오른쪽 배열의 끝 지점
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);

            // 병합 함수 호출: 왼쪽 시작, 중간, 오른쪽 끝 인덱스를 전달
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
            mergeSort(array, MAX_SIZE - 1);  // 병합 정렬 호출

            printf("Result:\n");
            printArray(array);
            isFirst++;
        }
        else {
            mergeSort(array, MAX_SIZE - 1);  // 병합 정렬 호출
        }

        totalComparisons += compare;
        totalMoves += moves;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
