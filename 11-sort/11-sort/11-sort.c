#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 

#define SIZE 100 // 배열의 크기 정의
#define swap(x, y, t) ((t) = (x), (x) = (y), (y) = (t)) // swap 매크로 정의

int count = 0; // 현재 실행에서의 비교 횟수
int totalcount = 0; // 여러 번 실행한 후 총 비교 횟수

// 배열을 출력하는 함수
void print_list(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        printf(" %02d", list[i]); // 두 자리로 출력 (앞에 0 포함)
    }
    printf("\n");
}

// 0~999 사이의 랜덤 숫자로 배열을 채우는 함수
void generateRandomData(int list[]) {
    for (int i = 0; i < 100; i++) {
        list[i] = rand() % 1000;
    }
}

// 선택 정렬 함수
void doSelectionSort(int list[]) {
    int i, j, least, temp;
    printf("selection sort result :\n");
    for (i = 0; i < SIZE - 1; i++) { // 배열의 길이 - 1 만큼 반복
        least = i; // 현재 위치를 최소값으로 가정
        for (j = i + 1; j < SIZE; j++) { // 나머지 요소와 비교
            if (list[least] > list[j])
                least = j; // 더 작은 값을 찾으면 최소값 인덱스 갱신
        }
        swap(list[i], list[least], temp); // 최소값을 현재 위치로 이동
        // 특정 단계에서 배열 상태를 출력
        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 98) {
            printf("step %d : ", i + 1);
            print_list(list);
            printf("\n");
        }
    }
}

// 삽입 정렬 함수
void doInsertionSort(int list[]) {
    int i, j, key;
    totalcount = 0; // 총 비교 횟수를 초기화
    for (int try = 0; try < 20; try++) { // 평균 비교 횟수를 계산하기 위해 20번 실행
        count = 0; // 실행마다 비교 횟수 초기화
        for (i = 1; i < SIZE; i++) { // 두 번째 요소부터 시작
            key = list[i]; // 현재 요소를 저장
            for (j = i - 1; j >= 0; j--) { // 왼쪽으로 이동하며 비교
                count++;
                if (list[j] > key)
                    list[j + 1] = list[j]; // 큰 값을 오른쪽으로 이동
                else
                    break; // 삽입 위치를 찾으면 종료
            }
            list[j + 1] = key; // 요소 삽입
        }
        // 첫 번째 실행에서 결과 출력
        if (try == 0) {
            printf("InsertionSort Result : \n");
            print_list(list);
            printf("\n");
        }
        totalcount += count; // 비교 횟수를 누적
        generateRandomData(list); // 배열을 새로 랜덤 생성
    }
    printf("insertion compare average : %d\n", totalcount / 20); // 평균 비교 횟수 출력
    printf("\n");
}

// 버블 정렬 함수
void doBubbleSort(int list[]) {
    int i, j, temp;
    int flag = 0; // 정렬 여부를 나타내는 플래그
    totalcount = 0; // 총 비교 횟수를 초기화
    for (int try = 0; try < 20; try++) { // 평균 비교 횟수를 계산하기 위해 20번 실행
        count = 0; // 실행마다 비교 횟수 초기화
        for (i = SIZE - 1; i > 0; i--) { // 배열의 끝부터 시작
            for (j = 0; j < i; j++) { // 현재 범위에서 인접한 요소를 비교
                if (list[j] > list[j + 1]) {
                    swap(list[j], list[j + 1], temp); // 요소 교환
                    count += 3; // 비교 및 교환 횟수 증가
                    flag = 1; // 교환 발생
                }
            }
            if (flag == 0)
                break; // 정렬 완료 시 루프 종료
        }
        // 첫 번째 실행에서 결과 출력
        if (try == 0) {
            printf("BubbleSort Result : \n");
            print_list(list);
            printf("\n");
        }
        totalcount += count; // 비교 횟수를 누적
        generateRandomData(list); // 배열을 새로 랜덤 생성
    }
    printf("Bubble compare average : %d\n", totalcount / 20); // 평균 비교 횟수 출력
}

// 메인 함수
int main() {
    srand((unsigned int)time(NULL)); // 랜덤 시드 설정

    int randomData[SIZE]; // 랜덤 데이터 저장
    int select[SIZE]; // 선택 정렬용 배열
    int bubble[SIZE]; // 버블 정렬용 배열
    int insertion[SIZE]; // 삽입 정렬용 배열

    generateRandomData(randomData); // 랜덤 데이터 생성

    // 배열 복사
    for (int i = 0; i < SIZE; i++) {
        select[i] = randomData[i];
        bubble[i] = randomData[i];
        insertion[i] = randomData[i];
    }

    doSelectionSort(select); // 선택 정렬 실행
    doInsertionSort(insertion); // 삽입 정렬 실행
    doBubbleSort(bubble); // 버블 정렬 실행

    return 0;
}
