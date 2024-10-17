#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int* b)   // 두 요소를 교환하는 함수
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void resortHeap(int inputData[], int n, int i)  // 힙을 재정렬하는 함수
{
    int largest = i; // 루트를 가장 큰 값으로 가정
    int left = 2 * i + 1; // 왼쪽 자식
    int right = 2 * i + 2; // 오른쪽 자식

    // 왼쪽 자식이 더 크다면
    if (left < n && inputData[left] > inputData[largest])
        largest = left; // 가장 큰 노드가 왼쪽 노드로

    // 오른쪽 자식이 더 크다면
    if (right < n && inputData[right] > inputData[largest])
        largest = right;    // 가장 큰 노드가 오른쪽 노드로

    if (largest != i)   // 루트가 가장 큰 값이 아니라면
    {
        swap(&inputData[i], &inputData[largest]);
        // 바뀐 자식 노드를 재정렬
        resortHeap(inputData, n, largest);
    }
}


void BuildMaxHeap(int inputData[], int n)   // 최대 힙을 구성하는 함수
{
    for (int i = 1; i <= n; i++)    // 요소를 하나씩 힙에 삽입하는 과정을 출력
    {
        for (int j = i / 2 - 1; j >= 0; j--)    // 부분 배열로 힙을 만들기 시작
        {
            resortHeap(inputData, i, j);
        }

        for (int k = 0; k < i; k++) // 현재까지 힙에 추가된 상태 출력
        {
            printf("%d ", inputData[k]);
        }
        printf("\n");
    }
}


void BuildMaxHeapAndSort(int inputData[], int n)    // 힙 정렬 실행 함수
{
    BuildMaxHeap(inputData, n);  // 최대 힙 생성

    for (int i = n - 1; i > 0; i--) // 하나씩 힙에서 루트(최대값)를 제거하고 정렬
    {
        swap(&inputData[0], &inputData[i]); // 최대값인 루트(0번째 요소)를 끝으로 보냄

        resortHeap(inputData, i, 0);    // 힙 재정렬 후 상태 출력

        for (int j = 0; j < i; j++) 
        {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}


int main(void) 
{
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    printf("<Sort>\n"); // 힙 정렬 실행
    BuildMaxHeapAndSort(inputData, size);

    printf("\nSorted Array:\n");    // 정렬된 결과 출력
    
    for (int i = 0; i < size; i++) 
    {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}





