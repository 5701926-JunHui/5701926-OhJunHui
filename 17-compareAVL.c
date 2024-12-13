#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// AVL Tree와 BST를 위한 구조체 및 함수 정의
typedef struct Node
{
    int key;              // 노드의 키 값
    struct Node* left;    // 왼쪽 자식 노드
    struct Node* right;   // 오른쪽 자식 노드
    int height;           // AVL 트리를 위한 높이 정보
} Node;

int compareCount = 0; // 비교 횟수 기록 변수
int searchCount = 0;  // 탐색 횟수 기록 변수

// 유틸리티 함수: 두 값 중 더 큰 값을 반환
int maxReturn(int a, int b)
{
    return (a > b) ? a : b;
}

// AVL 트리의 높이를 반환
int height(Node* n)
{
    return n == NULL ? 0 : n->height;
}

// 새 노드를 생성하여 반환
Node* createNode(int key)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // 새 노드의 초기 높이는 1
    return node;
}

// AVL 트리의 오른쪽 회전 연산
Node* rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    // 회전 수행
    x->right = y;
    y->left = T2;

    // 높이 갱신
    y->height = maxReturn(height(y->left), height(y->right)) + 1;
    x->height = maxReturn(height(x->left), height(x->right)) + 1;

    return x; // 새로운 루트 반환
}

// AVL 트리의 왼쪽 회전 연산
Node* rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    // 회전 수행
    y->left = x;
    x->right = T2;

    // 높이 갱신
    x->height = maxReturn(height(x->left), height(x->right)) + 1;
    y->height = maxReturn(height(y->left), height(y->right)) + 1;

    return y; // 새로운 루트 반환
}

// AVL 트리의 균형 팩터를 계산
int getBalance(Node* n)
{
    return n == NULL ? 0 : height(n->left) - height(n->right);
}

// AVL 트리에 새로운 키를 삽입
Node* insertAVL(Node* node, int key)
{
    if (node == NULL)
    {
        return createNode(key); // 새로운 노드 생성
    }

    if (key < node->key)
    {
        node->left = insertAVL(node->left, key); // 왼쪽 서브트리에 삽입
    }
    else if (key > node->key)
    {
        node->right = insertAVL(node->right, key); // 오른쪽 서브트리에 삽입
    }
    else
    {
        return node; // 중복된 키는 삽입하지 않음
    }

    // 노드 높이 갱신
    node->height = 1 + maxReturn(height(node->left), height(node->right));

    // 균형 팩터 계산
    int balance = getBalance(node);

    // 균형이 깨졌을 경우 회전 수행
    if (balance > 1 && key < node->left->key)
    {
        return rotateRight(node);
    }
    if (balance < -1 && key > node->right->key)
    {
        return rotateLeft(node);
    }
    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; // 균형이 맞는 상태로 반환
}

// AVL 트리에서 가장 작은 값을 가진 노드를 찾음
Node* minValueNode(Node* node)
{
    Node* current = node;

    while (current->left != NULL)
    {
        current = current->left; // 왼쪽 끝까지 이동
    }
    return current;
}

// AVL 트리에서 키를 삭제
Node* deleteAVL(Node* root, int key)
{
    if (root == NULL)
    {
        return root; // 빈 트리 처리
    }

    // 재귀적으로 삭제 수행
    if (key < root->key)
    {
        root->left = deleteAVL(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteAVL(root->right, key);
    }
    else
    {
        // 삭제할 노드가 리프 노드이거나 자식이 하나일 경우 처리
        if ((root->left == NULL) || (root->right == NULL))
        {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp; // 자식 노드를 복사
            }
            free(temp);
        }
        else
        {
            Node* temp = minValueNode(root->right); // 후속 노드 찾기
            root->key = temp->key; // 후속 노드의 키 복사
            root->right = deleteAVL(root->right, temp->key); // 후속 노드 삭제
        }
    }

    if (root == NULL)
    {
        return root; // 트리가 비었을 경우 반환
    }

    // 높이 갱신
    root->height = 1 + maxReturn(height(root->left), height(root->right));

    // 균형 확인 및 회전
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rotateRight(root);
    }
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
    {
        return rotateLeft(root);
    }
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// BST에 키를 삽입
Node* insertBST(Node* node, int key)
{
    if (node == NULL)
    {
        return createNode(key); // 새 노드 생성
    }

    if (key < node->key)
    {
        node->left = insertBST(node->left, key); // 왼쪽 서브트리에 삽입
    }
    else if (key > node->key)
    {
        node->right = insertBST(node->right, key); // 오른쪽 서브트리에 삽입
    }
    return node;
}

