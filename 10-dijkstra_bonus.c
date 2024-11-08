#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// 그래프의 각 노드를 나타내는 구조체
typedef struct Node 
{
    int vertex;        // 연결된 정점 번호
    int weight;        // 간선의 가중치
    struct Node* next; // 다음 노드를 가리키는 포인터
} Node;


// 그래프를 나타내는 구조체
typedef struct Graph 
{
    int vertices;     // 정점의 개수
    Node** adjList;   // 인접 리스트 배열
} Graph;


// 최소 힙의 노드를 나타내는 구조체
typedef struct MinHeapNode 
{
    int vertex;  // 정점 번호
    int dist;    // 최단 거리 값
} MinHeapNode;


// 최소 힙 구조체
typedef struct MinHeap 
{
    int size;            // 현재 힙에 포함된 노드 수
    int capacity;        // 힙의 최대 용량
    int* pos;            // 정점의 위치 배열
    MinHeapNode** array; // 힙 노드의 배열
} MinHeap;


// 새 노드 생성 함수
Node* createNode(int vertex, int weight) 
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // 새 노드 메모리 할당

    newNode->vertex = vertex; // 노드의 정점 번호 설정
    newNode->weight = weight; // 노드의 가중치 설정
    newNode->next = NULL; // 다음 노드는 아직 없음

    return newNode;
}


// 새 그래프 생성 함수
Graph* createGraph(int vertices) 
{
    Graph* graph = (Graph*)malloc(sizeof(Graph)); // 그래프 메모리 할당
    graph->vertices = vertices; // 정점 개수 설정
    graph->adjList = (Node**)malloc((vertices + 1) * sizeof(Node*)); // 인접 리스트 배열 생성

    for (int i = 0; i <= vertices; i++) // 모든 인접 리스트 초기화
        graph->adjList[i] = NULL;

    return graph;
}


// 그래프에 간선 추가 함수 (양방향)
void addEdge(Graph* graph, int src, int dest, int weight) 
{
    Node* newNode = createNode(dest, weight); // 도착 정점에 대한 새 노드 생성
    newNode->next = graph->adjList[src]; // 원래 있던 리스트 앞에 삽입
    graph->adjList[src] = newNode; // 출발 정점의 리스트에 연결

    newNode = createNode(src, weight); // 반대 방향 간선 생성
    newNode->next = graph->adjList[dest]; // 도착 정점의 리스트에 연결
    graph->adjList[dest] = newNode; // 리스트 업데이트
}


// 최소 힙 생성 함수
MinHeap* createMinHeap(int capacity) 
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap)); // 힙 메모리 할당

    minHeap->pos = (int*)malloc((capacity + 1) * sizeof(int)); // 위치 배열 생성
    minHeap->size = 0; // 초기 크기 설정
    minHeap->capacity = capacity; // 용량 설정
    minHeap->array = (MinHeapNode**)malloc((capacity + 1) * sizeof(MinHeapNode*)); // 노드 배열 생성

    return minHeap;
}


// 최소 힙의 두 노드를 교환하는 함수
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) 
{
    MinHeapNode* t = *a; // 임시 포인터로 교환
    *a = *b;
    *b = t;
}


// 최소 힙을 정렬 상태로 만드는 함수 (Heapify)
void MinHeapify(MinHeap* minHeap, int idx) 
{
    int smallest = idx; // 현재 노드를 가장 작은 노드로 초기화
    int left = 2 * idx + 1; // 왼쪽 자식 노드 인덱스
    int right = 2 * idx + 2; // 오른쪽 자식 노드 인덱스

    // 왼쪽 자식이 더 작으면 smallest 갱신
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    // 오른쪽 자식이 더 작으면 smallest 갱신
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    // 필요 시 위치 교환 및 재귀 호출로 정렬 유지
    if (smallest != idx) 
    {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->vertex] = idx; // 위치 갱신
        minHeap->pos[idxNode->vertex] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        MinHeapify(minHeap, smallest); // 재귀 호출로 힙 정렬 유지
    }
}


