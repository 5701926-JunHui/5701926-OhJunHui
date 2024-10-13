#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100


typedef struct  // 히프 구조체 정의 
{
    int heap[MAX_SIZE];
    int heap_size;
} TreeNode;


int parent(int i)   // 부모 인덱스 계산
{
    return (i - 1) / 2; // i/2가 아니라, (i - 1) / 2인 이유는 배열의 인덱스가 1이 아니라 0부터 시작하기 때문
}


int leftChild(int i)    // 왼쪽 자식 인덱스 계산
{
    return 2 * i + 1;
}


int rightChild(int i)   // 오른쪽 자식 인덱스 계산
{
    return 2 * i + 2;
}


void PrintHeapMove(TreeNode* h) // 히프의 상태를 출력하는 함수
{
    for (int i = 0; i < h->heap_size; i++) 
    {
        printf("%d ", h->heap[i]);
    }
    printf("\n");
}


int HeapTreeDown(TreeNode* h, int i)    // 삭제 시 노드 이동을 할 때 히프의 성질을 유지하는 함수
{
    int largest = i;

    int left = leftChild(i);
    int right = rightChild(i);

    int moves = 0; // 이동 된 횟수: 0으로 초기화

    // 왼쪽 자식이 현재 노드보다 크다면 
    if (left < h->heap_size && h->heap[left] > h->heap[largest])
        largest = left; // 가장 큰 값을 가진 노드로 업데이트

    // 오른쪽 자식이 현재까지 가장 큰 노드보다 크다면
    if (right < h->heap_size && h->heap[right] > h->heap[largest])
        largest = right;    // 가장 큰 값을 가진 노드로 업데이트

    // 가장 큰 값이 현재 노드가 아니라면 교체
    if (largest != i) 
    {
        // 노드 교체
        int temp = h->heap[i];

        h->heap[i] = h->heap[largest];
        h->heap[largest] = temp;

        moves++; // 이동

        PrintHeapMove(h);   // 교체된 후 히프 상태를 출력

        moves += HeapTreeDown(h, largest);  // 자식 노드로 계속 아래로 이동 -> 호출
    }

    return moves;
}

// 히프에 새로운 값을 넣는 함수
void InsertMaxHeapTree(TreeNode* h, int value, int print, int userInput) 
{
    if (h->heap_size == MAX_SIZE) 
    {
        return;
    }

    // 새로운 값을 추가
    h->heap[h->heap_size] = value;
    int i = h->heap_size;
    h->heap_size++;

    // 삽입할 때 히프 상태 출력
    if (print) 
    {
        PrintHeapMove(h);
    }

    int moves = 0; // 이동된 횟수: 0으로 초기화

    while (i != 0 && h->heap[parent(i)] < h->heap[i]) 
    {
        // 노드 교체
        int temp = h->heap[i];

        h->heap[i] = h->heap[parent(i)];
        h->heap[parent(i)] = temp;

        i = parent(i);

        moves++; // 교체가 일어날 때마다 이동 횟수 증가

        if (print)  // 교체 후 히프 상태를 출력
        {
            PrintHeapMove(h);
        }
    }

    if (userInput)  // 사용자가 요소를 입력한 경우에만 이동 횟수 출력
    {
        printf("노드가 이동된 횟수: %d\n", moves);
    }
}


void DeleteMaxHeapTree(TreeNode* h) // 히프에서 루트(최대값)를 삭제하는 함수
{
    if (h->heap_size == 0) 
    {
        return;
    }

    // 마지막 요소를 루트로 이동
    h->heap[0] = h->heap[h->heap_size - 1];
    h->heap_size--;

    PrintHeapMove(h);

    int moves = HeapTreeDown(h, 0);

    printf("노드가 이동된 횟수: %d\n", moves);
}


void PrintHeapTree(TreeNode* h) // 히프를 레벨별로 출력하는 함수

{
    if (h->heap_size == 0) 
    {
        return;
    }

    int level = 0;
    int nodes_in_level = 1;     // 해당 레벨에서 출력할 노드의 수
    int index = 0;  // 현재 노드의 인덱스: 0으로 초기화

    while (index < h->heap_size) 
    {
        printf("[%d] : ", level + 1);

        for (int i = 0; i < nodes_in_level && index < h->heap_size; i++) 
        {
            printf("%d ", h->heap[index]);
            index++;
        }

        printf("\n");

        level++;
        nodes_in_level *= 2;    // 레벨이 증가할 때마다 출력할 노드의 수가 2배 늘어남
    }
}

// 최대 히프 생성 함수
TreeNode* generateMaxHeapTree(int inputData[], int size) 
{
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));   // 메모리 동적 할당

    if (root == NULL)
    {
        exit(1);
    }
    root->heap_size = 0;    // 초기에는 히프의 크기: 0으로 초기화


    for (int i = 0; i < size; i++) 
    {
        InsertMaxHeapTree(root, inputData[i], 0, 0);
    }
    return root;
}


void runUserInterface(TreeNode* root)   // 메뉴 창 출력 및 프로그램 실행 함수
{
    char choice;
    int value;

    printf("-------------------\n");
    printf("| i: 노드 추가    |\n");
    printf("| d: 노드 삭제    |\n");
    printf("| p: 레벨별 출력  |\n");
    printf("| c: 종료         |\n");
    printf("-------------------\n\n");

    while (1) 
    {
        printf("\n\n메뉴 입력: ");
        scanf_s(" %c", &choice);

        switch (choice) 
        {
        case 'i':
            printf("추가할 값 입력: ");
            scanf_s("%d", &value);
            InsertMaxHeapTree(root, value, 1, 1);
            break;

        case 'd':
            DeleteMaxHeapTree(root);
            break;

        case 'p':
            printf("트리 레벨별 출력\n");
            PrintHeapTree(root);
            break;

        case 'c':
            return;

        default:
            printf("잘못된 선택입니다.\n");
        }
    }
}


int main(void)
{
    int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = generateMaxHeapTree(inputData, size);  // 히프 생성

    runUserInterface(root); // 사용자가 요소를 입력하는 함수 실행
    
    free(root); // 메모리 반납
    return 0;
}





