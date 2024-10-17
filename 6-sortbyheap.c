#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int* b)   // �� ��Ҹ� ��ȯ�ϴ� �Լ�
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void resortHeap(int inputData[], int n, int i)  // ���� �������ϴ� �Լ�
{
    int largest = i; // ��Ʈ�� ���� ū ������ ����
    int left = 2 * i + 1; // ���� �ڽ�
    int right = 2 * i + 2; // ������ �ڽ�

    // ���� �ڽ��� �� ũ�ٸ�
    if (left < n && inputData[left] > inputData[largest])
        largest = left; // ���� ū ��尡 ���� ����

    // ������ �ڽ��� �� ũ�ٸ�
    if (right < n && inputData[right] > inputData[largest])
        largest = right;    // ���� ū ��尡 ������ ����

    if (largest != i)   // ��Ʈ�� ���� ū ���� �ƴ϶��
    {
        swap(&inputData[i], &inputData[largest]);
        // �ٲ� �ڽ� ��带 ������
        resortHeap(inputData, n, largest);
    }
}


void BuildMaxHeap(int inputData[], int n)   // �ִ� ���� �����ϴ� �Լ�
{
    for (int i = 1; i <= n; i++)    // ��Ҹ� �ϳ��� ���� �����ϴ� ������ ���
    {
        for (int j = i / 2 - 1; j >= 0; j--)    // �κ� �迭�� ���� ����� ����
        {
            resortHeap(inputData, i, j);
        }

        for (int k = 0; k < i; k++) // ������� ���� �߰��� ���� ���
        {
            printf("%d ", inputData[k]);
        }
        printf("\n");
    }
}


void BuildMaxHeapAndSort(int inputData[], int n)    // �� ���� ���� �Լ�
{
    BuildMaxHeap(inputData, n);  // �ִ� �� ����

    for (int i = n - 1; i > 0; i--) // �ϳ��� ������ ��Ʈ(�ִ밪)�� �����ϰ� ����
    {
        swap(&inputData[0], &inputData[i]); // �ִ밪�� ��Ʈ(0��° ���)�� ������ ����

        resortHeap(inputData, i, 0);    // �� ������ �� ���� ���

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

    printf("<Sort>\n"); // �� ���� ����
    BuildMaxHeapAndSort(inputData, size);

    printf("\nSorted Array:\n");    // ���ĵ� ��� ���
    
    for (int i = 0; i < size; i++) 
    {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}





