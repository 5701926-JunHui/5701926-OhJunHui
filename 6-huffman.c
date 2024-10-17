#include <stdio.h>
#include <stdlib.h>

// Huffman Ʈ���� ��� ����ü ����
typedef struct Node 
{
    char character;
    int frequency;
    struct Node* left, * right;
} Huffman;

// �켱���� ť(�ּ� ��) ����ü ����
typedef struct MinHeap 
{
    int size;
    int capacity;
    Huffman** array;
} MinHeap;

// ��� ���� �Լ�
Huffman* createNode(char character, int frequency) 
{
    Huffman* newNode = (Huffman*)malloc(sizeof(Huffman));

    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;

    return newNode;
}

// �ּ� �� ���� �Լ�
MinHeap* createMinHeap(int capacity) 
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Huffman**)malloc(minHeap->capacity * sizeof(Huffman*));

    return minHeap;
}

// �� ��带 ��ȯ�ϴ� �Լ�
void swapNodes(Huffman** a, Huffman** b) 
{
    Huffman* t = *a;
    *a = *b;
    *b = t;
}

// �ּ� ��(Heapify) �Լ�
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

// �ּ� ������ �ּڰ��� �����ϴ� �Լ�
Huffman* extractMin(MinHeap* minHeap) 
{
    Huffman* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;

    minHeapify(minHeap, 0);

    return temp;
}

// �ּ� �� ���� �Լ�
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

// �� ���� ��� �Լ� (���ڸ� ���)
void printHeap(MinHeap* minHeap) 
{
    for (int i = 0; i < minHeap->size; ++i) 
    {
        printf("%d ", minHeap->array[i]->frequency);
    }
    printf("\n");
}

// �־��� �󵵸� ������� �ּ� ���� �����ϴ� �Լ�
MinHeap* buildMinHeap(char characters[], int frequencies[], int size) 
{
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i) 
    {
        insertMinHeap(minHeap, createNode(characters[i], frequencies[i]));
        printHeap(minHeap); // ���� �� �� ��� (���ڸ�)
    }
    return minHeap;
}

// ������ Ʈ�� ���� �Լ�
Huffman* BuildHuffmanTree(char characters[], int frequencies[], int size) 
{
    Huffman* left, * right, * top;

    MinHeap* minHeap = buildMinHeap(characters, frequencies, size);

    while (minHeap->size != 1) 
    {
        // �� ���� �ּ� �� ��� ����
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // �� ��带 �����Ͽ� ���ο� ��带 ����
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        // ���� ������ ���ڸ� ���
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, top->frequency);

        // ���� ���� ��带 ���� ����
        insertMinHeap(minHeap, top);

        // ���� �� ���� ��� (���ڸ�)
        printHeap(minHeap);
    }
    return extractMin(minHeap);
}

// ������ �ڵ� ��� �Լ�
void printCodes(Huffman* root, int arr[], int top) 
{
    if (root->left) 
    {
        arr[top] = 1; // ���� �ڽ��� 1
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) 
    {
        arr[top] = 0; // ������ �ڽ��� 0
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

// GenerateHuffmanCodes �Լ� ����
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


