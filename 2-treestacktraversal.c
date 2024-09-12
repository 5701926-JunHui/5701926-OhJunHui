#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

int top = -1;
TreeNode* stack[SIZE];


void push(TreeNode* node) {
    if (top < SIZE - 1) {
        stack[++top] = node;
        printf("push(%2d) ", stack[top]->data);
    }
    else {
        printf("Stack is full\n");
    }
}


TreeNode* pop() {
    if (top >= 0) {
        printf("pop(%2d) ", stack[top]->data);
        return stack[top--];
    }
    else {
        printf("Stack is empty\n");
        return NULL;
    }
}


TreeNode* peek() {
    if (top >= 0) {
        return stack[top];
    }
    return NULL;
}


void PlaceNode(TreeNode* root, int direction, int data) {
    if (direction == 0) {
        root->left = malloc(sizeof(TreeNode));
        root->left->data = data;
        root->left->left = NULL;
        root->left->right = NULL;
    }
    else if (direction == 1) {
        root->right = malloc(sizeof(TreeNode));
        root->right->data = data;
        root->right->left = NULL;
        root->right->right = NULL;
    }
}


void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}


void LinkePreOrder(TreeNode* root) {
    if (root == NULL) return;

    push(root);
    while (top >= 0) {
        TreeNode* del = pop();
        if (del != NULL) {
            printf("visit(%2d)\n", del->data);

            
            if (del->right != NULL) {
                push(del->right);
            }

            
            if (del->left != NULL) {
                push(del->left);
            }
        }
    }
}


void LinkInOrder(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* current = root;
    while (current != NULL || top >= 0) {
        while (current != NULL) {
            push(current);
            current = current->left;
        }
        current = pop();
        printf("visit(%2d)\n", current->data);

        current = current->right;
    }
}


void LinkPostOrder(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* current = root;
    TreeNode* lastVisited = NULL;
    while (top >= 0 || current != NULL) {
        if (current != NULL) {
            push(current);
            current = current->left;
        }
        else {
            TreeNode* peekNode = peek();
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                current = peekNode->right;
            }
            else {
                pop();
                printf("visit(%2d)\n", peekNode->data);
                lastVisited = peekNode;
            }
        }
    }
}


void FreeTree(TreeNode* root) {
    if (root != NULL) {
        FreeTree(root->left);
        FreeTree(root->right);
        free(root);
    }
}


void LinkOrders(TreeNode* root) {
    LinkePreOrder(root);
    printf("\n\n");
    LinkInOrder(root);
    printf("\n\n");
    LinkPostOrder(root);
    printf("\n\n");


}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);
    LinkOrders(root);

    FreeTree(root);

    return 0;
}
