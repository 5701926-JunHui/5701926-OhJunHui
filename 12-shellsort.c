#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100 // �迭�� ũ�� ����

// ���� ���ڸ� �����Ͽ� �迭�� �����ϴ� �Լ�
void generateRandomNumbers(int array[])
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = rand() % 1000; // 0-999 ������ ���� ���� ����
    }
}

// �� ������ �����ϴ� �Լ�
void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount)
{
    int n = ARRAY_SIZE; // �迭�� ũ��
    int gap, i, j, temp;

    // gap ��� (gapType�� ���� �ٸ��� ����)
    if (gapType == 2)
    {
        gap = n / 2; // gap�� n/2�� ����
    }
    else
    {
        gap = n / 3; // gap�� n/3�� ����
    }

    // gap�� 0���� ū ���� ��� ���� ����
    while (gap > 0)
    {
        printf("Sorting with gap = %d: ", gap);
        printf("\n");

        for (i = gap; i < n; i++)
        {
            temp = array[i]; // ���� ��� ����
            j = i;

            // �̵� �� �� ī��Ʈ
            (*moveCount)++;

            // ��Ҹ� ������ ��ġ�� �̵�
            while (j >= gap && array[j - gap] > temp)
            {
                array[j] = array[j - gap]; // ��� �̵�
                j -= gap; // �ε��� ������Ʈ
                (*comparisonCount)++; // �� ī��Ʈ ����
                (*moveCount)++; // �̵� ī��Ʈ ����
            }
            array[j] = temp; // ������ ��ġ�� ��� ����
            (*moveCount)++;
        }

        // ���� �迭 ���� ���
        for (int k = 0; k < n; k++)
        {
            printf("%d ", array[k]);
        }
        printf("\n\n");

        gap /= (gapType == 2 ? 2 : 3); // gap ���̱�
    }

    // ���� �Ϸ� �� ���� �迭 ���
    printf("Sorted shellArray (gap = %d):\n", gapType);
    for (int k = 0; k < n; k++)
    {
        printf("%d ", array[k]);
    }
    printf("\n\n");
}

// ���� ������ �����ϴ� �Լ�
void doInsertionSort(int array[], int* comparisonCount, int* moveCount)
{
    for (int i = 1; i < ARRAY_SIZE; i++)
    {
        int key = array[i]; // ���� Ű ����
        int j = i - 1;

        // �̵� �� �� ī��Ʈ
        (*moveCount)++;

        // Ű�� ������ ��ġ�� �̵�
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j]; // ��� �̵�
            j--; // �ε��� ������Ʈ
            (*comparisonCount)++; // �� ī��Ʈ ����
            (*moveCount)++; // �̵� ī��Ʈ ����
        }
        array[j + 1] = key; // ������ ��ġ�� Ű ����
        (*moveCount)++;
    }

    // ���ĵ� �迭 ���
    printf("Sorted insertionArray:\n");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

int main(void)
{
    int array[ARRAY_SIZE]; // ������ �迭
    int comparisonCount = 0; // �� Ƚ�� �ʱ�ȭ
    int moveCount = 0; // �̵� Ƚ�� �ʱ�ȭ

    srand(time(NULL)); // ���� �õ� �ʱ�ȭ
    generateRandomNumbers(array); // ���� ���� ����

    // �� ���� (n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    srand(time(NULL)); // ���� �õ� �ʱ�ȭ
    generateRandomNumbers(array); // ���� ���� ����

    // �� ���� (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    srand(time(NULL));
    generateRandomNumbers(array);

    // ���� ����
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