// 최소 힙에서 최소 노드를 선별하는 함수
MinHeapNode* selectMinHeapNode(MinHeap* minHeap)
{
    if (minHeap->size == 0) // 힙이 비어있는 경우
        return NULL;

    MinHeapNode* root = minHeap->array[0]; // 최솟값을 root로 설정
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; // 마지막 노드를 root로 이동
    minHeap->array[0] = lastNode;

    minHeap->pos[root->vertex] = minHeap->size - 1; // 위치 갱신
    minHeap->pos[lastNode->vertex] = 0;

    --minHeap->size; // 힙 크기 감소
    MinHeapify(minHeap, 0); // 루트에서 시작하여 힙 정렬 유지

    return root; // 최솟값 반환
}


// 정점의 최소 거리 값을 갱신하는 함수 (더 짧은 거리 값을 발견 시 갱신)
void decreaseKey(MinHeap* minHeap, int v, int dist) 
{
    int i = minHeap->pos[v]; // 정점 v의 힙 내 위치
    minHeap->array[i]->dist = dist; // 거리 값 갱신

    // 부모 노드와 비교하여 힙 정렬 상태 유지 (부모 노드가 자식보다 작아야 하는 특성 유지)
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
    {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2; // 부모 인덱스로 이동
    }
}


// 정점이 최소 힙에 있는지 확인하는 함수
int checkVertex(MinHeap* minHeap, int v) 
{
    return minHeap->pos[v] < minHeap->size; // 위치가 유효한지 확인
}


// 각 정점의 거리와 발견 여부 출력 함수
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


// 다익스트라 알고리즘 구현 함수 (최소 힙)
void dijkstra(Graph* graph, int src)
{
    int p = graph->vertices;
    int* dist = (int*)malloc((p + 1) * sizeof(int)); // 거리 배열
    int* found = (int*)malloc((p + 1) * sizeof(int)); // 발견 배열
    int* foundOrder = (int*)malloc((p + 1) * sizeof(int)); // 발견 순서 기록 배열
    int foundCount = 0;

    // 초기 거리값 및 발견 여부 초기화
    for (int i = 1; i <= p; i++)
    {
        dist[i] = INT_MAX;
        found[i] = 0;
    }
    dist[src] = 0; // 시작 정점의 거리는 0

    // 최소 힙을 사용하는 dijkstra 알고리즘
    MinHeap* minHeap = createMinHeap(p);

    for (int v = 1; v <= p; v++)
    {
        minHeap->array[v - 1] = (MinHeapNode*)malloc(sizeof(MinHeapNode));
        minHeap->array[v - 1]->vertex = v;
        minHeap->array[v - 1]->dist = dist[v];
        minHeap->pos[v] = v - 1;
    }

    minHeap->size = p;
    decreaseKey(minHeap, src, dist[src]); // 시작 정점의 키값 감소

    while (minHeap->size)
    {
        MinHeapNode* minHeapNode = selectMinHeapNode(minHeap); // 최단 거리 노드 추출
        int u = minHeapNode->vertex;
        found[u] = 1; // 정점 u를 발견으로 표시
        foundOrder[foundCount++] = u;

        // 발견된 정점의 거리 출력
        printDistance(dist, found, p); // 각 단계 출력

        Node* temp = graph->adjList[u]; // u의 인접 정점 확인

        while (temp != NULL)
        {
            int v = temp->vertex;

            if (!found[v] && dist[u] != INT_MAX && dist[u] + temp->weight < dist[v])
            {
                dist[v] = dist[u] + temp->weight; // 거리 갱신
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
        free(minHeapNode); // 추출된 노드 메모리 해제
    }

    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);

    // 발견된 정점 순서 출력
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
    int vertices = 10; // 그래프의 정점 개수 설정

    Graph* graph = createGraph(vertices); // 그래프 생성

    // 간선 추가
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

    dijkstra(graph, 1); // 시작 정점 1로 dijkstra 호출

    return 0;
}