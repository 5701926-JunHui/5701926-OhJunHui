#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000  // 배열의 크기를 1000으로 정의

int compareCount = 0;  // 전역 변수로 퀵 정렬의 비교 횟수를 저장

// 랜덤 배열 생성 함수
void generateRandomArray(int* array)
{
    // 배열의 각 요소를 0~999 사이의 랜덤 숫자로 초기화
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;
    }
}

// 순차 탐색 함수
int linearSearch(int* array, int size, int target)
{
    int compare = 0;  // 비교 횟수 초기화

    // 배열을 처음부터 끝까지 탐색
    for (int i = 0; i < size; i++)
    {
        compare++;  // 비교 횟수 증가

        // 찾으면 반복문 종료
        if (array[i] == target)
        {
            break;
        }
    }
    return compare;  // 탐색 과정에서의 비교 횟수 반환
}

// 순차 탐색 평균 비교 횟수 계산
float getAverageLinearSearchCompareCount(int* array)
{
    int totalCompare = 0;  // 총 비교 횟수 초기화

    // 랜덤한 숫자에 대해 100번 순차 탐색 수행
    for (int i = 0; i < 100; i++)
    {
        int target = array[rand() % SIZE];  // 배열의 임의의 값을 탐색 대상으로 설정
        totalCompare += linearSearch(array, SIZE, target);  // 순차 탐색의 비교 횟수 누적
    }
    return totalCompare / 100.0;  // 평균 비교 횟수 반환
}

// 퀵 정렬 함수
void quickSort(int* array, int left, int right)
{
    if (left >= right) return;

    int pivot = array[right];  // 피벗을 배열의 마지막 값으로 선택
    int i = left - 1;  // 작은 값이 저장될 위치를 나타내는 변수

    // 피벗보다 작은 값을 왼쪽으로 정렬
    for (int j = left; j < right; j++)
    {
        compareCount++;  // 비교 횟수 증가

        if (array[j] < pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // 피벗을 중앙 위치로 이동
    int temp = array[i + 1];
    array[i + 1] = array[right];
    array[right] = temp;

    // 좌우 부분 배열 정렬
    quickSort(array, left, i);
    quickSort(array, i + 2, right);
}

// 퀵 정렬 비교 횟수 계산
void getQuickSortCompareCount(int* array)
{
    compareCount = 0;  // 비교 횟수 초기화
    quickSort(array, 0, SIZE - 1);  // 배열 전체를 정렬
}

// 이진 탐색 함수
int binarySearch(int* array, int size, int target)
{
    int left = 0, right = size - 1;  // 탐색 범위 초기화
    int compare = 0;  // 비교 횟수 초기화

    while (left <= right)
    {
        compare++;  // 비교 횟수 증가
        int mid = left + (right - left) / 2;  // 중간 인덱스 계산

        if (array[mid] == target)
        {
            break;  // 값을 찾으면 종료
        }

        else if (array[mid] < target)
        {
            left = mid + 1;  // 오른쪽 부분 배열 탐색
        }

        else
        {
            right = mid - 1;  // 왼쪽 부분 배열 탐색
        }
    }
    return compare;  // 탐색 과정에서의 비교 횟수 반환
}

// 이진 탐색 평균 비교 횟수 계산
float getAverageBinarySearchCompareCount(int* array)
{
    int totalCompare = 0;  // 총 비교 횟수 초기화

    // 랜덤한 숫자에 대해 100번 이진 탐색 수행
    for (int i = 0; i < 100; i++)
    {
        int target = array[rand() % SIZE];  // 배열의 임의의 값을 탐색 대상으로 설정
        totalCompare += binarySearch(array, SIZE, target);  // 이진 탐색의 비교 횟수 누적
    }
    return totalCompare / 100.0;  // 평균 비교 횟수 반환
}

// 배열 출력 함수
void printArray(int* array)
{
    printf("Array Sorting Result:\n");

    // 배열의 처음 20개 요소 출력
    for (int i = 0; i < 20; i++)
    {
        printf("%3d ", array[i]);
    }
    printf("\n");

    // 배열의 마지막 20개 요소 출력
    for (int i = SIZE - 20; i < SIZE; i++)
    {
        printf("%3d ", array[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    srand(time(NULL));  // 랜덤 시드 초기화
    int array[SIZE];  // 크기가 1000인 배열 생성

    generateRandomArray(array);  // 랜덤 값으로 배열 초기화

    // 순차 탐색 평균 비교 횟수 출력
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // 퀵 정렬 및 비교 횟수 출력
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // 이진 탐색 평균 비교 횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    // 정렬된 배열의 처음 20개와 마지막 20개 요소 출력
    printArray(array);

    return 0;
}
