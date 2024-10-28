#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType
{
    int n; // ������ ��
    int weight[MAX_VERTICES][MAX_VERTICES]; // ���� ���
} GraphType;

int selected[MAX_VERTICES]; // ���õ� ����
int distance[MAX_VERTICES]; // ���� �������κ����� �Ÿ�

// �׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g)
{
    g->n = 10; // �׷����� ���� �� ����
    for (int i = 1; i <= g->n; i++)
    {
        for (int j = 1; j <= g->n; j++)
        {
            // �ڱ� �ڽŰ��� �Ÿ��� 0, �������� ���Ѵ�� �ʱ�ȭ
            g->weight[i][j] = (i == j) ? 0 : INF;
        }
    }
}

// �׷����� �����ϴ� �Լ�
void GenerateGraph(GraphType* g)
{
    // ������ ����ġ ����
    g->weight[1][2] = 3; g->weight[1][6] = 11;
    g->weight[1][7] = 12; g->weight[2][3] = 5;
    g->weight[2][5] = 1; g->weight[2][4] = 4;
    g->weight[2][6] = 7; g->weight[2][7] = 8;
    g->weight[3][4] = 2; g->weight[3][7] = 6;
    g->weight[3][8] = 5; g->weight[4][5] = 13;
    g->weight[4][8] = 14; g->weight[4][10] = 16;
    g->weight[5][6] = 9; g->weight[5][9] = 18;
    g->weight[5][10] = 17; g->weight[7][8] = 13;
    g->weight[8][10] = 15; g->weight[9][10] = 10;

    // ������ �׷����̱� ������ ��Ī ��� ����
    for (int i = 1; i <= g->n; i++)
    {
        for (int j = 1; j <= g->n; j++)
        {
            if (g->weight[i][j] != INF && g->weight[i][j] != 0)
            {
                g->weight[j][i] = g->weight[i][j];
            }
        }
    }
}

// �ּ� �Ÿ� ������ ã�� �Լ�
int get_min_vertex(int n)
{
    int v = -1; // �ʱ�ȭ

    for (int i = 1; i <= n; i++)
    {
        // ���õ��� �ʾҰ�, ������ �ּ� �Ÿ����� �Ÿ��� ª�� ���� ã��
        if (!selected[i] && (v == -1 || distance[i] < distance[v] ||
            (distance[i] == distance[v] && i < v)))
        {
            v = i;
        }
    }
    return v; // �ּ� ���� ��ȯ
}

// Prim �˰����� ����Ͽ� �ּ� ���� Ʈ���� ã�� �Լ�
void FindPrimMST(GraphType* g, int s)
{
    int i, u, v;

    // �ʱ�ȭ
    for (u = 1; u <= g->n; u++)
    {
        distance[u] = INF; // �Ÿ� ���Ѵ�� �ʱ�ȭ
        selected[u] = FALSE; // ���õ��� ����
    }

    distance[s] = 0; // ���� ������ �Ÿ��� 0���� ����

    printf("Prim MST Algorithm\n");

    // ��� ������ ���� �ݺ�
    for (i = 1; i <= g->n; i++)
    {
        u = get_min_vertex(g->n); // �ּ� ���� ����
        selected[u] = TRUE; // ���� ���� ǥ��

        if (distance[u] == INF) return; // ������� ���� �����̸� ����

        printf("���� %d �߰�\n", u);

        // ���õ� ������ ����� ������ �Ÿ� ������Ʈ
        for (v = 1; v <= g->n; v++)
        {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v])
            {
                distance[v] = g->weight[u][v]; // �Ÿ� ������Ʈ
            }
        }
    }
}

int main(void)
{
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType)); // �׷��� �޸� �Ҵ�
    graph_init(g); // �׷��� �ʱ�ȭ

    GenerateGraph(g); // �׷��� ����

    FindPrimMST(g, 1); // Prim MST ã��

    free(g); // �޸� ����
    return 0;
}