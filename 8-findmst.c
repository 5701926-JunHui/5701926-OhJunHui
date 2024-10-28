#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // �θ� ��� �迭

void set_init(int n)    // �ʱ�ȭ
{
    for (int i = 0; i < n; i++)
        parent[i] = -1; // ��� ������ �θ� -1�� �ʱ�ȭ (��Ʈ ���)
}

// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr) // ��ȯ�� �߰�
{
    if (parent[curr] == -1)
        return curr; // curr�� ��Ʈ ����� ���

    // ��Ʈ ��带 ã�� ���� ��� ����
    while (parent[curr] != -1) curr = parent[curr];

    return curr;
}

// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b)
{
    int root1 = set_find(a); // ��� a�� ��Ʈ�� ã�´�.
    int root2 = set_find(b); // ��� b�� ��Ʈ�� ã�´�.

    if (root1 != root2) // ���� �ٸ� ������ ���
        parent[root1] = root2; // root1�� root2�� ��ģ��.
}

struct Edge // ������ ��Ÿ���� ����ü
{
    int start, end, weight; // ���� ����, �� ����, ����ġ
};

typedef struct GraphType
{
    int n; // ������ ����
    struct Edge edges[2 * MAX_VERTICES]; // ���� �迭
} GraphType;

// �ּ� �� ����ü
typedef struct MinHeap
{
    int size; // ���� ũ��
    struct Edge* edges[MAX_VERTICES * 2]; // ���� �迭
} MinHeap;

// �� �ʱ�ȭ
void init_heap(MinHeap* heap)
{
    heap->size = 0; // ���� ũ�⸦ 0���� �ʱ�ȭ
}

// ���� ���� �߰�
void insert_heap(MinHeap* heap, struct Edge* edge)
{
    int i = heap->size++; // ���� �߰��� ������ �ε���

    // �� ���� ����
    while (i > 0)
    {
        int parent = (i - 1) / 2; // �θ� �ε���

        if (heap->edges[parent]->weight <= edge->weight)
            break; // �θ��� ����ġ�� �� ũ�ų� ������ ����

        heap->edges[i] = heap->edges[parent]; // �θ� �Ʒ��� ����
        i = parent; // �ε����� �θ�� �̵�
    }
    heap->edges[i] = edge; // ���� ��ġ�� ���ο� ���� �߰�
}

// ������ �ּ� ���� ����
struct Edge* remove_min(MinHeap* heap)
{
    if (heap->size == 0)
        return NULL; // ���� ��������� NULL ��ȯ

    struct Edge* min_edge = heap->edges[0]; // �ּ� ���� ����
    struct Edge* last_edge = heap->edges[--heap->size]; // ������ ���� ���� �� ũ�� ����

    int i = 0;

    // �� ���� ����
    while (1)
    {
        int left = 2 * i + 1; // ���� �ڽ� �ε���
        int right = 2 * i + 2; // ������ �ڽ� �ε���
        int smallest = i; // ���� ���� ������ �ε��� �ʱ�ȭ

        // ���� �ڽİ� ��
        if (left < heap->size && heap->edges[left]->weight < last_edge->weight)
        {
            smallest = left;
        }

        // ������ �ڽİ� ��
        if (right < heap->size && heap->edges[right]->weight < heap->edges[smallest]->weight)
        {
            smallest = right;
        }

        if (smallest == i)
            break; // �� �̻� ��ȯ�� �ʿ䰡 ������ ����

        heap->edges[i] = heap->edges[smallest]; // ��ȯ
        i = smallest; // �ε����� ���� ���� �ڽ����� �̵�
    }
    heap->edges[i] = last_edge; // ������ ���� ��ġ ����

    return min_edge; // �ּ� ���� ��ȯ
}

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
    g->n = 0; // ���� ������ 0���� �ʱ�ȭ

    for (int i = 0; i < 2 * MAX_VERTICES; i++)
    {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF; // ������ �⺻ ����ġ�� ���Ѵ�� �ʱ�ȭ
    }
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w)
{
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++; // ���� ���� ����
}

// qsort()�� ���Ǵ� �Լ� (���� ����)
int compare(const void* a, const void* b)
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight); // ����ġ �������� ��
}

// Kruskal �˰��� (���ĵ� ���� ���)
GraphType* QuickKruskal(GraphType* g)
{
    int edge_accepted = 0; // ���õ� ���� ��

    // ������� ���õ� ������ �� 
    int uset, vset;
    struct Edge e;

    set_init(g->n); // ���� �ʱ�ȭ

    // ������ ����ġ �������� ����
    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    printf("Quick Based Kruskal \n");

    int i = 0;

    // ���� ����
    while (edge_accepted < (g->n - 1) && i < g->n)
    {
        e = g->edges[i]; // ���� ����
        uset = set_find(e.start); // ���� ������ ����
        vset = set_find(e.end); // �� ������ ����

        if (uset != vset) // ���� �ٸ� ������ ���
        {
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++; // ���õ� ���� �� ����
            set_union(uset, vset); // �� ���� ��ġ��
        }
        i++; // ���� �������� �̵�
    }
    return g; // GraphType ������ ��ȯ
}

// �ּ� ���� �̿��� Kruskal �˰���
void MinHeapKuskal(GraphType* g)
{
    int edge_accepted = 0; // ���õ� ���� ��
    set_init(g->n); // ���� �ʱ�ȭ
    MinHeap heap; // �ּ� �� ����
    init_heap(&heap); // �� �ʱ�ȭ

    printf("\nMinHeap Based Kruskal \n");

    // ������ �ּ� ���� ����
    for (int i = 0; i < g->n; i++)
    {
        struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge)); // ���� �޸� �Ҵ�
        *e = g->edges[i]; // ���� ����
        insert_heap(&heap, e); // ���� ���� ����
    }

    // ���� ����
    while (edge_accepted < (g->n - 1) && heap.size > 0)
    {
        struct Edge* e = remove_min(&heap); // �ּ� ���� ����
        int uset = set_find(e->start); // ���� ������ ����
        int vset = set_find(e->end); // �� ������ ����

        // ������ ������ �ٸ� ��� ����
        if (uset != vset)
        {
            printf("Edge (%d, %d) select %d\n", e->start, e->end, e->weight);
            edge_accepted++; // ���õ� ���� �� ����
            set_union(uset, vset); // �� ���� ��ġ��
        }
        free(e);     // �޸� ����
    }
}

// �׷����� �����ϴ� �Լ�
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

    GenerateGraph(g);   // �׷����� ����

    QuickKruskal(g);
    MinHeapKuskal(g);

    free(g);
    return 0;
}
