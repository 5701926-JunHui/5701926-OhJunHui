#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 100


typedef struct GraphList    // ���� ����Ʈ ����ü ����
{
    int n;                      // �׷��� ����
    struct GraphList* next;     // ���� ��� ������
} GraphList;


typedef struct Graph    // �׷��� ����ü ���� (���� ����Ʈ �迭 ����)
{
    GraphList* adjList[MAX_NODES];  // �� ����� ���� ����Ʈ
} Graph;


void initGraph(Graph* graph)    // �׷��� �ʱ�ȭ �Լ�
{
    for (int i = 0; i < MAX_NODES; i++) 
    {
        graph->adjList[i] = NULL;   // ��� ���� ����Ʈ�� NULL�� �ʱ�ȭ
    }
}

// �׷����� ���� �߰� �Լ�
void addEdge(Graph* graph, int node1, int node2) 
{
    // node1 -> node2 ���� ���� �߰� (���� ����Ʈ ���)
    GraphList* newNode = (GraphList*)malloc(sizeof(GraphList));
    newNode->n = node2;
    newNode->next = graph->adjList[node1];
    graph->adjList[node1] = newNode;

    // node2 -> node1 ���� ���� �߰� (������ ���� �׷����̱� ������)
    newNode = (GraphList*)malloc(sizeof(GraphList));
    newNode->n = node1;
    newNode->next = graph->adjList[node2];
    graph->adjList[node2] = newNode;
}

// ���� �켱 Ž�� �Լ�
void DFS(Graph* graph, int start, int target) 
{
    int stack[MAX_NODES], top = -1;
    int visit[MAX_NODES] = { 0 };  // �湮 �迭 (0: �湮����, 1: �湮��)
    int count = 0;

    stack[++top] = start;  // ���� ��带 ���ÿ� �߰�
    printf("Ž�� ���: ");

    // ������ �� ������ �ݺ�
    while (top != -1) 
    {
        int node = stack[top--];  // ���ÿ��� ��带 ����

        // ���� �湮���� ���� ��常 ó��
        if (!visit[node]) 
        {
            visit[node] = 1;  // ��� �湮 ó��
            printf("%d ", node);  // Ž�� ��� ���
            count++;

            // ��ǥ ��忡 �����ϸ� Ž�� ����
            if (node == target) 
            {
                printf("\nŽ�� ����: %d\n�湮�� ����� ��: %d\n", target, count);
                return;
            }

            // ���� ������ ���ÿ� �߰� (���� ��ȣ���� ó���ǵ��� �������� �߰�)
            GraphList* temp = graph->adjList[node];

            int adjNodes[MAX_NODES];
            int adjCount = 0;

            while (temp != NULL) 
            {
                if (!visit[temp->n]) 
                {
                    adjNodes[adjCount++] = temp->n;
                }
                temp = temp->next;
            }

            // ���� ��ȣ���� ���ÿ� �߰��ϱ� ���� �������� ó�� (1 2 3 -> 3 2 1)
            for (int i = adjCount - 1; i >= 0; i--) 
            {
                stack[++top] = adjNodes[i];
            }
        }
        else 
        {
            // �̹� �湮�� ���� ��Ʈ��ŷ�� ������ ���� ���
            printf("%d ", node);
        }
    }
    // ������ ��� ������� �� ��ǥ ��带 ã�� ���� ���
    printf("\nŽ�� ����: %d\n", target);
}

// �ʺ� �켱 Ž�� (BFS) �Լ�
void BFS(Graph* graph, int start, int target) 
{
    int queue[MAX_NODES], front = -1, rear = -1;
    int visit[MAX_NODES] = { 0 };  // �湮 �迭
    int count = 0;

    queue[++rear] = start;  // ���� ��带 ť�� �߰�
    visit[start] = 1;       // ���� ��� �湮 ó��

    
    while (front != rear)   // ť�� �� ������ �ݺ�
    {
        front++;
        int node = queue[front];    // ť���� ��带 ����
        printf("%d ", node);        // Ž�� ��� ���
        count++;

        if (node == target) // ��ǥ ��忡 �����ϸ� Ž�� ����
        {
            printf("\nŽ�� ����: %d\n�湮�� ����� ��: %d\n", target, count);
            return;
        }

        // ���� ������ ť�� �߰� (�湮���� ���� ��常)
        for (GraphList* temp = graph->adjList[node]; temp != NULL; temp = temp->next) 
        {
            if (!visit[temp->n]) 
            {
                visit[temp->n] = 1;         // �湮 ó��
                queue[++rear] = temp->n;    // ť�� �߰�
            }
        }
    }

    // ť�� ��� ������� �� ��ǥ ��带 ã�� ���� ���
    printf("\nŽ�� ����: %d\n", target);
}

int main(void) 
{
    Graph graph;
    initGraph(&graph);  // �׷��� �ʱ�ȭ

    // �׷��� ���� �߰�
    addEdge(&graph, 0, 2);
    addEdge(&graph, 0, 4);
    addEdge(&graph, 0, 5);
    addEdge(&graph, 0, 6);
    addEdge(&graph, 0, 9);
    addEdge(&graph, 1, 4);
    addEdge(&graph, 1, 5);
    addEdge(&graph, 1, 7);
    addEdge(&graph, 1, 10);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 2, 4);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 3, 5);
    addEdge(&graph, 4, 5);
    addEdge(&graph, 4, 6);
    addEdge(&graph, 4, 7);
    addEdge(&graph, 6, 7);
    addEdge(&graph, 6, 8);
    addEdge(&graph, 7, 10);
    addEdge(&graph, 8, 9);
    addEdge(&graph, 8, 10);

    // �޴� ���
    printf("---------------------\n");
    printf("| 1 : ���� �켱 Ž�� |\n");
    printf("| 2 : �ʺ� �켱 Ž�� |\n");
    printf("| 3 : ����           |\n");
    printf("---------------------\n\n");

    while (1)   // ������� �Է¿� ���� Ž�� ����
    {
        int choice, start, target;

        printf("\n\n�޴� �Է�: ");
        scanf_s("%d", &choice);

        if (choice == 3)    // 3�� �Է��ϸ�
        {
            printf("���α׷� ����\n");    // ���α׷� ����
            break;
        }

        printf("���� ��ȣ�� Ž���� �� �Է�: ");
        scanf_s("%d %d", &start, &target);

        if (choice == 1)    // 1�� �Է��ϸ�
        {
            DFS(&graph, start, target);  // ���� �켱 Ž�� ����
        }
        else if (choice == 2)   // 2�� �Է��ϸ�
        {
            BFS(&graph, start, target);  // �ʺ� �켱 Ž�� ����
        }
        else 
        {
            printf("�߸��� �޴� �����Դϴ�.\n");
        }
    }
    return 0;
}
