#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// �׷����� �� ��带 ��Ÿ���� ����ü
typedef struct Node 
{
    int vertex;        // ����� ���� ��ȣ
    int weight;        // ������ ����ġ
    struct Node* next; // ���� ��带 ����Ű�� ������
} Node;


// �׷����� ��Ÿ���� ����ü
typedef struct Graph 
{
    int vertices;     // ������ ����
    Node** adjList;   // ���� ����Ʈ �迭
} Graph;


// �ּ� ���� ��带 ��Ÿ���� ����ü
typedef struct MinHeapNode 
{
    int vertex;  // ���� ��ȣ
    int dist;    // �ִ� �Ÿ� ��
} MinHeapNode;


// �ּ� �� ����ü
typedef struct MinHeap 
{
    int size;            // ���� ���� ���Ե� ��� ��
    int capacity;        // ���� �ִ� �뷮
    int* pos;            // ������ ��ġ �迭
    MinHeapNode** array; // �� ����� �迭
} MinHeap;


// �� ��� ���� �Լ�
Node* createNode(int vertex, int weight) 
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // �� ��� �޸� �Ҵ�

    newNode->vertex = vertex; // ����� ���� ��ȣ ����
    newNode->weight = weight; // ����� ����ġ ����
    newNode->next = NULL; // ���� ���� ���� ����

    return newNode;
}


// �� �׷��� ���� �Լ�
Graph* createGraph(int vertices) 
{
    Graph* graph = (Graph*)malloc(sizeof(Graph)); // �׷��� �޸� �Ҵ�
    graph->vertices = vertices; // ���� ���� ����
    graph->adjList = (Node**)malloc((vertices + 1) * sizeof(Node*)); // ���� ����Ʈ �迭 ����

    for (int i = 0; i <= vertices; i++) // ��� ���� ����Ʈ �ʱ�ȭ
        graph->adjList[i] = NULL;

    return graph;
}


// �׷����� ���� �߰� �Լ� (�����)
void addEdge(Graph* graph, int src, int dest, int weight) 
{
    Node* newNode = createNode(dest, weight); // ���� ������ ���� �� ��� ����
    newNode->next = graph->adjList[src]; // ���� �ִ� ����Ʈ �տ� ����
    graph->adjList[src] = newNode; // ��� ������ ����Ʈ�� ����

    newNode = createNode(src, weight); // �ݴ� ���� ���� ����
    newNode->next = graph->adjList[dest]; // ���� ������ ����Ʈ�� ����
    graph->adjList[dest] = newNode; // ����Ʈ ������Ʈ
}


// �ּ� �� ���� �Լ�
MinHeap* createMinHeap(int capacity) 
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap)); // �� �޸� �Ҵ�

    minHeap->pos = (int*)malloc((capacity + 1) * sizeof(int)); // ��ġ �迭 ����
    minHeap->size = 0; // �ʱ� ũ�� ����
    minHeap->capacity = capacity; // �뷮 ����
    minHeap->array = (MinHeapNode**)malloc((capacity + 1) * sizeof(MinHeapNode*)); // ��� �迭 ����

    return minHeap;
}


// �ּ� ���� �� ��带 ��ȯ�ϴ� �Լ�
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) 
{
    MinHeapNode* t = *a; // �ӽ� �����ͷ� ��ȯ
    *a = *b;
    *b = t;
}


// �ּ� ���� ���� ���·� ����� �Լ� (Heapify)
void MinHeapify(MinHeap* minHeap, int idx) 
{
    int smallest = idx; // ���� ��带 ���� ���� ���� �ʱ�ȭ
    int left = 2 * idx + 1; // ���� �ڽ� ��� �ε���
    int right = 2 * idx + 2; // ������ �ڽ� ��� �ε���

    // ���� �ڽ��� �� ������ smallest ����
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    // ������ �ڽ��� �� ������ smallest ����
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    // �ʿ� �� ��ġ ��ȯ �� ��� ȣ��� ���� ����
    if (smallest != idx) 
    {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->vertex] = idx; // ��ġ ����
        minHeap->pos[idxNode->vertex] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        MinHeapify(minHeap, smallest); // ��� ȣ��� �� ���� ����
    }
}


// �ּ� ������ �ּ� ��带 �����ϴ� �Լ�
MinHeapNode* selectMinHeapNode(MinHeap* minHeap)
{
    if (minHeap->size == 0) // ���� ����ִ� ���
        return NULL;

    MinHeapNode* root = minHeap->array[0]; // �ּڰ��� root�� ����
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; // ������ ��带 root�� �̵�
    minHeap->array[0] = lastNode;

    minHeap->pos[root->vertex] = minHeap->size - 1; // ��ġ ����
    minHeap->pos[lastNode->vertex] = 0;

    --minHeap->size; // �� ũ�� ����
    MinHeapify(minHeap, 0); // ��Ʈ���� �����Ͽ� �� ���� ����

    return root; // �ּڰ� ��ȯ
}


