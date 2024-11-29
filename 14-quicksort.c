#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100  // 배열의 크기를 100으로 정의
#define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )  // 두 변수를 교환하는 매크로

// 전역 변수 선언
int comparisonCount = 0;  // 비교 횟수 카운터
int moveCount = 0;       // 이동 횟수 카운터
int isFirst = 0;         // 첫 번째 실행 여부
int totalComparisons = 0; // 총 비교 횟수
int totalMoveCount = 0;  // 총 이동 횟수
int rounds = 0;          // 정렬 과정 출력 카운트

// 배열에 랜덤 값을 생성하는 함수
void generateRandomArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;  // 0부터 999 사이의 랜덤 값 생성
    }
}

// 배열을 구별하는 함수 (피벗을 기준으로 나누기)
int partition(int list[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;  // low는 left로 초기화
    high = right + 1;  // high는 right + 1로 초기화
    pivot = list[left];  // 피벗 값을 첫 번째 요소로 설정

    do
    {
        do
        {
            low++;
            comparisonCount++;  // 비교 횟수 증가
        } while (low <= right && list[low] < pivot);  // 피벗보다 큰 값을 찾을 때까지 증가

        do
        {
            high--;
            comparisonCount++;  // 비교 횟수 증가
        } while (high >= left && list[high] > pivot);  // 피벗보다 작은 값을 찾을 때까지 감소

        if (low < high)
        {
            SWAP(list[low], list[high], temp);  // 저항이 발견되면 두 값을 교환
            moveCount += 3;  // 이동 횟수 증가 (3번의 이동)
        }
    } while (low < high);  // low가 high보다 작으면 계속 진행

    SWAP(list[left], list[high], temp);  // 피벗 값을 올바른 위치로 교환
    moveCount += 3;  // 이동 횟수 증가

    return high;  // 피벗의 최종 인덱스를 반환
}

// 퀵 정렬을 수행하는 함수 (반복적 방법)
void doQuickSort(int list[], int left, int right)
{
    // 스택을 사용하기 위해 최대 크기를 SIZE로 설정
    int stack[SIZE];
    int top = -1;  // 스택의 top을 -1로 초기화

    // 첫 번째 범위를 스택에 푸시
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0)  // 스택이 비어있지 않으면 반복
    {
        // 스택에서 오른쪽과 왼쪽 인덱스를 팝
        right = stack[top--];
        left = stack[top--];

        if (left < right)  // 왼쪽 인덱스가 오른쪽 인덱스보다 작으면
        {
            int q = partition(list, left, right);  // 파티션 함수를 호출하여 피벗 위치 찾기

            // 10회마다 40에서 60 위치의 값을 출력
            if (rounds % 10 == 0 && isFirst == 0)
            {
                for (int i = 40; i < 60; i++)
                    printf("%d ", list[i]);  // 해당 범위의 값 출력
                printf("\n\n");
            }
            rounds++;  // 정렬 과정 카운트 증가

            // 왼쪽 부분과 오른쪽 부분의 범위를 스택에 푸시
            stack[++top] = left;      // 왼쪽 부분 범위
            stack[++top] = q - 1;    // 피벗 왼쪽 부분 범위
            stack[++top] = q + 1;    // 피벗 오른쪽 부분 범위
            stack[++top] = right;     // 오른쪽 부분 범위
        }
    }
}

// 배열의 요소를 출력하는 함수
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);  // 각 요소 출력
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    srand(time(NULL));  // 랜덤 시드 초기화
    int array[SIZE];  // 배열 선언

    for (int i = 0; i < 20; i++)  // 20회 실행
    {
        generateRandomArray(array);  // 랜덤 배열 생성
        comparisonCount = 0;  // 비교 횟수 초기화
        moveCount = 0;       // 이동 횟수 초기화
        rounds = 0;          // 정렬 과정 카운트 초기화

        if (i == 0)  // 첫 번째 실행일 경우
        {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);  // 퀵 정렬 실행

            printf("Result\n");
            printArray(array, SIZE);  // 정렬된 배열 출력
            isFirst++;  // 첫 번째 실행 표시
        }
        else
        {
            doQuickSort(array, 0, SIZE - 1);  // 이후 실행에서도 퀵 정렬 실행
        }
        totalComparisons += comparisonCount;  // 총 비교 횟수 업데이트
        totalMoveCount += moveCount;          // 총 이동 횟수 업데이트
    }
    // 평균 비교 횟수와 평균 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;  // 프로그램 종료
}
