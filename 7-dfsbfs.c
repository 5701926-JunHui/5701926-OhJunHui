#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 11

typedef struct GraphList     // �׷����� ���� ����Ʈ ����ü
{
    int n;                   // �׷��� ���� (���)
    struct GraphList* next;  // ���� ��带 ����Ű�� ������
} GraphList;


typedef struct Graph    // �׷��� ����ü 
{
    GraphList* adjList[MAX_NODES];  // �� ����� ���� ����Ʈ
} Graph;


void initGraph(Graph* graph)    // �׷��� �ʱ�ȭ �Լ�
{
    for (int i = 0; i < MAX_NODES; i++) // ��� ����� ���� ����Ʈ�� NULL�� �ʱ�ȭ
    {
        graph->adjList[i] = NULL;
    }
}


void addEdge(Graph* graph, int node1, int node2)   // ���� �߰� �Լ�
{
    // node1���� node2�� ���� ���� �߰�
    GraphList* newNode = (GraphList*)malloc(sizeof(GraphList));

    newNode->n = node2;
    newNode->next = graph->adjList[node1];
    graph->adjList[node1] = newNode;

    // ���� �׷����̱� ������ node2���� node1�� ���� ������ �߰�
    newNode = (GraphList*)malloc(sizeof(GraphList));

    newNode->n = node1;
    newNode->next = graph->adjList[node2];
    graph->adjList[node2] = newNode;
}

// ���� �켱 Ž�� �Լ�
void DFS(Graph* graph, int start, int target) 
{
    int stack[MAX_NODES], top = -1;          // ������ �̿��� DFS
    int visit[MAX_NODES] = { 0 };            // �湮 ���θ� ����ϴ� �迭
    int count = 0;                           // �湮�� ��� �� ī��Ʈ

    stack[++top] = start;                    // ���� ��带 ���ÿ� �߰�

    // ������ �� ������ Ž�� �ݺ�
    while (top != -1) 
    {
        int node = stack[top--];          // ���ÿ��� ��� ������
        
        if (!visit[node])
        {
            visit[node] = 1;            // ��带 �湮 ó��
            count++;
            printf("%d ", node);

            if (node == target)  // ��ǥ ��忡 �����ϸ� Ž�� ���� 
            {         
                printf("\nŽ�� ����: %d\n�湮�� ����� ��: %d\n", target, count);
                return;
            }

            // ���� ������ ���ÿ� �߰�
            for (GraphList* temp = graph->adjList[node]; temp != NULL; temp = temp->next)
            {
                if (!visit[temp->n]) 
                {    
                    stack[++top] = temp->n;
                }
            }
        }
    }
    printf("\nŽ�� ����: %d\n", target);
}

// �ʺ� �켱 Ž��(BFS) �Լ�
void BFS(Graph* graph, int start, int target)
{
    int queue[MAX_NODES], front = -1, rear = -1;  // ť�� �̿��� BFS
    int visit[MAX_NODES] = { 0 };                 // �湮 ���θ� ����ϴ� �迭
    int count = 0;                                // �湮�� ��� �� ī��Ʈ

    queue[++rear] = start;                        // ���� ��带 ť�� �߰�
    visit[start] = 1;                             // ���� ��� �湮 ó��

    // ť�� �� ������ Ž�� �ݺ�
    while (front != rear)
    {
        front++;
        int node = queue[front];                   // ť���� ��� ������
        printf("%d ", node);
        count++;                                   // �湮�� ��� �� ����

        if (node == target)  // ��ǥ ��忡 �����ϸ� Ž�� ����
        {
            printf("\nŽ�� ����: %d\n�湮�� ����� ��: %d\n", target, count);
            return;
        }

        // ���� ������ ť�� �߰�
        for (GraphList* temp = graph->adjList[node]; temp != NULL; temp = temp->next)
        {
            if (!visit[temp->n])
            {
                visit[temp->n] = 1;             // ��� �湮 ó��
                queue[++rear] = temp->n;       // ť�� �߰�
            }
        }
    }
    printf("\nŽ�� ����: %d\n", target);
}


int main(void) 
{
    Graph graph;                  // �׷��� ����
    initGraph(&graph);            // �׷��� �ʱ�ȭ

    // �׷��� ���� �߰�
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 1, 4);
    addEdge(&graph, 1, 5);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 2, 6);
    addEdge(&graph, 3, 5);
    addEdge(&graph, 4, 6);
    addEdge(&graph, 5, 7);
    addEdge(&graph, 6, 8);
    addEdge(&graph, 8, 9);
    addEdge(&graph, 9, 10);

    // �޴� ��� �� �Է� ó��
    printf("---------------------\n");
    printf("| 1 : ���� �켱 Ž�� |\n");
    printf("| 2 : �ʺ� �켱 Ž�� |\n");
    printf("| 3 : ����           |\n");
    printf("---------------------\n\n");

    while (1)
    {
        int choice, start, target;
        printf("\n\n�޴� �Է�: ");
        scanf_s("%d", &choice);  // Ž�� �ɼ� ����

        if (choice == 3)
        {
            printf("���α׷� ����\n");
            break;              // �޴� 3 ���� �� ���α׷� ����
        }

        // ���� ���� ��ǥ ��� �Է�
        printf("���� ��ȣ�� Ž���� �� �Է�: ");
        scanf_s("%d %d", &start, &target);

        if (choice == 1) 
        {
            DFS(&graph, start, target);  // �޴� 1 ���� �� ���� �켱 Ž�� ����
        }
        else if (choice == 2)
        {
            BFS(&graph, start, target);  // �޴� 2 ���� �� �ʺ� �켱 Ž�� ����
        }
        else 
        {
            printf("�߸��� �޴� �����Դϴ�.\n");
        }
    }
    return 0;
}
