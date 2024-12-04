#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int CompareCount;

void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000;
    }
}

int partition(int list[], int left, int right) {
    int pivot = list[left];
    int low = left + 1;
    int high = right;
    int temp;

    while (low <= high) {
        while (low <= right && list[low] <= pivot) low++;
        while (high >= left && list[high] > pivot) high--;
        if (low < high) SWAP(list[low], list[high], temp);
    }
    SWAP(list[left], list[high], temp);
    return high;
}

void QuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        QuickSort(list, left, q - 1);
        QuickSort(list, q + 1, right);
    }
}

double getAverageBinarySearchCompareCount(int array[]) {
    double totalCompare = 0.0;
    for (int i = 0; i < SIZE; i++) {
        int key = array[rand() % SIZE];
        int low = 0, high = SIZE - 1, CompareCount = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (array[mid] == key) {
                CompareCount++;
                break;
            }

            else if (array[mid] > key) {
                high = mid - 1;
                CompareCount++;
            }

            else { low = mid + 1; CompareCount++; }

            CompareCount++;
        }
        totalCompare += CompareCount;
    }
    return totalCompare / SIZE;
}

int interpolationSearch(int arr[], int n, int x)
{
    int low = 0, high = (n - 1);
 
    while (low<=high)
    {
       
        CompareCount++;
        if (x < arr[low]) break;
        CompareCount++;
        if (x > arr[high]) break;


        CompareCount++;
        if (low== high)
        {
            CompareCount++;
            if (arr[low]) return low;
            else return -1;

        }
  
        int pos = low + (((double)(high - low) /
            (arr[high] - arr[low])) * (x - arr[low]));

        CompareCount++;
            if (arr[pos] == x) {
          
                return pos;
            }
           else if (arr[pos] < x) {
                
                low = pos + 1;
            }
            else {
        
                high = pos - 1;
            }
           
    }
    return -1;
}



double getAverageInterpolationSearchComparecount(int array[]) {
    CompareCount = 0;
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];
        interpolationSearch(array, SIZE - 1, target);
    }
    return (double)CompareCount / SIZE;
}

void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

int main() {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);
    QuickSort(array, 0, SIZE - 1);
    printArray(array);
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));
    return 0;
}