#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 


#define SIZE 100 
#define swap(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

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

int doInsertionSort(int list[],int printvalue) {
    int i, j, key;
    int count = 0;
    for (i = 1; i < SIZE; i++) {
        key = list[i];
        for (j = i - 1; j >= 0; j--) {
            count++;
            if (list[j] > key)  list[j + 1] = list[j];
            else break;
        }
        list[j + 1] = key;
    }
    if (printvalue == 0) {
        printf("InsertionSort Result : \n");
        print_list(list);
        printf("\n");
    }
    return count;
}


int doBubbleSort(int list[],int printvalue) {
    int i, j, temp;
  int count = 0;
    int flag = 0;
    for (i = SIZE - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (list[j] > list[j + 1]) {
                swap(list[j], list[j + 1], temp); count+=3;
                flag = 1;
            }
        }
        if (flag == 0) break;
    }
    if (printvalue == 0) {
        printf("BubbleSort Result : \n");
        print_list(list);
        printf("\n");
    }
    return count;
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

    printf("Selection sort Result : \n");
    doSelectionSort(select);

    int Totalcount = 0;
    for (int i = 1; i < 21; i++) {
       generateRandomData(randomData);
       Totalcount += doInsertionSort(randomData, i);
   }
    printf("InsertionSort compare average : %d\n", Totalcount/20);
    doInsertionSort(select,0);

    Totalcount = 0;
    for (int i = 1; i < 21; i++) {
        generateRandomData(randomData );
        Totalcount += doBubbleSort(randomData, i);
    }
    printf("BubbleSort move average : %d\n", Totalcount / 20);
    doBubbleSort(bubble ,0);
    return 0;
}