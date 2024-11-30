#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000  // �迭�� ũ�⸦ 1000���� ����

int compareCount = 0;  // ���� ������ �� ������ �� Ƚ���� ����

// ���� �迭 ���� �Լ�
void generateRandomArray(int* array)
{
    // �迭�� �� ��Ҹ� 0~999 ������ ���� ���ڷ� �ʱ�ȭ
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;
    }
}

// ���� Ž�� �Լ�
int linearSearch(int* array, int size, int target)
{
    int compare = 0;  // �� Ƚ�� �ʱ�ȭ

    // �迭�� ó������ ������ Ž��
    for (int i = 0; i < size; i++)
    {
        compare++;  // �� Ƚ�� ����

        // ã���� �ݺ��� ����
        if (array[i] == target)
        {
            break;
        }
    }
    return compare;  // Ž�� ���������� �� Ƚ�� ��ȯ
}

// ���� Ž�� ��� �� Ƚ�� ���
float getAverageLinearSearchCompareCount(int* array)
{
    int totalCompare = 0;  // �� �� Ƚ�� �ʱ�ȭ

    // ������ ���ڿ� ���� 100�� ���� Ž�� ����
    for (int i = 0; i < 100; i++)
    {
        int target = array[rand() % SIZE];  // �迭�� ������ ���� Ž�� ������� ����
        totalCompare += linearSearch(array, SIZE, target);  // ���� Ž���� �� Ƚ�� ����
    }
    return totalCompare / 100.0;  // ��� �� Ƚ�� ��ȯ
}

// �� ���� �Լ�
void quickSort(int* array, int left, int right)
{
    if (left >= right) return;

    int pivot = array[right];  // �ǹ��� �迭�� ������ ������ ����
    int i = left - 1;  // ���� ���� ����� ��ġ�� ��Ÿ���� ����

    // �ǹ����� ���� ���� �������� ����
    for (int j = left; j < right; j++)
    {
        compareCount++;  // �� Ƚ�� ����

        if (array[j] < pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // �ǹ��� �߾� ��ġ�� �̵�
    int temp = array[i + 1];
    array[i + 1] = array[right];
    array[right] = temp;

    // �¿� �κ� �迭 ����
    quickSort(array, left, i);
    quickSort(array, i + 2, right);
}

// �� ���� �� Ƚ�� ���
void getQuickSortCompareCount(int* array)
{
    compareCount = 0;  // �� Ƚ�� �ʱ�ȭ
    quickSort(array, 0, SIZE - 1);  // �迭 ��ü�� ����
}

// ���� Ž�� �Լ�
int binarySearch(int* array, int size, int target)
{
    int left = 0, right = size - 1;  // Ž�� ���� �ʱ�ȭ
    int compare = 0;  // �� Ƚ�� �ʱ�ȭ

    while (left <= right)
    {
        compare++;  // �� Ƚ�� ����
        int mid = left + (right - left) / 2;  // �߰� �ε��� ���

        if (array[mid] == target)
        {
            break;  // ���� ã���� ����
        }

        else if (array[mid] < target)
        {
            left = mid + 1;  // ������ �κ� �迭 Ž��
        }

        else
        {
            right = mid - 1;  // ���� �κ� �迭 Ž��
        }
    }
    return compare;  // Ž�� ���������� �� Ƚ�� ��ȯ
}

// ���� Ž�� ��� �� Ƚ�� ���
float getAverageBinarySearchCompareCount(int* array)
{
    int totalCompare = 0;  // �� �� Ƚ�� �ʱ�ȭ

    // ������ ���ڿ� ���� 100�� ���� Ž�� ����
    for (int i = 0; i < 100; i++)
    {
        int target = array[rand() % SIZE];  // �迭�� ������ ���� Ž�� ������� ����
        totalCompare += binarySearch(array, SIZE, target);  // ���� Ž���� �� Ƚ�� ����
    }
    return totalCompare / 100.0;  // ��� �� Ƚ�� ��ȯ
}

// �迭 ��� �Լ�
void printArray(int* array)
{
    printf("Array Sorting Result:\n");

    // �迭�� ó�� 20�� ��� ���
    for (int i = 0; i < 20; i++)
    {
        printf("%3d ", array[i]);
    }
    printf("\n");

    // �迭�� ������ 20�� ��� ���
    for (int i = SIZE - 20; i < SIZE; i++)
    {
        printf("%3d ", array[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    srand(time(NULL));  // ���� �õ� �ʱ�ȭ
    int array[SIZE];  // ũ�Ⱑ 1000�� �迭 ����

    generateRandomArray(array);  // ���� ������ �迭 �ʱ�ȭ

    // ���� Ž�� ��� �� Ƚ�� ���
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // �� ���� �� �� Ƚ�� ���
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // ���� Ž�� ��� �� Ƚ�� ���
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    // ���ĵ� �迭�� ó�� 20���� ������ 20�� ��� ���
    printArray(array);

    return 0;
}
