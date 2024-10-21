#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 100


typedef struct GraphList    // 인접 리스트 구조체 정의
{
    int n;                      // 그래프 정점
    struct GraphList* next;     // 다음 노드 포인터
} GraphList;


typedef struct Graph    // 그래프 구조체 정의 (인접 리스트 배열 포함)
{
    GraphList* adjList[MAX_NODES];  // 각 노드의 인접 리스트
} Graph;


void initGraph(Graph* graph)    // 그래프 초기화 함수
{
    for (int i = 0; i < MAX_NODES; i++) 
    {
        graph->adjList[i] = NULL;   // 모든 인접 리스트를 NULL로 초기화
    }
}

// 그래프에 간선 추가 함수
void addEdge(Graph* graph, int node1, int node2) 
{
    // node1 -> node2 방향 간선 추가 (연결 리스트 방식)
    GraphList* newNode = (GraphList*)malloc(sizeof(GraphList));
    newNode->n = node2;
    newNode->next = graph->adjList[node1];
    graph->adjList[node1] = newNode;

    // node2 -> node1 방향 간선 추가 (방향이 없는 그래프이기 때문에)
    newNode = (GraphList*)malloc(sizeof(GraphList));
    newNode->n = node1;
    newNode->next = graph->adjList[node2];
    graph->adjList[node2] = newNode;
}

// 깊이 우선 탐색 함수
void DFS(Graph* graph, int start, int target) 
{
    int stack[MAX_NODES], top = -1;
    int visit[MAX_NODES] = { 0 };  // 방문 배열 (0: 방문안함, 1: 방문함)
    int count = 0;

    stack[++top] = start;  // 시작 노드를 스택에 추가
    printf("탐색 경로: ");

    // 스택이 빌 때까지 반복
    while (top != -1) 
    {
        int node = stack[top--];  // 스택에서 노드를 꺼냄

        // 아직 방문하지 않은 노드만 처리
        if (!visit[node]) 
        {
            visit[node] = 1;  // 노드 방문 처리
            printf("%d ", node);  // 탐색 경로 출력
            count++;

            // 목표 노드에 도달하면 탐색 성공
            if (node == target) 
            {
                printf("\n탐색 성공: %d\n방문한 노드의 수: %d\n", target, count);
                return;
            }

            // 인접 노드들을 스택에 추가 (작은 번호부터 처리되도록 역순으로 추가)
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

            // 작은 번호부터 스택에 추가하기 위해 역순으로 처리 (1 2 3 -> 3 2 1)
            for (int i = adjCount - 1; i >= 0; i--) 
            {
                stack[++top] = adjNodes[i];
            }
        }
        else 
        {
            // 이미 방문한 노드는 백트래킹을 실행할 때만 출력
            printf("%d ", node);
        }
    }
    // 스택이 모두 비워졌을 때 목표 노드를 찾지 못한 경우
    printf("\n탐색 실패: %d\n", target);
}

// 너비 우선 탐색 (BFS) 함수
void BFS(Graph* graph, int start, int target) 
{
    int queue[MAX_NODES], front = -1, rear = -1;
    int visit[MAX_NODES] = { 0 };  // 방문 배열
    int count = 0;

    queue[++rear] = start;  // 시작 노드를 큐에 추가
    visit[start] = 1;       // 시작 노드 방문 처리

    
    while (front != rear)   // 큐가 빌 때까지 반복
    {
        front++;
        int node = queue[front];    // 큐에서 노드를 꺼냄
        printf("%d ", node);        // 탐색 경로 출력
        count++;

        if (node == target) // 목표 노드에 도달하면 탐색 성공
        {
            printf("\n탐색 성공: %d\n방문한 노드의 수: %d\n", target, count);
            return;
        }

        // 인접 노드들을 큐에 추가 (방문하지 않은 노드만)
        for (GraphList* temp = graph->adjList[node]; temp != NULL; temp = temp->next) 
        {
            if (!visit[temp->n]) 
            {
                visit[temp->n] = 1;         // 방문 처리
                queue[++rear] = temp->n;    // 큐에 추가
            }
        }
    }

    // 큐가 모두 비워졌을 때 목표 노드를 찾지 못한 경우
    printf("\n탐색 실패: %d\n", target);
}

int main(void) 
{
    Graph graph;
    initGraph(&graph);  // 그래프 초기화

    // 그래프 간선 추가
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

    // 메뉴 출력
    printf("---------------------\n");
    printf("| 1 : 깊이 우선 탐색 |\n");
    printf("| 2 : 너비 우선 탐색 |\n");
    printf("| 3 : 종료           |\n");
    printf("---------------------\n\n");

    while (1)   // 사용자의 입력에 따라 탐색 실행
    {
        int choice, start, target;

        printf("\n\n메뉴 입력: ");
        scanf_s("%d", &choice);

        if (choice == 3)    // 3을 입력하면
        {
            printf("프로그램 종료\n");    // 프로그램 종료
            break;
        }

        printf("시작 번호와 탐색할 값 입력: ");
        scanf_s("%d %d", &start, &target);

        if (choice == 1)    // 1을 입력하면
        {
            DFS(&graph, start, target);  // 깊이 우선 탐색 실행
        }
        else if (choice == 2)   // 2를 입력하면
        {
            BFS(&graph, start, target);  // 너비 우선 탐색 실행
        }
        else 
        {
            printf("잘못된 메뉴 선택입니다.\n");
        }
    }
    return 0;
}
