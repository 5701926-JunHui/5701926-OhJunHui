#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100 // 배열의 크기 정의

// 랜덤 숫자를 생성하여 배열에 저장하는 함수
void generateRandomNumbers(int array[])
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = rand() % 1000; // 0-999 사이의 랜덤 숫자 생성
    }
}

// 셸 정렬을 수행하는 함수
void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount)
{
    int n = ARRAY_SIZE; // 배열의 크기
    int gap, i, j, temp;

    // gap 계산 (gapType에 따라 다르게 설정)
    if (gapType == 2)
    {
        gap = n / 2; // gap을 n/2로 설정
    }
    else
    {
        gap = n / 3; // gap을 n/3로 설정
    }

    // gap이 0보다 큰 동안 계속 정렬 수행
    while (gap > 0)
    {
        printf("Sorting with gap = %d: ", gap);
        printf("\n");

        for (i = gap; i < n; i++)
        {
            temp = array[i]; // 현재 요소 저장
            j = i;

            // 이동 및 비교 카운트
            (*moveCount)++;

            // 요소를 적절한 위치로 이동
            while (j >= gap && array[j - gap] > temp)
            {
                array[j] = array[j - gap]; // 요소 이동
                j -= gap; // 인덱스 업데이트
                (*comparisonCount)++; // 비교 카운트 증가
                (*moveCount)++; // 이동 카운트 증가
            }
            array[j] = temp; // 적절한 위치에 요소 삽입
            (*moveCount)++;
        }

        // 현재 배열 상태 출력
        for (int k = 0; k < n; k++)
        {
            printf("%d ", array[k]);
        }
        printf("\n\n");

        gap /= (gapType == 2 ? 2 : 3); // gap 줄이기
    }

    // 정렬 완료 후 최종 배열 출력
    printf("Sorted shellArray (gap = %d):\n", gapType);
    for (int k = 0; k < n; k++)
    {
        printf("%d ", array[k]);
    }
    printf("\n\n");
}

// 삽입 정렬을 수행하는 함수
void doInsertionSort(int array[], int* comparisonCount, int* moveCount)
{
    for (int i = 1; i < ARRAY_SIZE; i++)
    {
        int key = array[i]; // 현재 키 저장
        int j = i - 1;

        // 이동 및 비교 카운트
        (*moveCount)++;

        // 키를 적절한 위치로 이동
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j]; // 요소 이동
            j--; // 인덱스 업데이트
            (*comparisonCount)++; // 비교 카운트 증가
            (*moveCount)++; // 이동 카운트 증가
        }
        array[j + 1] = key; // 적절한 위치에 키 삽입
        (*moveCount)++;
    }

    // 정렬된 배열 출력
    printf("Sorted insertionArray:\n");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

int main(void)
{
    int array[ARRAY_SIZE]; // 정렬할 배열
    int comparisonCount = 0; // 비교 횟수 초기화
    int moveCount = 0; // 이동 횟수 초기화

    srand(time(NULL)); // 랜덤 시드 초기화
    generateRandomNumbers(array); // 랜덤 숫자 생성

    // 셸 정렬 (n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    srand(time(NULL)); // 랜덤 시드 초기화
    generateRandomNumbers(array); // 랜덤 숫자 생성

    // 셸 정렬 (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    srand(time(NULL));
    generateRandomNumbers(array);

    // 삽입 정렬
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
