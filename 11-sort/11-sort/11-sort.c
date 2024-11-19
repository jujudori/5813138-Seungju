#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 

#define SIZE 100 // �迭�� ũ�� ����
#define swap(x, y, t) ((t) = (x), (x) = (y), (y) = (t)) // swap ��ũ�� ����

int count = 0; // ���� ���࿡���� �� Ƚ��
int totalcount = 0; // ���� �� ������ �� �� �� Ƚ��

// �迭�� ����ϴ� �Լ�
void print_list(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        printf(" %02d", list[i]); // �� �ڸ��� ��� (�տ� 0 ����)
    }
    printf("\n");
}

// 0~999 ������ ���� ���ڷ� �迭�� ä��� �Լ�
void generateRandomData(int list[]) {
    for (int i = 0; i < 100; i++) {
        list[i] = rand() % 1000;
    }
}

// ���� ���� �Լ�
void doSelectionSort(int list[]) {
    int i, j, least, temp;
    printf("selection sort result :\n");
    for (i = 0; i < SIZE - 1; i++) { // �迭�� ���� - 1 ��ŭ �ݺ�
        least = i; // ���� ��ġ�� �ּҰ����� ����
        for (j = i + 1; j < SIZE; j++) { // ������ ��ҿ� ��
            if (list[least] > list[j])
                least = j; // �� ���� ���� ã���� �ּҰ� �ε��� ����
        }
        swap(list[i], list[least], temp); // �ּҰ��� ���� ��ġ�� �̵�
        // Ư�� �ܰ迡�� �迭 ���¸� ���
        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 98) {
            printf("step %d : ", i + 1);
            print_list(list);
            printf("\n");
        }
    }
}

// ���� ���� �Լ�
void doInsertionSort(int list[]) {
    int i, j, key;
    totalcount = 0; // �� �� Ƚ���� �ʱ�ȭ
    for (int try = 0; try < 20; try++) { // ��� �� Ƚ���� ����ϱ� ���� 20�� ����
        count = 0; // ���ึ�� �� Ƚ�� �ʱ�ȭ
        for (i = 1; i < SIZE; i++) { // �� ��° ��Һ��� ����
            key = list[i]; // ���� ��Ҹ� ����
            for (j = i - 1; j >= 0; j--) { // �������� �̵��ϸ� ��
                count++;
                if (list[j] > key)
                    list[j + 1] = list[j]; // ū ���� ���������� �̵�
                else
                    break; // ���� ��ġ�� ã���� ����
            }
            list[j + 1] = key; // ��� ����
        }
        // ù ��° ���࿡�� ��� ���
        if (try == 0) {
            printf("InsertionSort Result : \n");
            print_list(list);
            printf("\n");
        }
        totalcount += count; // �� Ƚ���� ����
        generateRandomData(list); // �迭�� ���� ���� ����
    }
    printf("insertion compare average : %d\n", totalcount / 20); // ��� �� Ƚ�� ���
    printf("\n");
}

// ���� ���� �Լ�
void doBubbleSort(int list[]) {
    int i, j, temp;
    int flag = 0; // ���� ���θ� ��Ÿ���� �÷���
    totalcount = 0; // �� �� Ƚ���� �ʱ�ȭ
    for (int try = 0; try < 20; try++) { // ��� �� Ƚ���� ����ϱ� ���� 20�� ����
        count = 0; // ���ึ�� �� Ƚ�� �ʱ�ȭ
        for (i = SIZE - 1; i > 0; i--) { // �迭�� ������ ����
            for (j = 0; j < i; j++) { // ���� �������� ������ ��Ҹ� ��
                if (list[j] > list[j + 1]) {
                    swap(list[j], list[j + 1], temp); // ��� ��ȯ
                    count += 3; // �� �� ��ȯ Ƚ�� ����
                    flag = 1; // ��ȯ �߻�
                }
            }
            if (flag == 0)
                break; // ���� �Ϸ� �� ���� ����
        }
        // ù ��° ���࿡�� ��� ���
        if (try == 0) {
            printf("BubbleSort Result : \n");
            print_list(list);
            printf("\n");
        }
        totalcount += count; // �� Ƚ���� ����
        generateRandomData(list); // �迭�� ���� ���� ����
    }
    printf("Bubble compare average : %d\n", totalcount / 20); // ��� �� Ƚ�� ���
}

// ���� �Լ�
int main() {
    srand((unsigned int)time(NULL)); // ���� �õ� ����

    int randomData[SIZE]; // ���� ������ ����
    int select[SIZE]; // ���� ���Ŀ� �迭
    int bubble[SIZE]; // ���� ���Ŀ� �迭
    int insertion[SIZE]; // ���� ���Ŀ� �迭

    generateRandomData(randomData); // ���� ������ ����

    // �迭 ����
    for (int i = 0; i < SIZE; i++) {
        select[i] = randomData[i];
        bubble[i] = randomData[i];
        insertion[i] = randomData[i];
    }

    doSelectionSort(select); // ���� ���� ����
    doInsertionSort(insertion); // ���� ���� ����
    doBubbleSort(bubble); // ���� ���� ����

    return 0;
}
