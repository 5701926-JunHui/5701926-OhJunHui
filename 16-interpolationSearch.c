#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

int comparisonCount = 0;

// �迭�� ������ ���� ä���ִ� �Լ�
void generateRandomArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 10000; // 0���� 9999 ������ ���� ����
    }
}

// �� ������ ���� �Լ�
// �ǹ��� �������� �迭�� �� �κ����� ����
int partition(int list[], int left, int right)
{
    int pivot = list[left]; // �ǹ��� �迭�� ù ��° ���
    int low = left + 1;
    int high = right;

    while (1)
    {
        // �����ʿ��� �ǹ����� ���� ���� ã��
        while (low <= high && list[high] >= pivot)
        {
            high--;
            comparisonCount++;
        }
        // ���ʿ��� �ǹ����� ū ���� ã��
        while (low <= high && list[low] <= pivot)
        {
            low++;
            comparisonCount++;
        }
        // low�� high�� �����ϸ� �ݺ� ����
        if (low > high)
            break;

        // low�� high ��ġ�� ���� ��ȯ
        int temp = list[low];
        list[low] = list[high];
        list[high] = temp;
    }
    // �ǹ��� high ��ġ�� ���� ��ȯ
    list[left] = list[high];
    list[high] = pivot;

    return high;
}

// �� ���� �Լ�
void QuickSort(int list[], int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right); // ������ ���
        QuickSort(list, left, q - 1);        // ���� �κ� ����
        QuickSort(list, q + 1, right);       // ������ �κ� ����
    }
}

// ���� Ž�� �Լ�
int binarySearch(int arr[], int size, int target)
{
    int left = 0, right = size - 1;
    comparisonCount = 0; // �� Ƚ�� �ʱ�ȭ

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // �߰� �ε��� ���
        comparisonCount++;

        if (arr[mid] == target) // �߰� ���� ��� ���� ��ġ
        {
            return mid;
        }
        else if (arr[mid] < target) // ��� ���� �� ũ�� ������ Ž��
        {
            left = mid + 1;
        }
        else // ��� ���� �� ������ ���� Ž��
        {
            right = mid - 1;
        }
    }
    return -1; // ��� ���� �迭�� ����
}

// ���� Ž�� �Լ�
int interpolationSearch(int arr[], int size, int target)
{
    int low = 0, high = size - 1;

    while (low <= high && target >= arr[low] && target <= arr[high])
    {
        if (low == high)
        {
            if (arr[low] == target) // �迭 ũ�Ⱑ 1�� �� ��� �� ã��
            {
                return low;
            }
            return -1; // ���� ���� ���
        }

        // ���� �� ���
        int pos = low + ((double)(high - low) / (arr[high] - arr[low]) * (target - arr[low]));
        comparisonCount++;

        if (arr[pos] == target) // ���� ���� ��� ���� ��ġ
        {
            return pos;
        }
        if (arr[pos] < target) // ���� ���� ��� ������ ����
        {
            low = pos + 1;
        }
        else // ���� ���� ��� ������ ŭ
        {
            high = pos - 1;
        }
    }
    return -1; // ��� ���� �迭�� ����
}

// �迭�� ����ϴ� �Լ�
void printArray(int* array)
{
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");

    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// ���� Ž���� ��� �� Ƚ���� ����ϴ� �Լ�
double getAverageBinarySearchCompareCount(int array[]) 
{
    int totalCompare = 0;

    for (int i = 0; i < 1000; i++) 
    {
        int target = array[rand() % SIZE]; // �迭���� ������ �� ����
        int left = 0;
        int right = SIZE - 1;
        int compare = 0;

        while (left <= right) 
        {
            compare++;
            int mid = left + (right - left) / 2;

            if (array[mid] == target) 
            { // ��� ���� ã��
                break;
            }
            else if (array[mid] < target) 
            { // ������ Ž��
                left = mid + 1;
            }
            else { // ���� Ž��
                right = mid - 1;
            }
        }
        totalCompare += compare; // �� Ƚ�� ����
    }
    return totalCompare / 1000.0; // ��� ��ȯ
}

// ���� Ž���� ��� �� Ƚ���� ����ϴ� �Լ�
double getAverageInterpolationSearchComparecount(int array[]) 
{
    int totalCompare = 0;

    for (int i = 0; i < 1000; i++) 
    {
        int target = array[rand() % SIZE]; // �迭���� ������ �� ����
        int low = 0;
        int high = SIZE - 1;
        int compare = 0;

        while (low <= high && array[high] != array[low]) 
        {
            compare++;

            int j = low + ((double)(target - array[low]) / (array[high] - array[low])) * (high - low);

            if (target > array[j])
                low = j + 1;
            else if (target < array[j])
                high = j - 1;
            else 
            {
                compare++;
                break;
            }
        }

        if (low < SIZE && array[low] == target) compare++;

        totalCompare += compare; // �� Ƚ�� ����
    }
    return totalCompare / 1000.0; // ��� ��ȯ
}


int main(int argc, char* argv[])
{
    srand(time(NULL)); // ���� �õ� ����
    int array[SIZE];
    generateRandomArray(array); // �迭 ����

    QuickSort(array, 0, SIZE - 1); // �迭 �� ����
    printArray(array); // ���ĵ� �迭 ���

    // ���� Ž�� ��� �� Ƚ�� ���
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));

    // ���� Ž�� ��� �� Ƚ�� ���
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));

    return 0;
}
