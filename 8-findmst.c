#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // 부모 노드 배열

void set_init(int n)    // 초기화
{
    for (int i = 0; i < n; i++)
        parent[i] = -1; // 모든 정점의 부모를 -1로 초기화 (루트 노드)
}

// curr가 속하는 집합을 반환한다.
int set_find(int curr) // 반환형 추가
{
    if (parent[curr] == -1)
        return curr; // curr가 루트 노드인 경우

    // 루트 노드를 찾기 위한 경로 압축
    while (parent[curr] != -1) curr = parent[curr];

    return curr;
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
    int root1 = set_find(a); // 노드 a의 루트를 찾는다.
    int root2 = set_find(b); // 노드 b의 루트를 찾는다.

    if (root1 != root2) // 서로 다른 집합인 경우
        parent[root1] = root2; // root1을 root2에 합친다.
}

struct Edge // 간선을 나타내는 구조체
{
    int start, end, weight; // 시작 정점, 끝 정점, 가중치
};

typedef struct GraphType
{
    int n; // 간선의 개수
    struct Edge edges[2 * MAX_VERTICES]; // 간선 배열
} GraphType;

// 최소 힙 구조체
typedef struct MinHeap
{
    int size; // 힙의 크기
    struct Edge* edges[MAX_VERTICES * 2]; // 간선 배열
} MinHeap;

// 힙 초기화
void init_heap(MinHeap* heap)
{
    heap->size = 0; // 힙의 크기를 0으로 초기화
}

// 힙에 간선 추가
void insert_heap(MinHeap* heap, struct Edge* edge)
{
    int i = heap->size++; // 새로 추가할 간선의 인덱스

    // 힙 구조 유지
    while (i > 0)
    {
        int parent = (i - 1) / 2; // 부모 인덱스

        if (heap->edges[parent]->weight <= edge->weight)
            break; // 부모의 가중치가 더 크거나 같으면 종료

        heap->edges[i] = heap->edges[parent]; // 부모를 아래로 내림
        i = parent; // 인덱스를 부모로 이동
    }
    heap->edges[i] = edge; // 현재 위치에 새로운 간선 추가
}

// 힙에서 최소 간선 제거
struct Edge* remove_min(MinHeap* heap)
{
    if (heap->size == 0)
        return NULL; // 힙이 비어있으면 NULL 반환

    struct Edge* min_edge = heap->edges[0]; // 최소 간선 저장
    struct Edge* last_edge = heap->edges[--heap->size]; // 마지막 간선 저장 후 크기 감소

    int i = 0;

    // 힙 구조 유지
    while (1)
    {
        int left = 2 * i + 1; // 왼쪽 자식 인덱스
        int right = 2 * i + 2; // 오른쪽 자식 인덱스
        int smallest = i; // 가장 작은 간선의 인덱스 초기화

        // 왼쪽 자식과 비교
        if (left < heap->size && heap->edges[left]->weight < last_edge->weight)
        {
            smallest = left;
        }

        // 오른쪽 자식과 비교
        if (right < heap->size && heap->edges[right]->weight < heap->edges[smallest]->weight)
        {
            smallest = right;
        }

        if (smallest == i)
            break; // 더 이상 교환할 필요가 없으면 종료

        heap->edges[i] = heap->edges[smallest]; // 교환
        i = smallest; // 인덱스를 가장 작은 자식으로 이동
    }
    heap->edges[i] = last_edge; // 마지막 간선 위치 설정

    return min_edge; // 최소 간선 반환
}

// 그래프 초기화 
void graph_init(GraphType* g)
{
    g->n = 0; // 간선 개수를 0으로 초기화

    for (int i = 0; i < 2 * MAX_VERTICES; i++)
    {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF; // 간선의 기본 가중치를 무한대로 초기화
    }
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++; // 간선 개수 증가
}

// qsort()에 사용되는 함수 (정렬 기준)
int compare(const void* a, const void* b)
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight); // 가중치 기준으로 비교
}

// Kruskal 알고리즘 (정렬된 간선 사용)
GraphType* QuickKruskal(GraphType* g)
{
    int edge_accepted = 0; // 선택된 간선 수

    // 현재까지 선택된 간선의 수 
    int uset, vset;
    struct Edge e;

    set_init(g->n); // 집합 초기화

    // 간선을 가중치 기준으로 정렬
    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    printf("Quick Based Kruskal \n");

    int i = 0;

    // 간선 선택
    while (edge_accepted < (g->n - 1) && i < g->n)
    {
        e = g->edges[i]; // 현재 간선
        uset = set_find(e.start); // 시작 정점의 집합
        vset = set_find(e.end); // 끝 정점의 집합

        if (uset != vset) // 서로 다른 집합인 경우
        {
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++; // 선택된 간선 수 증가
            set_union(uset, vset); // 두 집합 합치기
        }
        i++; // 다음 간선으로 이동
    }
    return g; // GraphType 포인터 반환
}

// 최소 힙을 이용한 Kruskal 알고리즘
void MinHeapKuskal(GraphType* g)
{
    int edge_accepted = 0; // 선택된 간선 수
    set_init(g->n); // 집합 초기화
    MinHeap heap; // 최소 힙 선언
    init_heap(&heap); // 힙 초기화

    printf("\nMinHeap Based Kruskal \n");

    // 간선을 최소 힙에 삽입
    for (int i = 0; i < g->n; i++)
    {
        struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge)); // 간선 메모리 할당
        *e = g->edges[i]; // 간선 복사
        insert_heap(&heap, e); // 힙에 간선 삽입
    }

    // 간선 선택
    while (edge_accepted < (g->n - 1) && heap.size > 0)
    {
        struct Edge* e = remove_min(&heap); // 최소 간선 제거
        int uset = set_find(e->start); // 시작 정점의 집합
        int vset = set_find(e->end); // 끝 정점의 집합

        // 간선의 집합이 다를 경우 선택
        if (uset != vset)
        {
            printf("Edge (%d, %d) select %d\n", e->start, e->end, e->weight);
            edge_accepted++; // 선택된 간선 수 증가
            set_union(uset, vset); // 두 집합 합치기
        }
        free(e);     // 메모리 해제
    }
}

// 그래프를 생성하는 함수
void GenerateGraph(GraphType* g)
{
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

int main(void)
{
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);   // 그래프를 생성

    QuickKruskal(g);
    MinHeapKuskal(g);

    free(g);
    return 0;
}