// ������ �ּ� �Ÿ� ���� �����ϴ� �Լ� (�� ª�� �Ÿ� ���� �߰� �� ����)
void decreaseKey(MinHeap* minHeap, int v, int dist) 
{
    int i = minHeap->pos[v]; // ���� v�� �� �� ��ġ
    minHeap->array[i]->dist = dist; // �Ÿ� �� ����

    // �θ� ���� ���Ͽ� �� ���� ���� ���� (�θ� ��尡 �ڽĺ��� �۾ƾ� �ϴ� Ư�� ����)
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
    {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2; // �θ� �ε����� �̵�
    }
}


// ������ �ּ� ���� �ִ��� Ȯ���ϴ� �Լ�
int checkVertex(MinHeap* minHeap, int v) 
{
    return minHeap->pos[v] < minHeap->size; // ��ġ�� ��ȿ���� Ȯ��
}


// �� ������ �Ÿ��� �߰� ���� ��� �Լ�
void printDistance(int* dist, int* found, int V) 
{
    printf("Distance: ");

    for (int i = 1; i <= 10; i++) 
    {
        if (i > V) break;

        if (dist[i] == INT_MAX)
            printf("* ");

        else
            printf("%d ", dist[i]);
    }
    printf("\nFound: ");

    for (int i = 1; i <= 10; i++) 
    {
        if (i > V) break;
        printf("%d ", found[i]);
    }
    printf("\n\n");
}


// ���ͽ�Ʈ�� �˰��� ���� �Լ� (�ּ� ��)
void dijkstra(Graph* graph, int src)
{
    int p = graph->vertices;
    int* dist = (int*)malloc((p + 1) * sizeof(int)); // �Ÿ� �迭
    int* found = (int*)malloc((p + 1) * sizeof(int)); // �߰� �迭
    int* foundOrder = (int*)malloc((p + 1) * sizeof(int)); // �߰� ���� ��� �迭
    int foundCount = 0;

    // �ʱ� �Ÿ��� �� �߰� ���� �ʱ�ȭ
    for (int i = 1; i <= p; i++)
    {
        dist[i] = INT_MAX;
        found[i] = 0;
    }
    dist[src] = 0; // ���� ������ �Ÿ��� 0

    // �ּ� ���� ����ϴ� dijkstra �˰���
    MinHeap* minHeap = createMinHeap(p);

    for (int v = 1; v <= p; v++)
    {
        minHeap->array[v - 1] = (MinHeapNode*)malloc(sizeof(MinHeapNode));
        minHeap->array[v - 1]->vertex = v;
        minHeap->array[v - 1]->dist = dist[v];
        minHeap->pos[v] = v - 1;
    }

    minHeap->size = p;
    decreaseKey(minHeap, src, dist[src]); // ���� ������ Ű�� ����

    while (minHeap->size)
    {
        MinHeapNode* minHeapNode = selectMinHeapNode(minHeap); // �ִ� �Ÿ� ��� ����
        int u = minHeapNode->vertex;
        found[u] = 1; // ���� u�� �߰����� ǥ��
        foundOrder[foundCount++] = u;

        // �߰ߵ� ������ �Ÿ� ���
        printDistance(dist, found, p); // �� �ܰ� ���

        Node* temp = graph->adjList[u]; // u�� ���� ���� Ȯ��

        while (temp != NULL)
        {
            int v = temp->vertex;

            if (!found[v] && dist[u] != INT_MAX && dist[u] + temp->weight < dist[v])
            {
                dist[v] = dist[u] + temp->weight; // �Ÿ� ����
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
        free(minHeapNode); // ����� ��� �޸� ����
    }

    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);

    // �߰ߵ� ���� ���� ���
    printf("Found Order: ");

    for (int i = 0; i < foundCount; i++)
    {
        printf("%d ", foundOrder[i]);
    }
    printf("\n");

    free(dist);
    free(found);
    free(foundOrder);
}


int main(void) 
{
    int vertices = 10; // �׷����� ���� ���� ����

    Graph* graph = createGraph(vertices); // �׷��� ����

    // ���� �߰�
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 6, 11);
    addEdge(graph, 1, 7, 12);
    addEdge(graph, 2, 3, 5);
    addEdge(graph, 2, 4, 4);
    addEdge(graph, 2, 5, 1);
    addEdge(graph, 2, 6, 7);
    addEdge(graph, 2, 7, 8);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 3, 7, 6);
    addEdge(graph, 3, 8, 5);
    addEdge(graph, 4, 5, 13);
    addEdge(graph, 4, 8, 14);
    addEdge(graph, 4, 10, 16);
    addEdge(graph, 5, 6, 9);
    addEdge(graph, 5, 9, 18);
    addEdge(graph, 5, 10, 17);
    addEdge(graph, 7, 8, 13);
    addEdge(graph, 8, 10, 15);
    addEdge(graph, 9, 10, 10);

    dijkstra(graph, 1); // ���� ���� 1�� dijkstra ȣ��

    return 0;
}