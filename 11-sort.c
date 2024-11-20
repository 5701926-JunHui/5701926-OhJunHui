#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 // �迭�� ũ�� ����
#define TRIALS 20 // ���� �õ� Ƚ�� ����


// ���� ������ ���� �Լ�
void generateRandomData(int arr[]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        arr[i] = rand() % 1000; // 0���� 999 ������ ���� ���� ����
    }
}

// �迭 ��� �Լ�
void printArray(int arr[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        printf("%d ", arr[i]); // �迭�� �� ��� ���
    }
    printf("\n");
}

// ���� ����
void doSelectionSort(int arr[]) 
{
    int tempArr[SIZE]; // ������ ���� �ӽ� �迭

    for (int i = 0; i < SIZE; i++) 
    {
        tempArr[i] = arr[i]; // ���� �迭�� �ӽ� �迭�� ����
    }

    printf("Selection Sort:\n\n");

    int step = 0; // �ܰ� ī����

    for (int i = 0; i < SIZE - 1; i++) 
    {
        int minIdx = i; // �ּҰ��� �ε��� �ʱ�ȭ

        for (int j = i + 1; j < SIZE; j++) 
        {
            if (tempArr[j] < tempArr[minIdx]) 
            {
                minIdx = j; // �ּҰ��� �ε��� ������Ʈ
            }
        }

        // Swap
        int temp = tempArr[minIdx];
        tempArr[minIdx] = tempArr[i];
        tempArr[i] = temp;

        // Ư�� �ܰ迡�� ���
        step++;
        if (step == 10 || step % 20 == 10 || step == SIZE - 1) 
        {
            printf("Step %d: ", step);
            printArray(tempArr, SIZE); // ���� �迭 ���� ���
            printf("\n");
        }
    }
    printf("\n");
}

// ���� ����
void doInsertionSort(int arr[])
{
    int arrCopy[SIZE]; // ������ ���� ���� �迭

    for (int i = 0; i < SIZE; i++)
    {
        arrCopy[i] = arr[i]; // ���� �迭�� ����
    }

    int compareSum = 0; // �� Ƚ���� ������ ����
    int compareCount = 0; // �� �õ������� �� Ƚ��

    for (int t = 0; t < TRIALS; t++)
    {
        int arrTrial[SIZE]; // ������ ���� ���� �迭
        for (int i = 0; i < SIZE; i++)
        {
            arrTrial[i] = arrCopy[i]; // ���� �迭 ����
        }

        compareCount = 0; // �� �õ������� �� Ƚ�� �ʱ�ȭ

        for (int i = 1; i < SIZE; i++)
        {
            int key = arrTrial[i]; // ���� ������ ���
            int j = i - 1;

            while (j >= 0 && arrTrial[j] > key)
            {
                arrTrial[j + 1] = arrTrial[j]; // ��Ҹ� �� ĭ�� �̵�
                j--;
                compareCount++; // �� Ƚ�� ����
            }
            arrTrial[j + 1] = key; // ��� ����
            compareCount++; // ������ �� Ƚ�� ����
        }
        compareSum += compareCount; // �� �� Ƚ���� �߰�

        if (t == 0) 
        {
            printf("\nInsertion Sort Compare Average: %d\n", compareSum / TRIALS); // ��� �� Ƚ�� ���
            printf("Insertion Sort Result:\n"); // ���� ��� ���
            printArray(arrTrial, SIZE);
        }
    }
}

// ���� ����
void doBubbleSort(int arr[])
{
    int arrCopy[SIZE]; // ������ ���� ���� �迭

    for (int i = 0; i < SIZE; i++)
    {
        arrCopy[i] = arr[i]; // ���� �迭�� ����
    }

    int moveSum = 0; // �̵� Ƚ���� ������ ����
    int moveCount = 0; // �� �õ������� �̵� Ƚ��

    for (int t = 0; t < TRIALS; t++)
    {
        int arrTrial[SIZE]; // ������ ���� ���� �迭
        for (int i = 0; i < SIZE; i++)
        {
            arrTrial[i] = arrCopy[i]; // ���� �迭 ����
        }

        moveCount = 0; // �� �õ������� �̵� Ƚ�� �ʱ�ȭ

        for (int i = 0; i < SIZE - 1; i++)
        {
            for (int j = 0; j < SIZE - i - 1; j++)
            {
                if (arrTrial[j] > arrTrial[j + 1])
                {
                    int temp = arrTrial[j];
                    arrTrial[j] = arrTrial[j + 1];
                    arrTrial[j + 1] = temp;
                    moveCount++; // �̵� Ƚ�� ����
                }
            }
        }
        moveSum += moveCount; // �� �̵� Ƚ���� �߰�

        if (t == 0) {
            printf("\nBubble Sort Move Average: %d\n", moveSum / TRIALS); // ��� �̵� Ƚ�� ���
            printf("Bubble Sort Result:\n");    // ���� ��� ���
            printArray(arrTrial, SIZE);
        }
    }
}


int main(void)
{
    int randomData[SIZE]; // ���� �����͸� ������ �迭

    // ���� ������ ����
    srand(time(0));
    generateRandomData(randomData); // ���� ������ ���� �Լ� ȣ��

    // ���� ����
    doSelectionSort(randomData); // ���� ���� ����
    doInsertionSort(randomData); // ���� ���� ����
    doBubbleSort(randomData); // ���� ���� ����

    return 0;
}
