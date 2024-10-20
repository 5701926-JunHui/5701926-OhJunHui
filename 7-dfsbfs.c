#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 11

typedef struct GraphList     // 그래프의 인접 리스트 구조체
{
    int n;                   // 그래프 정점 (노드)
    struct GraphList* next;  // 다음 노드를 가리키는 포인터
} GraphList;


typedef struct Graph    // 그래프 구조체 
{
    GraphList* adjList[MAX_NODES];  // 각 노드의 인접 리스트
} Graph;


void initGraph(Graph* graph)    // 그래프 초기화 함수
{
    for (int i = 0; i < MAX_NODES; i++) // 모든 노드의 인접 리스트를 NULL로 초기화
    {
        graph->adjList[i] = NULL;
    }
}


void addEdge(Graph* graph, int node1, int node2)   // 간선 추가 함수
{
    // node1에서 node2로 가는 간선 추가
    GraphList* newNode = (GraphList*)malloc(sizeof(GraphList));

    newNode->n = node2;
    newNode->next = graph->adjList[node1];
    graph->adjList[node1] = newNode;

    // 무향 그래프이기 때문에 node2에서 node1로 가는 간선도 추가
    newNode = (GraphList*)malloc(sizeof(GraphList));

    newNode->n = node1;
    newNode->next = graph->adjList[node2];
    graph->adjList[node2] = newNode;
}

// 깊이 우선 탐색 함수
void DFS(Graph* graph, int start, int target) 
{
    int stack[MAX_NODES], top = -1;          // 스택을 이용한 DFS
    int visit[MAX_NODES] = { 0 };            // 방문 여부를 기록하는 배열
    int count = 0;                           // 방문한 노드 수 카운트

    stack[++top] = start;                    // 시작 노드를 스택에 추가

    // 스택이 빌 때까지 탐색 반복
    while (top != -1) 
    {
        int node = stack[top--];          // 스택에서 노드 꺼내기
        
        if (!visit[node])
        {
            visit[node] = 1;            // 노드를 방문 처리
            count++;
            printf("%d ", node);

            if (node == target)  // 목표 노드에 도달하면 탐색 종료 
            {         
                printf("\n탐색 성공: %d\n방문한 노드의 수: %d\n", target, count);
                return;
            }

            // 인접 노드들을 스택에 추가
            for (GraphList* temp = graph->adjList[node]; temp != NULL; temp = temp->next)
            {
                if (!visit[temp->n]) 
                {    
                    stack[++top] = temp->n;
                }
            }
        }
    }
    printf("\n탐색 실패: %d\n", target);
}

// 너비 우선 탐색(BFS) 함수
void BFS(Graph* graph, int start, int target)
{
    int queue[MAX_NODES], front = -1, rear = -1;  // 큐를 이용한 BFS
    int visit[MAX_NODES] = { 0 };                 // 방문 여부를 기록하는 배열
    int count = 0;                                // 방문한 노드 수 카운트

    queue[++rear] = start;                        // 시작 노드를 큐에 추가
    visit[start] = 1;                             // 시작 노드 방문 처리

    // 큐가 빌 때까지 탐색 반복
    while (front != rear)
    {
        front++;
        int node = queue[front];                   // 큐에서 노드 꺼내기
        printf("%d ", node);
        count++;                                   // 방문한 노드 수 증가

        if (node == target)  // 목표 노드에 도달하면 탐색 종료
        {
            printf("\n탐색 성공: %d\n방문한 노드의 수: %d\n", target, count);
            return;
        }

        // 인접 노드들을 큐에 추가
        for (GraphList* temp = graph->adjList[node]; temp != NULL; temp = temp->next)
        {
            if (!visit[temp->n])
            {
                visit[temp->n] = 1;             // 노드 방문 처리
                queue[++rear] = temp->n;       // 큐에 추가
            }
        }
    }
    printf("\n탐색 실패: %d\n", target);
}


int main(void) 
{
    Graph graph;                  // 그래프 선언
    initGraph(&graph);            // 그래프 초기화

    // 그래프 간선 추가
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

    // 메뉴 출력 및 입력 처리
    printf("---------------------\n");
    printf("| 1 : 깊이 우선 탐색 |\n");
    printf("| 2 : 너비 우선 탐색 |\n");
    printf("| 3 : 종료           |\n");
    printf("---------------------\n\n");

    while (1)
    {
        int choice, start, target;
        printf("\n\n메뉴 입력: ");
        scanf_s("%d", &choice);  // 탐색 옵션 선택

        if (choice == 3)
        {
            printf("프로그램 종료\n");
            break;              // 메뉴 3 선택 시 프로그램 종료
        }

        // 시작 노드와 목표 노드 입력
        printf("시작 번호와 탐색할 값 입력: ");
        scanf_s("%d %d", &start, &target);

        if (choice == 1) 
        {
            DFS(&graph, start, target);  // 메뉴 1 선택 시 깊이 우선 탐색 수행
        }
        else if (choice == 2)
        {
            BFS(&graph, start, target);  // 메뉴 2 선택 시 너비 우선 탐색 수행
        }
        else 
        {
            printf("잘못된 메뉴 선택입니다.\n");
        }
    }
    return 0;
}
