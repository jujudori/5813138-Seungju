#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

int  CompareCount;
int  totalCompare;

void generateRandomArray(int array[]) { //랜덤 데이터 생성 함수
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int* array) {

    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

//++++
double getAverageLinearSearchCompareCount(int array[])
{
    totalCompare = 0;
    int key;
    for (int i = 0; i < 100; i++) {
         key = array[rand() % SIZE];
        // 타겟값을 잡는다.

        CompareCount = 0;

        for (int j = 0; j < SIZE; j++) {
            CompareCount++;
            if (array[j] == key) break; 

        }

        totalCompare += CompareCount;
    }
        return (double)totalCompare / 100; 
}



int partition(int list[], int left, int right) {
    int pivot = list[left];
    int low = left + 1;
    int high = right;
    int temp;

    while (low<=high) {

        while (low<=right) {
            CompareCount++;
            if (list[low] > pivot) break; // 피벗보다 큰 값 발견 시 정지

            low++;
        }

        // high를 이동
        while (high>=left) {

            CompareCount++;
            if (list[high] <= pivot) break; // 피벗보다 작거나 같은 값 발견 시 정지

            high--;
        }

        CompareCount++; // low와 high 교차하지 않은 경우 SWAP 수행
        if (low < high)   SWAP(list[low], list[high], temp);
    }
 
        SWAP(list[left], list[high], temp);
        return high;

    }




// 퀵 정렬 함수에서 비교 횟수 추적
void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);  // 왼쪽 부분 정렬
        quick_sort(list, q + 1, right); // 오른쪽 부분 정렬
    }
}


int getQuickSortCompareCount(int array[]) {
    CompareCount =0;  // 비교 횟수 초기화
    quick_sort(array, 0, SIZE - 1);
    return CompareCount;  
}

double getAverageBinarySearchCompareCount(int array[])
{
    int key;
     totalCompare = 0;
    for (int i = 0; i < 100; i++) {
        key = array[rand() % 1000];

        int middle;
        int low = 0;
        int high = SIZE - 1;
        CompareCount = 0;

        while (low <= high) {
            middle = (low + high) / 2;
            CompareCount++;
            if (array[middle] == key) {
                break;
            }
            else if (key > array[middle])
            {
                low = middle + 1;
    
            }
            else {
                high = middle - 1;
             
            }
            }

        totalCompare += CompareCount;
    }
    return (double)totalCompare / 100;
}



int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);

    //평균값을 반환받기 위한 조치
    printf("Average Linear Search Compare Count: %.2f\n",
    getAverageLinearSearchCompareCount(array));

    //compareCount가 global variable이므로, 다음과 같이 구현
    CompareCount = 0;
    //array에 대해서 직접 정렬하면 된다.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", CompareCount);

    //정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n",
    getAverageBinarySearchCompareCount(array));

    printArray(array);
    return 0;
}