#include <stdio.h>
#include <stdlib.h>


typedef struct Node // Huffman Ʈ���� ��� ����ü ����
{
    char character;    // ����
    int frequency;     // �ش� ������ ��
    struct Node* left, * right;    // ����, ������ �ڽ� ��� ������
} Huffman;


typedef struct MinHeap  // �ּ� �� ����ü ����
{
    int size;        // ���� ���� �ִ� ����� ��
    int capacity;    // ���� �ִ� �뷮
    Huffman** array; // ��� ������ �迭 (���� ����)
} MinHeap;


Huffman* createNode(char character, int frequency)  // ���ο� ��� ���� �Լ�
{
    Huffman* newNode = (Huffman*)malloc(sizeof(Huffman));  // ���ο� ��� �޸� �Ҵ�

    newNode->character = character;  // ���� ����
    newNode->frequency = frequency;  // �� ����
    newNode->left = newNode->right = NULL;  // �ڽ� ���� NULL�� �ʱ�ȭ

    return newNode;  // ������ ��� ��ȯ
}


MinHeap* createMinHeap(int capacity)    // �ּ� �� ���� �Լ�
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));  // �ּ� �� �޸� �Ҵ�

    minHeap->size = 0;   // �ʱ� ũ��� 0
    minHeap->capacity = capacity;  // ���� �뷮 ����
    minHeap->array = (Huffman**)malloc(minHeap->capacity * sizeof(Huffman*));  // ��� �迭 ����

    return minHeap;  // ������ �ּ� �� ��ȯ
}


void swapNodes(Huffman** a, Huffman** b)    // �� ��带 ��ȯ�ϴ� �Լ�
{
    Huffman* t = *a;  // �ӽ� ������ ù ��° ��带 ����
    *a = *b;          // �� ��° ��带 ù ��° ��ġ�� �̵�
    *b = t;           // �ӽ� ������ ����� ù ��° ��带 �� ��° ��ġ�� �̵�
}


void minHeapify(MinHeap* minHeap, int idx)  // �ּ� ��(Heapify) �Լ�
{
    int smallest = idx;          // ���� ��带 ���� ���� ���� ����
    int left = 2 * idx + 1;      // ���� �ڽ��� �ε��� ���
    int right = 2 * idx + 2;     // ������ �ڽ��� �ε��� ���

    // ���� �ڽ��� �����ϰ�, ���� ��庸�� �󵵰� �� �۴ٸ� ���� ��� ������Ʈ
    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    // ������ �ڽ��� �����ϰ�, �� ���� �󵵶�� ���� ��� ������Ʈ
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    // ���� ��尡 ���� ��尡 �ƴ϶�� �ٲٰ� �� �Ӽ��� ����
    if (smallest != idx)
    {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}


Huffman* extractMin(MinHeap* minHeap)   // �ּ� ������ �ּڰ��� �����ϴ� �Լ�
{
    Huffman* temp = minHeap->array[0];  // ��Ʈ ���(�ּڰ�) ����
    minHeap->array[0] = minHeap->array[minHeap->size - 1];  // ������ ��带 ��Ʈ�� �̵�
    --minHeap->size;  // �� ũ�� ����

    minHeapify(minHeap, 0); // ��Ʈ���� �� �Ӽ��� �ٽ� ����

    return temp;  // ����� ��� ��ȯ
}


void insertMinHeap(MinHeap* minHeap, Huffman* node) // �ּ� �� ���� �Լ�
{
    ++minHeap->size;  // �� ũ�� ����
    int i = minHeap->size - 1;  // ������ �ε������� ����

    // �θ� ��庸�� �󵵰� ���� ��� ���� �̵�
    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];  // �θ� ��带 �Ʒ��� �̵�
        i = (i - 1) / 2;  // �θ��� �ε����� �̵�
    }
    minHeap->array[i] = node;  // ���ο� ��带 ����
}


void printHeap(MinHeap* minHeap)    // �� ���� ��� �Լ�
{
    for (int i = 0; i < minHeap->size; ++i)
    {
        printf("%d ", minHeap->array[i]->frequency);  // �� ����� �� ���
    }
    printf("\n");
}


MinHeap* buildMinHeap(char characters[], int frequencies[], int size)   // �־��� �󵵸� ������� �ּ� ���� �����ϴ� �Լ�
{
    MinHeap* minHeap = createMinHeap(size);  // �ּ� �� ����

    // �� ���ڿ� �󵵸� ������� ���� ��带 ����
    for (int i = 0; i < size; ++i)
    {
        insertMinHeap(minHeap, createNode(characters[i], frequencies[i]));  // ���ο� ��� ����
        printHeap(minHeap); // ���� �� �� ���
    }
    return minHeap;  // ������ �ּ� �� ��ȯ
}


Huffman* BuildHuffmanTree(char characters[], int frequencies[], int size)   // ������ Ʈ�� ���� �Լ�
{
    Huffman* left, * right, * top;

    MinHeap* minHeap = buildMinHeap(characters, frequencies, size);  // �ּ� �� ����

    // �ּ� ���� �ϳ��� ��常 ���� ������ �ݺ�
    while (minHeap->size != 1)
    {
        // �� ���� �ּ� �� ��� ����
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // �� ��带 �����Ͽ� ���ο� ��� ���� (���� ���� ���� ���ο� ���)
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        // ���� ���� ���
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, top->frequency);

        // ���� ���� ��带 ���� ����
        insertMinHeap(minHeap, top);

        // ���� �� ���� ���
        printHeap(minHeap);
    }
    return extractMin(minHeap);  // ������ Ʈ���� ��Ʈ ��ȯ
}


void printCodes(Huffman* root, int arr[], int top)  // ������ �ڵ� ��� �Լ�
{
    // ���� �ڽ��� �����ϸ� 1�� �߰��ϰ� ��������� ȣ��
    if (root->left)
    {
        arr[top] = 1;  // ���� �ڽ��� 1
        printCodes(root->left, arr, top + 1);
    }

    // ������ �ڽ��� �����ϸ� 0�� �߰��ϰ� ��������� ȣ��
    if (root->right)
    {
        arr[top] = 0;  // ������ �ڽ��� 0
        printCodes(root->right, arr, top + 1);
    }

    // ���� ���(���� ���)�� �����ϸ� �ش� ���ڿ� �� �ڵ带 ���
    if (!(root->left) && !(root->right))
    {
        printf("%c: ", root->character);  // ���� ���

        for (int i = 0; i < top; i++)  // �迭�� ����� 0�� 1�� ���
            printf("%d", arr[i]);
        printf("\n");
    }
}


void GenerateHuffmanCodes(char characters[], int frequencies[], int size) // ������ �ڵ带 �����ϴ� �Լ�
{
    Huffman* root = BuildHuffmanTree(characters, frequencies, size);  // ������ Ʈ�� ����

    int arr[100], top = 0;  // �ڵ� ������ ���� �迭�� �ʱ� �ε���

    printCodes(root, arr, top);  // ������ �ڵ� ���
}

int main(void)
{
    // ���� ���ڿ� �� �迭
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);  // �迭�� ũ�� ���

    GenerateHuffmanCodes(characters, frequencies, size);  // ������ �ڵ� ���� �� ���

    return 0;
}
