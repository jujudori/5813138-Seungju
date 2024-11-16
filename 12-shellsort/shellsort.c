#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 
#define ARRAY_SIZE 100 

 // 중복 확인을 위한 bool 사용

void generateRandomNumbers(int array[]) {
    int count = 0;

    for (int i = 0; i < 100; i++) {
        array[i] = rand() % 1000;
    }

    while (count < ARRAY_SIZE) {
        int num = rand() % 1000;  
        bool exists = false;

        for (int i = 0; i < count; i++) {
            if (array[i] == num) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            array[count++] = num;
        }
    }
}


void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount, int printvalue) {
    int gap, i, j, temp;
    int comparisons = 0, moves = 0;


    if (gapType == 2) {
        for (gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) {
            for (i = gap; i < ARRAY_SIZE; i++) {
                temp = array[i];
                moves++;
                for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                    array[j] = array[j - gap];
                    comparisons++;
                    moves++;
                }
                array[j] = temp;
                moves++;
            }
            if (printvalue == 0) {
                printf("Gap %d:\n", gap);
                for (int i = 0; i < 20; i++) {
                    printf("%2d ", array[i]);
                }
                printf("...\n");
            }
        }
        if (printvalue == 0&&gapType!=3) {
            printf("\n");
            printf("sorted shell array gap=2 : ");
            printArray(array);
        }
    }
    else if (gapType == 3) {
        for (gap = ARRAY_SIZE / 3; gap > 0; gap /= 3) {
            for (i = gap; i < ARRAY_SIZE; i++) {
                temp = array[i];
                moves++;
                for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                    array[j] = array[j - gap];
                    comparisons++;
                    moves++;
                }
                array[j] = temp;
                moves++;
            }

            if (printvalue == 0) {
                printf("Gap %d:\n", gap);
                for (int i = 0; i < 20; i++) {
                    printf("%2d ", array[i]);
                }
                printf("...\n");
            }
        }
    }
    if (printvalue == 0 && gapType!=2) {
        printf("\n");
        printf("sorted shell array gap= 3 : ");
        printArray(array);
    }
    *comparisonCount = comparisons;
    *moveCount = moves;
}


void doInsertionSort(int array[], int* comparisonCount, int* moveCount,int printvalue) {
    int i, j, key;
    int comparisons = 0, moves = 0;

    for (i = 1; i < ARRAY_SIZE; i++) {
        key = array[i];
        moves++;  
        for (j = i - 1; j >= 0 && array[j] > key; j--) {
            array[j + 1] = array[j];
            comparisons++;
            moves++;
        }
        array[j + 1] = key;
        moves++; 
    }

    if (printvalue == 0) {
        printf("sorted Insertion array : ");
        printArray(array);
    }
    *comparisonCount = comparisons;
    *moveCount = moves;
}

int main() {
	int array[ARRAY_SIZE];
    int shell2[ARRAY_SIZE];
    int shell3[ARRAY_SIZE];
    int insertion[ARRAY_SIZE];
    int comparisonCount, moveCount;
    srand(time(NULL));
	generateRandomNumbers(array);


	// Shell Sort
	printf("Shell Sort (n/2):\n");

    for (int i = 0; i < ARRAY_SIZE; i++) {
        shell2[i] = array[i];
        shell3[i] = array[i];
        insertion[i] = array[i];
    }

    doShellSort(shell2, 2, &comparisonCount, &moveCount, 0);


    int totalComparisons = 0, totalMoves = 0;
    for (int i = 1; i < 21; i++) {
        generateRandomNumbers(array);
        doShellSort(array, 2,&comparisonCount, &moveCount, i);
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }
    comparisonCount = totalComparisons /20;
    moveCount = totalMoves / 20;

	printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);
    
    
	printf("Shell Sort (n/3):\n");

    doShellSort(shell3, 3, &comparisonCount, &moveCount, 0);

    totalComparisons = 0, totalMoves = 0;
    for (int i = 1; i < 21; i++) {
        generateRandomNumbers(array);
        doShellSort(array, 3, &comparisonCount, &moveCount, i);
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }
    comparisonCount = totalComparisons / 20;
    moveCount = totalMoves / 20;
	printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

 //Insertion Sort – 보너스(보너스 풀지 않는 경우 하단 없어도 됨)

    printf("Insertion Sort:\n");
    doInsertionSort(insertion, &comparisonCount, &moveCount, 0);

 totalComparisons = 0, totalMoves = 0;
    for (int i = 1; i < 21; i++) {
        generateRandomNumbers(array);
        doInsertionSort(array, &comparisonCount, &moveCount,i);
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }
    comparisonCount = totalComparisons / 20;
    moveCount = totalMoves / 20;
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);
	return 0;
}