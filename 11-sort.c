#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 // 배열의 크기 정의
#define TRIALS 20 // 정렬 시도 횟수 정의


// 랜덤 데이터 생성 함수
void generateRandomData(int arr[]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        arr[i] = rand() % 1000; // 0부터 999 사이의 랜덤 숫자 생성
    }
}

// 배열 출력 함수
void printArray(int arr[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        printf("%d ", arr[i]); // 배열의 각 요소 출력
    }
    printf("\n");
}

// 선택 정렬
void doSelectionSort(int arr[]) 
{
    int tempArr[SIZE]; // 정렬을 위한 임시 배열

    for (int i = 0; i < SIZE; i++) 
    {
        tempArr[i] = arr[i]; // 원본 배열을 임시 배열로 복사
    }

    printf("Selection Sort:\n\n");

    int step = 0; // 단계 카운터

    for (int i = 0; i < SIZE - 1; i++) 
    {
        int minIdx = i; // 최소값의 인덱스 초기화

        for (int j = i + 1; j < SIZE; j++) 
        {
            if (tempArr[j] < tempArr[minIdx]) 
            {
                minIdx = j; // 최소값의 인덱스 업데이트
            }
        }

        // Swap
        int temp = tempArr[minIdx];
        tempArr[minIdx] = tempArr[i];
        tempArr[i] = temp;

        // 특정 단계에서 출력
        step++;
        if (step == 10 || step % 20 == 10 || step == SIZE - 1) 
        {
            printf("Step %d: ", step);
            printArray(tempArr, SIZE); // 현재 배열 상태 출력
            printf("\n");
        }
    }
    printf("\n");
}

// 삽입 정렬
void doInsertionSort(int arr[])
{
    int arrCopy[SIZE]; // 정렬을 위한 복사 배열

    for (int i = 0; i < SIZE; i++)
    {
        arrCopy[i] = arr[i]; // 원본 배열을 복사
    }

    int compareSum = 0; // 비교 횟수를 저장할 변수
    int compareCount = 0; // 각 시도에서의 비교 횟수

    for (int t = 0; t < TRIALS; t++)
    {
        int arrTrial[SIZE]; // 정렬을 위한 복사 배열
        for (int i = 0; i < SIZE; i++)
        {
            arrTrial[i] = arrCopy[i]; // 원본 배열 복사
        }

        compareCount = 0; // 각 시도에서의 비교 횟수 초기화

        for (int i = 1; i < SIZE; i++)
        {
            int key = arrTrial[i]; // 현재 삽입할 요소
            int j = i - 1;

            while (j >= 0 && arrTrial[j] > key)
            {
                arrTrial[j + 1] = arrTrial[j]; // 요소를 한 칸씩 이동
                j--;
                compareCount++; // 비교 횟수 증가
            }
            arrTrial[j + 1] = key; // 요소 삽입
            compareCount++; // 마지막 비교 횟수 증가
        }
        compareSum += compareCount; // 총 비교 횟수에 추가

        if (t == 0) 
        {
            printf("\nInsertion Sort Compare Average: %d\n", compareSum / TRIALS); // 평균 비교 횟수 출력
            printf("Insertion Sort Result:\n"); // 정렬 결과 출력
            printArray(arrTrial, SIZE);
        }
    }
}

// 버블 정렬
void doBubbleSort(int arr[])
{
    int arrCopy[SIZE]; // 정렬을 위한 복사 배열

    for (int i = 0; i < SIZE; i++)
    {
        arrCopy[i] = arr[i]; // 원본 배열을 복사
    }

    int moveSum = 0; // 이동 횟수를 저장할 변수
    int moveCount = 0; // 각 시도에서의 이동 횟수

    for (int t = 0; t < TRIALS; t++)
    {
        int arrTrial[SIZE]; // 정렬을 위한 복사 배열
        for (int i = 0; i < SIZE; i++)
        {
            arrTrial[i] = arrCopy[i]; // 원본 배열 복사
        }

        moveCount = 0; // 각 시도에서의 이동 횟수 초기화

        for (int i = 0; i < SIZE - 1; i++)
        {
            for (int j = 0; j < SIZE - i - 1; j++)
            {
                if (arrTrial[j] > arrTrial[j + 1])
                {
                    int temp = arrTrial[j];
                    arrTrial[j] = arrTrial[j + 1];
                    arrTrial[j + 1] = temp;
                    moveCount++; // 이동 횟수 증가
                }
            }
        }
        moveSum += moveCount; // 총 이동 횟수에 추가

        if (t == 0) {
            printf("\nBubble Sort Move Average: %d\n", moveSum / TRIALS); // 평균 이동 횟수 출력
            printf("Bubble Sort Result:\n");    // 정렬 결과 출력
            printArray(arrTrial, SIZE);
        }
    }
}


int main(void)
{
    int randomData[SIZE]; // 랜덤 데이터를 저장할 배열

    // 랜덤 데이터 생성
    srand(time(0));
    generateRandomData(randomData); // 랜덤 데이터 생성 함수 호출

    // 정렬 수행
    doSelectionSort(randomData); // 선택 정렬 수행
    doInsertionSort(randomData); // 삽입 정렬 수행
    doBubbleSort(randomData); // 버블 정렬 수행

    return 0;
}
