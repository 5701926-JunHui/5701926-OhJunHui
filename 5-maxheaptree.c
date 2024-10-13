#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100


typedef struct  // ���� ����ü ���� 
{
    int heap[MAX_SIZE];
    int heap_size;
} TreeNode;


int parent(int i)   // �θ� �ε��� ���
{
    return (i - 1) / 2; // i/2�� �ƴ϶�, (i - 1) / 2�� ������ �迭�� �ε����� 1�� �ƴ϶� 0���� �����ϱ� ����
}


int leftChild(int i)    // ���� �ڽ� �ε��� ���
{
    return 2 * i + 1;
}


int rightChild(int i)   // ������ �ڽ� �ε��� ���
{
    return 2 * i + 2;
}


void PrintHeapMove(TreeNode* h) // ������ ���¸� ����ϴ� �Լ�
{
    for (int i = 0; i < h->heap_size; i++) 
    {
        printf("%d ", h->heap[i]);
    }
    printf("\n");
}


int HeapTreeDown(TreeNode* h, int i)    // ���� �� ��� �̵��� �� �� ������ ������ �����ϴ� �Լ�
{
    int largest = i;

    int left = leftChild(i);
    int right = rightChild(i);

    int moves = 0; // �̵� �� Ƚ��: 0���� �ʱ�ȭ

    // ���� �ڽ��� ���� ��庸�� ũ�ٸ� 
    if (left < h->heap_size && h->heap[left] > h->heap[largest])
        largest = left; // ���� ū ���� ���� ���� ������Ʈ

    // ������ �ڽ��� ������� ���� ū ��庸�� ũ�ٸ�
    if (right < h->heap_size && h->heap[right] > h->heap[largest])
        largest = right;    // ���� ū ���� ���� ���� ������Ʈ

    // ���� ū ���� ���� ��尡 �ƴ϶�� ��ü
    if (largest != i) 
    {
        // ��� ��ü
        int temp = h->heap[i];

        h->heap[i] = h->heap[largest];
        h->heap[largest] = temp;

        moves++; // �̵�

        PrintHeapMove(h);   // ��ü�� �� ���� ���¸� ���

        moves += HeapTreeDown(h, largest);  // �ڽ� ���� ��� �Ʒ��� �̵� -> ȣ��
    }

    return moves;
}

// ������ ���ο� ���� �ִ� �Լ�
void InsertMaxHeapTree(TreeNode* h, int value, int print, int userInput) 
{
    if (h->heap_size == MAX_SIZE) 
    {
        return;
    }

    // ���ο� ���� �߰�
    h->heap[h->heap_size] = value;
    int i = h->heap_size;
    h->heap_size++;

    // ������ �� ���� ���� ���
    if (print) 
    {
        PrintHeapMove(h);
    }

    int moves = 0; // �̵��� Ƚ��: 0���� �ʱ�ȭ

    while (i != 0 && h->heap[parent(i)] < h->heap[i]) 
    {
        // ��� ��ü
        int temp = h->heap[i];

        h->heap[i] = h->heap[parent(i)];
        h->heap[parent(i)] = temp;

        i = parent(i);

        moves++; // ��ü�� �Ͼ ������ �̵� Ƚ�� ����

        if (print)  // ��ü �� ���� ���¸� ���
        {
            PrintHeapMove(h);
        }
    }

    if (userInput)  // ����ڰ� ��Ҹ� �Է��� ��쿡�� �̵� Ƚ�� ���
    {
        printf("��尡 �̵��� Ƚ��: %d\n", moves);
    }
}


void DeleteMaxHeapTree(TreeNode* h) // �������� ��Ʈ(�ִ밪)�� �����ϴ� �Լ�
{
    if (h->heap_size == 0) 
    {
        return;
    }

    // ������ ��Ҹ� ��Ʈ�� �̵�
    h->heap[0] = h->heap[h->heap_size - 1];
    h->heap_size--;

    PrintHeapMove(h);

    int moves = HeapTreeDown(h, 0);

    printf("��尡 �̵��� Ƚ��: %d\n", moves);
}


void PrintHeapTree(TreeNode* h) // ������ �������� ����ϴ� �Լ�

{
    if (h->heap_size == 0) 
    {
        return;
    }

    int level = 0;
    int nodes_in_level = 1;     // �ش� �������� ����� ����� ��
    int index = 0;  // ���� ����� �ε���: 0���� �ʱ�ȭ

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
        nodes_in_level *= 2;    // ������ ������ ������ ����� ����� ���� 2�� �þ
    }
}

// �ִ� ���� ���� �Լ�
TreeNode* generateMaxHeapTree(int inputData[], int size) 
{
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));   // �޸� ���� �Ҵ�

    if (root == NULL)
    {
        exit(1);
    }
    root->heap_size = 0;    // �ʱ⿡�� ������ ũ��: 0���� �ʱ�ȭ


    for (int i = 0; i < size; i++) 
    {
        InsertMaxHeapTree(root, inputData[i], 0, 0);
    }
    return root;
}


void runUserInterface(TreeNode* root)   // �޴� â ��� �� ���α׷� ���� �Լ�
{
    char choice;
    int value;

    printf("-------------------\n");
    printf("| i: ��� �߰�    |\n");
    printf("| d: ��� ����    |\n");
    printf("| p: ������ ���  |\n");
    printf("| c: ����         |\n");
    printf("-------------------\n\n");

    while (1) 
    {
        printf("\n\n�޴� �Է�: ");
        scanf_s(" %c", &choice);

        switch (choice) 
        {
        case 'i':
            printf("�߰��� �� �Է�: ");
            scanf_s("%d", &value);
            InsertMaxHeapTree(root, value, 1, 1);
            break;

        case 'd':
            DeleteMaxHeapTree(root);
            break;

        case 'p':
            printf("Ʈ�� ������ ���\n");
            PrintHeapTree(root);
            break;

        case 'c':
            return;

        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }
}


int main(void)
{
    int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = generateMaxHeapTree(inputData, size);  // ���� ����

    runUserInterface(root); // ����ڰ� ��Ҹ� �Է��ϴ� �Լ� ����
    
    free(root); // �޸� �ݳ�
    return 0;
}





