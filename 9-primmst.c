#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType
{
    int n; // 정점의 수
    int weight[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬
} GraphType;

int selected[MAX_VERTICES]; // 선택된 정점
int distance[MAX_VERTICES]; // 시작 정점으로부터의 거리

// 그래프 초기화 함수
void graph_init(GraphType* g)
{
    g->n = 10; // 그래프의 정점 수 설정
    for (int i = 1; i <= g->n; i++)
    {
        for (int j = 1; j <= g->n; j++)
        {
            // 자기 자신과의 거리는 0, 나머지는 무한대로 초기화
            g->weight[i][j] = (i == j) ? 0 : INF;
        }
    }
}

// 그래프를 생성하는 함수
void GenerateGraph(GraphType* g)
{
    // 간선의 가중치 설정
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

    // 무방향 그래프이기 때문에 대칭 행렬 설정
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

// 최소 거리 정점을 찾는 함수
int get_min_vertex(int n)
{
    int v = -1; // 초기화

    for (int i = 1; i <= n; i++)
    {
        // 선택되지 않았고, 현재의 최소 거리보다 거리가 짧은 정점 찾기
        if (!selected[i] && (v == -1 || distance[i] < distance[v] ||
            (distance[i] == distance[v] && i < v)))
        {
            v = i;
        }
    }
    return v; // 최소 정점 반환
}

// Prim 알고리즘을 사용하여 최소 신장 트리를 찾는 함수
void FindPrimMST(GraphType* g, int s)
{
    int i, u, v;

    // 초기화
    for (u = 1; u <= g->n; u++)
    {
        distance[u] = INF; // 거리 무한대로 초기화
        selected[u] = FALSE; // 선택되지 않음
    }

    distance[s] = 0; // 시작 정점의 거리를 0으로 설정

    printf("Prim MST Algorithm\n");

    // 모든 정점에 대해 반복
    for (i = 1; i <= g->n; i++)
    {
        u = get_min_vertex(g->n); // 최소 정점 선택
        selected[u] = TRUE; // 정점 선택 표시

        if (distance[u] == INF) return; // 연결되지 않은 정점이면 종료

        printf("정점 %d 추가\n", u);

        // 선택된 정점과 연결된 정점의 거리 업데이트
        for (v = 1; v <= g->n; v++)
        {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v])
            {
                distance[v] = g->weight[u][v]; // 거리 업데이트
            }
        }
    }
}

int main(void)
{
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType)); // 그래프 메모리 할당
    graph_init(g); // 그래프 초기화

    GenerateGraph(g); // 그래프 생성

    FindPrimMST(g, 1); // Prim MST 찾기

    free(g); // 메모리 해제
    return 0;
}