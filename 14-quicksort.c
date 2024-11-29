#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100  // �迭�� ũ�⸦ 100���� ����
#define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )  // �� ������ ��ȯ�ϴ� ��ũ��

// ���� ���� ����
int comparisonCount = 0;  // �� Ƚ�� ī����
int moveCount = 0;       // �̵� Ƚ�� ī����
int isFirst = 0;         // ù ��° ���� ����
int totalComparisons = 0; // �� �� Ƚ��
int totalMoveCount = 0;  // �� �̵� Ƚ��
int rounds = 0;          // ���� ���� ��� ī��Ʈ

// �迭�� ���� ���� �����ϴ� �Լ�
void generateRandomArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;  // 0���� 999 ������ ���� �� ����
    }
}

// �迭�� �����ϴ� �Լ� (�ǹ��� �������� ������)
int partition(int list[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;  // low�� left�� �ʱ�ȭ
    high = right + 1;  // high�� right + 1�� �ʱ�ȭ
    pivot = list[left];  // �ǹ� ���� ù ��° ��ҷ� ����

    do
    {
        do
        {
            low++;
            comparisonCount++;  // �� Ƚ�� ����
        } while (low <= right && list[low] < pivot);  // �ǹ����� ū ���� ã�� ������ ����

        do
        {
            high--;
            comparisonCount++;  // �� Ƚ�� ����
        } while (high >= left && list[high] > pivot);  // �ǹ����� ���� ���� ã�� ������ ����

        if (low < high)
        {
            SWAP(list[low], list[high], temp);  // ������ �߰ߵǸ� �� ���� ��ȯ
            moveCount += 3;  // �̵� Ƚ�� ���� (3���� �̵�)
        }
    } while (low < high);  // low�� high���� ������ ��� ����

    SWAP(list[left], list[high], temp);  // �ǹ� ���� �ùٸ� ��ġ�� ��ȯ
    moveCount += 3;  // �̵� Ƚ�� ����

    return high;  // �ǹ��� ���� �ε����� ��ȯ
}

// �� ������ �����ϴ� �Լ� (�ݺ��� ���)
void doQuickSort(int list[], int left, int right)
{
    // ������ ����ϱ� ���� �ִ� ũ�⸦ SIZE�� ����
    int stack[SIZE];
    int top = -1;  // ������ top�� -1�� �ʱ�ȭ

    // ù ��° ������ ���ÿ� Ǫ��
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0)  // ������ ������� ������ �ݺ�
    {
        // ���ÿ��� �����ʰ� ���� �ε����� ��
        right = stack[top--];
        left = stack[top--];

        if (left < right)  // ���� �ε����� ������ �ε������� ������
        {
            int q = partition(list, left, right);  // ��Ƽ�� �Լ��� ȣ���Ͽ� �ǹ� ��ġ ã��

            // 10ȸ���� 40���� 60 ��ġ�� ���� ���
            if (rounds % 10 == 0 && isFirst == 0)
            {
                for (int i = 40; i < 60; i++)
                    printf("%d ", list[i]);  // �ش� ������ �� ���
                printf("\n\n");
            }
            rounds++;  // ���� ���� ī��Ʈ ����

            // ���� �κа� ������ �κ��� ������ ���ÿ� Ǫ��
            stack[++top] = left;      // ���� �κ� ����
            stack[++top] = q - 1;    // �ǹ� ���� �κ� ����
            stack[++top] = q + 1;    // �ǹ� ������ �κ� ����
            stack[++top] = right;     // ������ �κ� ����
        }
    }
}

// �迭�� ��Ҹ� ����ϴ� �Լ�
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);  // �� ��� ���
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    srand(time(NULL));  // ���� �õ� �ʱ�ȭ
    int array[SIZE];  // �迭 ����

    for (int i = 0; i < 20; i++)  // 20ȸ ����
    {
        generateRandomArray(array);  // ���� �迭 ����
        comparisonCount = 0;  // �� Ƚ�� �ʱ�ȭ
        moveCount = 0;       // �̵� Ƚ�� �ʱ�ȭ
        rounds = 0;          // ���� ���� ī��Ʈ �ʱ�ȭ

        if (i == 0)  // ù ��° ������ ���
        {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);  // �� ���� ����

            printf("Result\n");
            printArray(array, SIZE);  // ���ĵ� �迭 ���
            isFirst++;  // ù ��° ���� ǥ��
        }
        else
        {
            doQuickSort(array, 0, SIZE - 1);  // ���� ���࿡���� �� ���� ����
        }
        totalComparisons += comparisonCount;  // �� �� Ƚ�� ������Ʈ
        totalMoveCount += moveCount;          // �� �̵� Ƚ�� ������Ʈ
    }
    // ��� �� Ƚ���� ��� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;  // ���α׷� ����
}
