#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

int  CompareCount;
int  totalCompare;

void generateRandomArray(int array[]) { //���� ������ ���� �Լ�
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
        // Ÿ�ٰ��� ��´�.

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
            if (list[low] > pivot) break; // �ǹ����� ū �� �߰� �� ����

            low++;
        }

        // high�� �̵�
        while (high>=left) {

            CompareCount++;
            if (list[high] <= pivot) break; // �ǹ����� �۰ų� ���� �� �߰� �� ����

            high--;
        }

        CompareCount++; // low�� high �������� ���� ��� SWAP ����
        if (low < high)   SWAP(list[low], list[high], temp);
    }
 
        SWAP(list[left], list[high], temp);
        return high;

    }




// �� ���� �Լ����� �� Ƚ�� ����
void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);  // ���� �κ� ����
        quick_sort(list, q + 1, right); // ������ �κ� ����
    }
}


int getQuickSortCompareCount(int array[]) {
    CompareCount =0;  // �� Ƚ�� �ʱ�ȭ
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

    //��հ��� ��ȯ�ޱ� ���� ��ġ
    printf("Average Linear Search Compare Count: %.2f\n",
    getAverageLinearSearchCompareCount(array));

    //compareCount�� global variable�̹Ƿ�, ������ ���� ����
    CompareCount = 0;
    //array�� ���ؼ� ���� �����ϸ� �ȴ�.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", CompareCount);

    //���ĵ� Array�� ���ؼ� Binary Search 100ȸ ���� �� ��� ��Ƚ�� ���
    printf("Average Binary Search Compare Count: %.2f\n",
    getAverageBinarySearchCompareCount(array));

    printArray(array);
    return 0;
}