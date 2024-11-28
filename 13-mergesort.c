#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0; // 비교 횟수
int moveCount = 0; // 이동 횟수
int totalComparisons = 0; // 총 비교 횟수
int totalMoves = 0; // 총 이동 횟수
int isFirst = 0; // 첫 번째 실행 여부
int rounds = 0; // 병합 횟수 추적

// 랜덤 배열 생성 함수
void generateRandomArray(int array[]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        array[i] = rand() % 1000; // 0-999 사이의 랜덤 숫자 생성
    }
}

// 배열 출력 함수
void printArray(int array[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        printf("%3d ", array[i]); // 배열의 각 요소를 출력
    }
    printf("\n");
}

// 배열 병합 함수
void merge(int array[], int left, int mid, int right) 
{
    int i, j, k;
    int n1 = mid - left + 1; // 왼쪽 배열의 크기
    int n2 = right - mid; // 오른쪽 배열의 크기

    // 왼쪽과 오른쪽 배열을 동적 할당
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // 왼쪽과 오른쪽 배열에 값 복사
    for (i = 0; i < n1; i++)
        L[i] = array[left + i];

    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    i = 0; j = 0; k = left; // 인덱스 초기화

    // 병합 과정
    while (i < n1 && j < n2) 
    {
        comparisonCount++; // 비교 횟수 증가

        if (L[i] <= R[j]) 
        {
            array[k] = L[i]; // 왼쪽 배열의 값 선택
            i++;
        }
        else 
        {
            array[k] = R[j]; // 오른쪽 배열의 값 선택
            j++;
        }
        moveCount++; // 이동 횟수 증가
        k++;
    }

    // 남은 왼쪽 배열 요소 복사
    while (i < n1) 
    {
        array[k] = L[i];
        i++;
        k++;
        moveCount++;
    }

    // 남은 오른쪽 배열 요소 복사
    while (j < n2) 
    {
        array[k] = R[j];
        j++;
        k++;
        moveCount++;
    }

    free(L); // 동적 할당 해제
    free(R); // 동적 할당 해제

    // 병합이 완료된 후 rounds 증가
    rounds++;

    // rounds가 10의 배수일 때 배열 상태 출력
    if (rounds % 10 == 0 && isFirst == 0) 
    {
        for (int i = 0; i < 10; i++)
            printf("%3d ", array[i]); // 배열의 처음 10개 요소 출력

        printf("| "); // 구분선 출력

        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)
            printf("%3d ", array[i]); // 중앙 위치부터 10개 요소 출력
        printf("\n\n");
    }
}

// 합병 정렬 함수 (반복적 방법)
void doMergeSort(int array[], int left, int right) 
{
    for (int currentSize = 1; currentSize <= right - left; currentSize *= 2) 
    {
        for (int leftStart = left; leftStart < right; leftStart += 2 * currentSize) 
        {
            int mid = leftStart + currentSize - 1; // 중간 인덱스
            int rightEnd = leftStart + 2 * currentSize - 1; // 오른쪽 끝 인덱스

            if (mid >= right) // 중간 인덱스가 범위를 넘으면 종료
                break;

            if (rightEnd > right) // 오른쪽 끝 인덱스 조정
                rightEnd = right;

            merge(array, leftStart, mid, rightEnd); // 병합 호출
        }
    }
}

int main(void) 
{
    int array[SIZE];

    srand(time(NULL)); // 랜덤 시드 초기화

    for (int i = 0; i < 20; i++) 
    {
        generateRandomArray(array); // 랜덤 배열 생성
        comparisonCount = 0; // 비교 횟수 초기화
        moveCount = 0; // 이동 횟수 초기화

        if (i == 0) 
        {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1); // 합병 정렬 수행

            printf("Result\n");
            printArray(array, SIZE); // 정렬된 배열 출력
            isFirst++; // 첫 번째 실행 플래그 설정
        }
        else 
        {
            doMergeSort(array, 0, SIZE - 1); // 이후 테스트에 대해 정렬 수행
        }
        totalComparisons += comparisonCount; // 총 비교 횟수 누적
        totalMoves += moveCount; // 총 이동 횟수 누적
    }
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0); // 평균 비교 횟수 출력
    printf("Average Moves: %.2f\n", totalMoves / 20.0); // 평균 이동 횟수 출력

    return 0;
}
