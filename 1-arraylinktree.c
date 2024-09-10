#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 15

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

void GenerateArrayTree(int* tree) {

    int list[15] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }

    for (int i = 0; i < 15; i++) {
        printf("%2d ", tree[i]);
    }
    printf("\n");
}


void ArrayPreOrder(int* tree, int index) {
    if (index < MAX_SIZE && tree[index] != -1) {
        printf("[%2d] ", tree[index]);
        ArrayPreOrder(tree, 2 * index + 1);
        ArrayPreOrder(tree, 2 * index + 2);
    }
}

void ArrayInorder(int* tree, int index) {
    if (index < MAX_SIZE && tree[index] != -1) {
        ArrayInorder(tree, 2 * index + 1);
        printf("[%2d] ", tree[index]);
        ArrayInorder(tree, 2 * index + 2);
    }
}

void ArrayPostOrder(int* tree, int index) {
    if (index < MAX_SIZE && tree[index] != -1) {
        ArrayPostOrder(tree, 2 * index + 1);
        ArrayPostOrder(tree, 2 * index + 2);
        printf("[%2d] ", tree[index]);
    }
}

void ArrayOrders(int* tree) {
    printf("Preorder: ");
    ArrayPreOrder(tree, 0);
    printf("\n");

    printf("Inorder: ");
    ArrayInorder(tree, 0);
    printf("\n");

    printf("Postorder: ");
    ArrayPostOrder(tree, 0);
    printf("\n");
}

void PlaceNode(TreeNode** node, int data) {
    if (*node == NULL) {
        *node = (TreeNode*)malloc(sizeof(TreeNode));
        (*node)->data = data;
        (*node)->left = NULL;
        (*node)->right = NULL;
    }
    else {
        if (data < (*node)->data) {
            PlaceNode(&((*node)->left), data);
        }
        else {
            PlaceNode(&((*node)->right), data);
        }
    }
}

TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void GenerateLinkTree(TreeNode** root) {
    TreeNode* nodes[15];
    int list[15] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    for (int i = 0; i < 15; i++) {
        nodes[i] = CreateNode(list[i]);
    }

    for (int i = 0; i < 15; i++) {
        if (2 * i + 1 < 15) {
            nodes[i]->left = nodes[2 * i + 1];
        }
        if (2 * i + 2 < 15) {
            nodes[i]->right = nodes[2 * i + 2];
        }
    }

    *root = nodes[0];
}

void LinkPreOrder(TreeNode* root) {
    if (root != NULL) {
        printf("%2d ", root->data);
        LinkPreOrder(root->left);
        LinkPreOrder(root->right);
    }
}

void LinkInOrder(TreeNode* root) {
    if (root != NULL) {
        LinkInOrder(root->left);
        printf("%2d ", root->data);
        LinkInOrder(root->right);
    }
}

void LinkPostOrder(TreeNode* root) {
    if (root != NULL) {
        LinkPostOrder(root->left);
        LinkPostOrder(root->right);
        printf("%2d ", root->data);
    }
}

void LinkOrders(TreeNode* root) {
    printf("Preorder: ");
    LinkPreOrder(root);
    printf("\n");

    printf("Inorder: ");
    LinkInOrder(root);
    printf("\n");

    printf("Postorder: ");
    LinkPostOrder(root);
    printf("\n");
}

void FreeTree(TreeNode* root) {
    if (root != NULL) {
        FreeTree(root->left);
        FreeTree(root->right);
        free(root);
    }
}

int main(void) {
    int arr[MAX_SIZE];
    TreeNode* root = NULL;

    GenerateArrayTree(arr);
    ArrayOrders(arr);

    GenerateLinkTree(&root);
    LinkOrders(root);

    FreeTree(root);
    return 0;
}