#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 


#define SIZE 100 
#define swap(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
int count = 0; int totalcount = 0;

void print_list(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        printf(" %02d", list[i]);
    }
    printf("\n");
}

void generateRandomData(int list[]) {

    for (int i = 0; i < 100; i++) {
        list[i] = rand() % 1000;
    }

}

void doSelectionSort(int list[]) {
    int i, j, least, temp;
    printf("selection sort result :\n");
    for (i = 0; i < SIZE-1; i++) {
        least = i;
        for (j = i + 1; j < SIZE; j++) {
            if (list[least] > list[j]) least = j;
        }
        swap(list[i], list[least], temp);
        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 98) {
            printf("step %d : ", i+1);
            print_list(list);
            printf("\n");
        }
    }
}

void doInsertionSort(int list[]) {
    int i, j, key;
    totalcount = 0;
    for(int  try= 0; try< 20;try++){
        count = 0;
        for (i = 1; i < SIZE; i++) {
            key = list[i];
            for (j = i - 1; j >= 0; j--) {
                count++;
                if (list[j] > key)  list[j + 1] = list[j];
                else break;
            }
            list[j + 1] = key;
        }
            if (try == 0 ){
                printf("InsertionSort Result : \n");
                    print_list(list);
                    printf("\n");
            }
            totalcount += count;
            generateRandomData(list);
        }
    printf("insertion compare average : %d\n", totalcount / 20);
    printf("\n");
}



void doBubbleSort(int list[]) {
    int i, j, temp;
    int flag = 0;
    totalcount = 0;
    for (int try = 0; try < 20; try++) {
        count = 0;
        for (i = SIZE - 1; i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (list[j] > list[j + 1]) {
                    swap(list[j], list[j + 1], temp); count += 3;
                    flag = 1;
                }
            }
            if (flag == 0) break;
        }
        if (try == 0) {
            printf("BubbleSort Result : \n");
            print_list(list);
            printf("\n");
        }
        totalcount += count;
        generateRandomData(list);
    }
    printf("Bubble compare average : %d\n", totalcount / 20);
}

int main() {
    srand((unsigned int)time(NULL));
  
    int randomData[SIZE];
    int select[SIZE];
    int bubble[SIZE];
    int insertion[SIZE];

    generateRandomData(randomData);

    for (int i = 0; i < SIZE; i++) {
        select[i] = randomData[i];
        bubble[i] = randomData[i];
        insertion[i] = randomData[i];
    }
    doSelectionSort(select);
    doInsertionSort(insertion);
    doBubbleSort(bubble);
    return 0;
}