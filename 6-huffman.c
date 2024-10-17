#include <stdio.h>
#include <stdlib.h>

// Huffman 트리의 노드 구조체 정의
typedef struct Node 
{
    char character;
    int frequency;
    struct Node* left, * right;
} Huffman;

// 우선순위 큐(최소 힙) 구조체 정의
typedef struct MinHeap 
{
    int size;
    int capacity;
    Huffman** array;
} MinHeap;

// 노드 생성 함수
Huffman* createNode(char character, int frequency) 
{
    Huffman* newNode = (Huffman*)malloc(sizeof(Huffman));

    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;

    return newNode;
}

// 최소 힙 생성 함수
MinHeap* createMinHeap(int capacity) 
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Huffman**)malloc(minHeap->capacity * sizeof(Huffman*));

    return minHeap;
}

// 두 노드를 교환하는 함수
void swapNodes(Huffman** a, Huffman** b) 
{
    Huffman* t = *a;
    *a = *b;
    *b = t;
}

// 최소 힙(Heapify) 함수
void minHeapify(MinHeap* minHeap, int idx) 
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) 
    {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 최소 힙에서 최솟값을 추출하는 함수
Huffman* extractMin(MinHeap* minHeap) 
{
    Huffman* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;

    minHeapify(minHeap, 0);

    return temp;
}

// 최소 힙 삽입 함수
void insertMinHeap(MinHeap* minHeap, Huffman* node) 
{
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency) 
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// 힙 상태 출력 함수 (숫자만 출력)
void printHeap(MinHeap* minHeap) 
{
    for (int i = 0; i < minHeap->size; ++i) 
    {
        printf("%d ", minHeap->array[i]->frequency);
    }
    printf("\n");
}

// 주어진 빈도를 기반으로 최소 힙을 생성하는 함수
MinHeap* buildMinHeap(char characters[], int frequencies[], int size) 
{
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i) 
    {
        insertMinHeap(minHeap, createNode(characters[i], frequencies[i]));
        printHeap(minHeap); // 삽입 후 힙 출력 (숫자만)
    }
    return minHeap;
}

// 허프만 트리 생성 함수
Huffman* BuildHuffmanTree(char characters[], int frequencies[], int size) 
{
    Huffman* left, * right, * top;

    MinHeap* minHeap = buildMinHeap(characters, frequencies, size);

    while (minHeap->size != 1) 
    {
        // 두 개의 최소 빈도 노드 추출
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // 두 노드를 결합하여 새로운 노드를 생성
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        // 결합 과정을 숫자만 출력
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, top->frequency);

        // 새로 만든 노드를 힙에 삽입
        insertMinHeap(minHeap, top);

        // 현재 힙 상태 출력 (숫자만)
        printHeap(minHeap);
    }
    return extractMin(minHeap);
}

// 허프만 코드 출력 함수
void printCodes(Huffman* root, int arr[], int top) 
{
    if (root->left) 
    {
        arr[top] = 1; // 왼쪽 자식은 1
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) 
    {
        arr[top] = 0; // 오른쪽 자식은 0
        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right)) 
    {
        printf("%c: ", root->character);

        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// GenerateHuffmanCodes 함수 정의
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) 
{
    Huffman* root = BuildHuffmanTree(characters, frequencies, size);

    int arr[100], top = 0;

    printCodes(root, arr, top);
}


int main(void) 
{
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    GenerateHuffmanCodes(characters, frequencies, size);

    return 0;
}


