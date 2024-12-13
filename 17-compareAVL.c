#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// AVL Tree�� BST�� ���� ����ü �� �Լ� ����
typedef struct Node
{
    int key;              // ����� Ű ��
    struct Node* left;    // ���� �ڽ� ���
    struct Node* right;   // ������ �ڽ� ���
    int height;           // AVL Ʈ���� ���� ���� ����
} Node;

int compareCount = 0; // �� Ƚ�� ��� ����
int searchCount = 0;  // Ž�� Ƚ�� ��� ����

// ��ƿ��Ƽ �Լ�: �� �� �� �� ū ���� ��ȯ
int maxReturn(int a, int b)
{
    return (a > b) ? a : b;
}

// AVL Ʈ���� ���̸� ��ȯ
int height(Node* n)
{
    return n == NULL ? 0 : n->height;
}

// �� ��带 �����Ͽ� ��ȯ
Node* createNode(int key)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // �� ����� �ʱ� ���̴� 1
    return node;
}

// AVL Ʈ���� ������ ȸ�� ����
Node* rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    // ȸ�� ����
    x->right = y;
    y->left = T2;

    // ���� ����
    y->height = maxReturn(height(y->left), height(y->right)) + 1;
    x->height = maxReturn(height(x->left), height(x->right)) + 1;

    return x; // ���ο� ��Ʈ ��ȯ
}

// AVL Ʈ���� ���� ȸ�� ����
Node* rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    // ȸ�� ����
    y->left = x;
    x->right = T2;

    // ���� ����
    x->height = maxReturn(height(x->left), height(x->right)) + 1;
    y->height = maxReturn(height(y->left), height(y->right)) + 1;

    return y; // ���ο� ��Ʈ ��ȯ
}

// AVL Ʈ���� ���� ���͸� ���
int getBalance(Node* n)
{
    return n == NULL ? 0 : height(n->left) - height(n->right);
}

// AVL Ʈ���� ���ο� Ű�� ����
Node* insertAVL(Node* node, int key)
{
    if (node == NULL)
    {
        return createNode(key); // ���ο� ��� ����
    }

    if (key < node->key)
    {
        node->left = insertAVL(node->left, key); // ���� ����Ʈ���� ����
    }
    else if (key > node->key)
    {
        node->right = insertAVL(node->right, key); // ������ ����Ʈ���� ����
    }
    else
    {
        return node; // �ߺ��� Ű�� �������� ����
    }

    // ��� ���� ����
    node->height = 1 + maxReturn(height(node->left), height(node->right));

    // ���� ���� ���
    int balance = getBalance(node);

    // ������ ������ ��� ȸ�� ����
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

    return node; // ������ �´� ���·� ��ȯ
}

// AVL Ʈ������ ���� ���� ���� ���� ��带 ã��
Node* minValueNode(Node* node)
{
    Node* current = node;

    while (current->left != NULL)
    {
        current = current->left; // ���� ������ �̵�
    }
    return current;
}

// AVL Ʈ������ Ű�� ����
Node* deleteAVL(Node* root, int key)
{
    if (root == NULL)
    {
        return root; // �� Ʈ�� ó��
    }

    // ��������� ���� ����
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
        // ������ ��尡 ���� ����̰ų� �ڽ��� �ϳ��� ��� ó��
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
                *root = *temp; // �ڽ� ��带 ����
            }
            free(temp);
        }
        else
        {
            Node* temp = minValueNode(root->right); // �ļ� ��� ã��
            root->key = temp->key; // �ļ� ����� Ű ����
            root->right = deleteAVL(root->right, temp->key); // �ļ� ��� ����
        }
    }

    if (root == NULL)
    {
        return root; // Ʈ���� ����� ��� ��ȯ
    }

    // ���� ����
    root->height = 1 + maxReturn(height(root->left), height(root->right));

    // ���� Ȯ�� �� ȸ��
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

// BST�� Ű�� ����
Node* insertBST(Node* node, int key)
{
    if (node == NULL)
    {
        return createNode(key); // �� ��� ����
    }

    if (key < node->key)
    {
        node->left = insertBST(node->left, key); // ���� ����Ʈ���� ����
    }
    else if (key > node->key)
    {
        node->right = insertBST(node->right, key); // ������ ����Ʈ���� ����
    }
    return node;
}

// BST���� Ű�� ����
Node* deleteBST(Node* root, int key)
{
    if (root == NULL)
    {
        return root; // �� Ʈ�� ó��
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

// Ʈ������ Ű�� Ž��
int searchTree(Node* root, int key)
{
    if (root == NULL)
    {
        return 0; // Ű�� ã�� ����
    }

    compareCount++; // �� Ƚ�� ����

    if (key == root->key)
    {
        return 1; // Ű�� ã��
    }
    else if (key < root->key)
    {
        return searchTree(root->left, key); // ���� ����Ʈ�� Ž��
    }
    else
    {
        return searchTree(root->right, key); // ������ ����Ʈ�� Ž��
    }
}

// Ʈ�� �޸� ����
void freeTree(Node* root)
{
    if (root != NULL)
    {
        freeTree(root->left); // ���� ����Ʈ�� ����
        freeTree(root->right); // ������ ����Ʈ�� ����
        free(root); // ���� ��� ����
    }
}

// AVL Ʈ�� Batch �۾� ����
void doAVLBatch(Node** root)
{
    for (int i = 0; i < 2000; i++)
    {
        int A = rand() % 3; // �۾� ���� (����, ����, Ž��)
        int B = rand() % 1000; // ���� Ű ����

        if (A == 0)
        {
            *root = insertAVL(*root, B); // ����
        }
        else if (A == 1)
        {
            *root = deleteAVL(*root, B); // ����
        }
        else if (A == 2)
        {
            searchCount++; // Ž�� Ƚ�� ����
            searchTree(*root, B); // Ž��
        }
    }
}

// BST Batch �۾� ����
void doBinaryBatch(Node** root)
{
    for (int i = 0; i < 2000; i++)
    {
        int A = rand() % 3; // �۾� ���� (����, ����, Ž��)
        int B = rand() % 1000; // ���� Ű ����

        if (A == 0)
        {
            *root = insertBST(*root, B); // ����
        }
        else if (A == 1)
        {
            *root = deleteBST(*root, B); // ����
        }
        else if (A == 2)
        {
            searchCount++; // Ž�� Ƚ�� ����
            searchTree(*root, B); // Ž��
        }
    }
}

// ���� �Լ�
int main(int argc, char* argv[])
{
    Node* root = NULL; // Ʈ�� �ʱ�ȭ
    srand(time(NULL)); // ���� �õ� ����
    float allCount = 0.0; // ��� �� Ƚ�� ��� ����

    // AVL Batch ����
    doAVLBatch(&root);
    allCount = (float)compareCount / searchCount; // ��� ���
    printf("average AVL compare count: %.2f\n", allCount);

    // AVL Ʈ�� �޸� ����
    freeTree(root);
    root = NULL; // �ʱ�ȭ
    compareCount = searchCount = 0; // �� �� Ž�� Ƚ�� �ʱ�ȭ

    // BST Batch ����
    doBinaryBatch(&root);
    allCount = (float)compareCount / searchCount; // ��� ���
    printf("average Bin compare count: %.2f\n", allCount);

    // BST �޸� ����
    freeTree(root);
    return 0; // ���α׷� ����
}
