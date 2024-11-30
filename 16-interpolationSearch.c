#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

int comparisonCount = 0;

// 배열에 무작위 값을 채워넣는 함수
void generateRandomArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 10000; // 0부터 9999 사이의 난수 생성
    }
}

// 퀵 정렬의 분할 함수
// 피벗을 기준으로 배열을 두 부분으로 나눔
int partition(int list[], int left, int right)
{
    int pivot = list[left]; // 피벗은 배열의 첫 번째 요소
    int low = left + 1;
    int high = right;

    while (1)
    {
        // 오른쪽에서 피벗보다 작은 값을 찾음
        while (low <= high && list[high] >= pivot)
        {
            high--;
            comparisonCount++;
        }
        // 왼쪽에서 피벗보다 큰 값을 찾음
        while (low <= high && list[low] <= pivot)
        {
            low++;
            comparisonCount++;
        }
        // low와 high가 교차하면 반복 종료
        if (low > high)
            break;

        // low와 high 위치의 값을 교환
        int temp = list[low];
        list[low] = list[high];
        list[high] = temp;
    }
    // 피벗과 high 위치의 값을 교환
    list[left] = list[high];
    list[high] = pivot;

    return high;
}

// 퀵 정렬 함수
void QuickSort(int list[], int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right); // 분할점 계산
        QuickSort(list, left, q - 1);        // 왼쪽 부분 정렬
        QuickSort(list, q + 1, right);       // 오른쪽 부분 정렬
    }
}

// 이진 탐색 함수
int binarySearch(int arr[], int size, int target)
{
    int left = 0, right = size - 1;
    comparisonCount = 0; // 비교 횟수 초기화

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // 중간 인덱스 계산
        comparisonCount++;

        if (arr[mid] == target) // 중간 값이 대상 값과 일치
        {
            return mid;
        }
        else if (arr[mid] < target) // 대상 값이 더 크면 오른쪽 탐색
        {
            left = mid + 1;
        }
        else // 대상 값이 더 작으면 왼쪽 탐색
        {
            right = mid - 1;
        }
    }
    return -1; // 대상 값이 배열에 없음
}

// 보간 탐색 함수
int interpolationSearch(int arr[], int size, int target)
{
    int low = 0, high = size - 1;

    while (low <= high && target >= arr[low] && target <= arr[high])
    {
        if (low == high)
        {
            if (arr[low] == target) // 배열 크기가 1일 때 대상 값 찾기
            {
                return low;
            }
            return -1; // 값이 없을 경우
        }

        // 보간 점 계산
        int pos = low + ((double)(high - low) / (arr[high] - arr[low]) * (target - arr[low]));
        comparisonCount++;

        if (arr[pos] == target) // 보간 점이 대상 값과 일치
        {
            return pos;
        }
        if (arr[pos] < target) // 보간 점이 대상 값보다 작음
        {
            low = pos + 1;
        }
        else // 보간 점이 대상 값보다 큼
        {
            high = pos - 1;
        }
    }
    return -1; // 대상 값이 배열에 없음
}

// 배열을 출력하는 함수
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

// 이진 탐색의 평균 비교 횟수를 계산하는 함수
double getAverageBinarySearchCompareCount(int array[]) 
{
    int totalCompare = 0;

    for (int i = 0; i < 1000; i++) 
    {
        int target = array[rand() % SIZE]; // 배열에서 무작위 값 선택
        int left = 0;
        int right = SIZE - 1;
        int compare = 0;

        while (left <= right) 
        {
            compare++;
            int mid = left + (right - left) / 2;

            if (array[mid] == target) 
            { // 대상 값을 찾음
                break;
            }
            else if (array[mid] < target) 
            { // 오른쪽 탐색
                left = mid + 1;
            }
            else { // 왼쪽 탐색
                right = mid - 1;
            }
        }
        totalCompare += compare; // 비교 횟수 누적
    }
    return totalCompare / 1000.0; // 평균 반환
}

// 보간 탐색의 평균 비교 횟수를 계산하는 함수
double getAverageInterpolationSearchComparecount(int array[]) 
{
    int totalCompare = 0;

    for (int i = 0; i < 1000; i++) 
    {
        int target = array[rand() % SIZE]; // 배열에서 무작위 값 선택
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

        totalCompare += compare; // 비교 횟수 누적
    }
    return totalCompare / 1000.0; // 평균 반환
}


int main(int argc, char* argv[])
{
    srand(time(NULL)); // 랜덤 시드 설정
    int array[SIZE];
    generateRandomArray(array); // 배열 생성

    QuickSort(array, 0, SIZE - 1); // 배열 퀵 정렬
    printArray(array); // 정렬된 배열 출력

    // 이진 탐색 평균 비교 횟수 출력
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));

    // 보간 탐색 평균 비교 횟수 출력
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));

    return 0;
}
