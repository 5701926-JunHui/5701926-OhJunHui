#include <stdio.h>
#include <stdlib.h>


typedef struct Node // Huffman 트리의 노드 구조체 정의
{
    char character;    // 문자
    int frequency;     // 해당 문자의 빈도
    struct Node* left, * right;    // 왼쪽, 오른쪽 자식 노드 포인터
} Huffman;


typedef struct MinHeap  // 최소 힙 구조체 정의
{
    int size;        // 현재 힙에 있는 노드의 수
    int capacity;    // 힙의 최대 용량
    Huffman** array; // 노드 포인터 배열 (힙을 저장)
} MinHeap;


Huffman* createNode(char character, int frequency)  // 새로운 노드 생성 함수
{
    Huffman* newNode = (Huffman*)malloc(sizeof(Huffman));  // 새로운 노드 메모리 할당

    newNode->character = character;  // 문자 설정
    newNode->frequency = frequency;  // 빈도 설정
    newNode->left = newNode->right = NULL;  // 자식 노드는 NULL로 초기화

    return newNode;  // 생성된 노드 반환
}


MinHeap* createMinHeap(int capacity)    // 최소 힙 생성 함수
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));  // 최소 힙 메모리 할당

    minHeap->size = 0;   // 초기 크기는 0
    minHeap->capacity = capacity;  // 힙의 용량 설정
    minHeap->array = (Huffman**)malloc(minHeap->capacity * sizeof(Huffman*));  // 노드 배열 생성

    return minHeap;  // 생성된 최소 힙 반환
}


void swapNodes(Huffman** a, Huffman** b)    // 두 노드를 교환하는 함수
{
    Huffman* t = *a;  // 임시 변수에 첫 번째 노드를 저장
    *a = *b;          // 두 번째 노드를 첫 번째 위치로 이동
    *b = t;           // 임시 변수에 저장된 첫 번째 노드를 두 번째 위치로 이동
}


void minHeapify(MinHeap* minHeap, int idx)  // 최소 힙(Heapify) 함수
{
    int smallest = idx;          // 현재 노드를 가장 작은 노드로 가정
    int left = 2 * idx + 1;      // 왼쪽 자식의 인덱스 계산
    int right = 2 * idx + 2;     // 오른쪽 자식의 인덱스 계산

    // 왼쪽 자식이 존재하고, 현재 노드보다 빈도가 더 작다면 작은 노드 업데이트
    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    // 오른쪽 자식이 존재하고, 더 작은 빈도라면 작은 노드 업데이트
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    // 작은 노드가 현재 노드가 아니라면 바꾸고 힙 속성을 유지
    if (smallest != idx)
    {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}


Huffman* extractMin(MinHeap* minHeap)   // 최소 힙에서 최솟값을 추출하는 함수
{
    Huffman* temp = minHeap->array[0];  // 루트 노드(최솟값) 저장
    minHeap->array[0] = minHeap->array[minHeap->size - 1];  // 마지막 노드를 루트로 이동
    --minHeap->size;  // 힙 크기 감소

    minHeapify(minHeap, 0); // 루트에서 힙 속성을 다시 유지

    return temp;  // 추출된 노드 반환
}


void insertMinHeap(MinHeap* minHeap, Huffman* node) // 최소 힙 삽입 함수
{
    ++minHeap->size;  // 힙 크기 증가
    int i = minHeap->size - 1;  // 마지막 인덱스에서 시작

    // 부모 노드보다 빈도가 작은 경우 위로 이동
    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];  // 부모 노드를 아래로 이동
        i = (i - 1) / 2;  // 부모의 인덱스로 이동
    }
    minHeap->array[i] = node;  // 새로운 노드를 삽입
}


void printHeap(MinHeap* minHeap)    // 힙 상태 출력 함수
{
    for (int i = 0; i < minHeap->size; ++i)
    {
        printf("%d ", minHeap->array[i]->frequency);  // 각 노드의 빈도 출력
    }
    printf("\n");
}


MinHeap* buildMinHeap(char characters[], int frequencies[], int size)   // 주어진 빈도를 기반으로 최소 힙을 생성하는 함수
{
    MinHeap* minHeap = createMinHeap(size);  // 최소 힙 생성

    // 각 문자와 빈도를 기반으로 힙에 노드를 삽입
    for (int i = 0; i < size; ++i)
    {
        insertMinHeap(minHeap, createNode(characters[i], frequencies[i]));  // 새로운 노드 삽입
        printHeap(minHeap); // 삽입 후 힙 출력
    }
    return minHeap;  // 생성된 최소 힙 반환
}


Huffman* BuildHuffmanTree(char characters[], int frequencies[], int size)   // 허프만 트리 생성 함수
{
    Huffman* left, * right, * top;

    MinHeap* minHeap = buildMinHeap(characters, frequencies, size);  // 최소 힙 생성

    // 최소 힙에 하나의 노드만 남을 때까지 반복
    while (minHeap->size != 1)
    {
        // 두 개의 최소 빈도 노드 추출
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // 두 노드를 결합하여 새로운 노드 생성 (빈도의 합을 가진 새로운 노드)
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        // 결합 과정 출력
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, top->frequency);

        // 새로 만든 노드를 힙에 삽입
        insertMinHeap(minHeap, top);

        // 현재 힙 상태 출력
        printHeap(minHeap);
    }
    return extractMin(minHeap);  // 허프만 트리의 루트 반환
}


void printCodes(Huffman* root, int arr[], int top)  // 허프만 코드 출력 함수
{
    // 왼쪽 자식이 존재하면 1을 추가하고 재귀적으로 호출
    if (root->left)
    {
        arr[top] = 1;  // 왼쪽 자식은 1
        printCodes(root->left, arr, top + 1);
    }

    // 오른쪽 자식이 존재하면 0을 추가하고 재귀적으로 호출
    if (root->right)
    {
        arr[top] = 0;  // 오른쪽 자식은 0
        printCodes(root->right, arr, top + 1);
    }

    // 리프 노드(문자 노드)에 도달하면 해당 문자와 그 코드를 출력
    if (!(root->left) && !(root->right))
    {
        printf("%c: ", root->character);  // 문자 출력

        for (int i = 0; i < top; i++)  // 배열에 저장된 0과 1을 출력
            printf("%d", arr[i]);
        printf("\n");
    }
}


void GenerateHuffmanCodes(char characters[], int frequencies[], int size) // 허프만 코드를 생성하는 함수
{
    Huffman* root = BuildHuffmanTree(characters, frequencies, size);  // 허프만 트리 생성

    int arr[100], top = 0;  // 코드 저장을 위한 배열과 초기 인덱스

    printCodes(root, arr, top);  // 허프만 코드 출력
}

int main(void)
{
    // 예시 문자와 빈도 배열
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);  // 배열의 크기 계산

    GenerateHuffmanCodes(characters, frequencies, size);  // 허프만 코드 생성 및 출력

    return 0;
}
