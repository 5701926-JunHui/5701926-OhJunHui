#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0; // �� Ƚ��
int moveCount = 0; // �̵� Ƚ��
int totalComparisons = 0; // �� �� Ƚ��
int totalMoves = 0; // �� �̵� Ƚ��
int isFirst = 0; // ù ��° ���� ����
int rounds = 0; // ���� Ƚ�� ����

// ���� �迭 ���� �Լ�
void generateRandomArray(int array[]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        array[i] = rand() % 1000; // 0-999 ������ ���� ���� ����
    }
}

// �迭 ��� �Լ�
void printArray(int array[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        printf("%3d ", array[i]); // �迭�� �� ��Ҹ� ���
    }
    printf("\n");
}

// �迭 ���� �Լ�
void merge(int array[], int left, int mid, int right) 
{
    int i, j, k;
    int n1 = mid - left + 1; // ���� �迭�� ũ��
    int n2 = right - mid; // ������ �迭�� ũ��

    // ���ʰ� ������ �迭�� ���� �Ҵ�
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // ���ʰ� ������ �迭�� �� ����
    for (i = 0; i < n1; i++)
        L[i] = array[left + i];

    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    i = 0; j = 0; k = left; // �ε��� �ʱ�ȭ

    // ���� ����
    while (i < n1 && j < n2) 
    {
        comparisonCount++; // �� Ƚ�� ����

        if (L[i] <= R[j]) 
        {
            array[k] = L[i]; // ���� �迭�� �� ����
            i++;
        }
        else 
        {
            array[k] = R[j]; // ������ �迭�� �� ����
            j++;
        }
        moveCount++; // �̵� Ƚ�� ����
        k++;
    }

    // ���� ���� �迭 ��� ����
    while (i < n1) 
    {
        array[k] = L[i];
        i++;
        k++;
        moveCount++;
    }

    // ���� ������ �迭 ��� ����
    while (j < n2) 
    {
        array[k] = R[j];
        j++;
        k++;
        moveCount++;
    }

    free(L); // ���� �Ҵ� ����
    free(R); // ���� �Ҵ� ����

    // ������ �Ϸ�� �� rounds ����
    rounds++;

    // rounds�� 10�� ����� �� �迭 ���� ���
    if (rounds % 10 == 0 && isFirst == 0) 
    {
        for (int i = 0; i < 10; i++)
            printf("%3d ", array[i]); // �迭�� ó�� 10�� ��� ���

        printf("| "); // ���м� ���

        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)
            printf("%3d ", array[i]); // �߾� ��ġ���� 10�� ��� ���
        printf("\n\n");
    }
}

// �պ� ���� �Լ� (�ݺ��� ���)
void doMergeSort(int array[], int left, int right) 
{
    for (int currentSize = 1; currentSize <= right - left; currentSize *= 2) 
    {
        for (int leftStart = left; leftStart < right; leftStart += 2 * currentSize) 
        {
            int mid = leftStart + currentSize - 1; // �߰� �ε���
            int rightEnd = leftStart + 2 * currentSize - 1; // ������ �� �ε���

            if (mid >= right) // �߰� �ε����� ������ ������ ����
                break;

            if (rightEnd > right) // ������ �� �ε��� ����
                rightEnd = right;

            merge(array, leftStart, mid, rightEnd); // ���� ȣ��
        }
    }
}

int main(void) 
{
    int array[SIZE];

    srand(time(NULL)); // ���� �õ� �ʱ�ȭ

    for (int i = 0; i < 20; i++) 
    {
        generateRandomArray(array); // ���� �迭 ����
        comparisonCount = 0; // �� Ƚ�� �ʱ�ȭ
        moveCount = 0; // �̵� Ƚ�� �ʱ�ȭ

        if (i == 0) 
        {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1); // �պ� ���� ����

            printf("Result\n");
            printArray(array, SIZE); // ���ĵ� �迭 ���
            isFirst++; // ù ��° ���� �÷��� ����
        }
        else 
        {
            doMergeSort(array, 0, SIZE - 1); // ���� �׽�Ʈ�� ���� ���� ����
        }
        totalComparisons += comparisonCount; // �� �� Ƚ�� ����
        totalMoves += moveCount; // �� �̵� Ƚ�� ����
    }
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0); // ��� �� Ƚ�� ���
    printf("Average Moves: %.2f\n", totalMoves / 20.0); // ��� �̵� Ƚ�� ���

    return 0;
}