// BST에서 키를 삭제
Node* deleteBST(Node* root, int key)
{
    if (root == NULL)
    {
        return root; // 빈 트리 처리
    }

    if (key < root->key)
    {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteBST(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteBST(root->right, temp->key);
    }
    return root;
}

// 트리에서 키를 탐색
int searchTree(Node* root, int key)
{
    if (root == NULL)
    {
        return 0; // 키를 찾지 못함
    }

    compareCount++; // 비교 횟수 증가

    if (key == root->key)
    {
        return 1; // 키를 찾음
    }
    else if (key < root->key)
    {
        return searchTree(root->left, key); // 왼쪽 서브트리 탐색
    }
    else
    {
        return searchTree(root->right, key); // 오른쪽 서브트리 탐색
    }
}

// 트리 메모리 해제
void freeTree(Node* root)
{
    if (root != NULL)
    {
        freeTree(root->left); // 왼쪽 서브트리 해제
        freeTree(root->right); // 오른쪽 서브트리 해제
        free(root); // 현재 노드 해제
    }
}

// AVL 트리 Batch 작업 실행
void doAVLBatch(Node** root)
{
    for (int i = 0; i < 2000; i++)
    {
        int A = rand() % 3; // 작업 선택 (삽입, 삭제, 탐색)
        int B = rand() % 1000; // 랜덤 키 생성

        if (A == 0)
        {
            *root = insertAVL(*root, B); // 삽입
        }
        else if (A == 1)
        {
            *root = deleteAVL(*root, B); // 삭제
        }
        else if (A == 2)
        {
            searchCount++; // 탐색 횟수 증가
            searchTree(*root, B); // 탐색
        }
    }
}

// BST Batch 작업 실행
void doBinaryBatch(Node** root)
{
    for (int i = 0; i < 2000; i++)
    {
        int A = rand() % 3; // 작업 선택 (삽입, 삭제, 탐색)
        int B = rand() % 1000; // 랜덤 키 생성

        if (A == 0)
        {
            *root = insertBST(*root, B); // 삽입
        }
        else if (A == 1)
        {
            *root = deleteBST(*root, B); // 삭제
        }
        else if (A == 2)
        {
            searchCount++; // 탐색 횟수 증가
            searchTree(*root, B); // 탐색
        }
    }
}

// 메인 함수
int main(int argc, char* argv[])
{
    Node* root = NULL; // 트리 초기화
    srand(time(NULL)); // 랜덤 시드 설정
    float allCount = 0.0; // 평균 비교 횟수 계산 변수

    // AVL Batch 실행
    doAVLBatch(&root);
    allCount = (float)compareCount / searchCount; // 평균 계산
    printf("average AVL compare count: %.2f\n", allCount);

    // AVL 트리 메모리 해제
    freeTree(root);
    root = NULL; // 초기화
    compareCount = searchCount = 0; // 비교 및 탐색 횟수 초기화

    // BST Batch 실행
    doBinaryBatch(&root);
    allCount = (float)compareCount / searchCount; // 평균 계산
    printf("average Bin compare count: %.2f\n", allCount);

    // BST 메모리 해제
    freeTree(root);
    return 0; // 프로그램 종료
}
