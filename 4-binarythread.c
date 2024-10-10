#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode 
{
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct ThreadNode
{
    int data;
    struct ThreadNode* left, * right;
    int is_Thread;
} ThreadNode;


TreeNode* new_Treenode(int data)
{
    TreeNode* temp = NULL;

    temp = malloc(sizeof(TreeNode));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

TreeNode* insert_NewTreenode(TreeNode* root_node, int data)
{
    if (root_node == NULL)
    {
        return new_Treenode(data);
    }

    if (root_node->data == data)
    {
        return root_node;
    }

    else if (root_node->data > data)
    {
        root_node->left = insert_NewTreenode(root_node->left, data);
    }

    else if (root_node->data < data)
    {
        root_node->right = insert_NewTreenode(root_node->right, data);
    }

    return root_node;
}

TreeNode* GenerateBinaryTree(int inputData[])
{
    TreeNode* root_node = NULL;

    for (int i = 0; i < 15; i++)
    {
        root_node = insert_NewTreenode(root_node, inputData[i]);
    }

    return root_node;
}

void BinaryTreeInOrder(TreeNode* root)
{
    if (root != NULL)
    {
        BinaryTreeInOrder(root->left);
        printf("%2d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}


ThreadNode* new_Threadnode(int ThreadData)
{
    ThreadNode* temp = (ThreadNode*)malloc(sizeof(ThreadNode));

    temp->data = ThreadData;
    temp->left = NULL;
    temp->right = NULL;
    temp->is_Thread = 0;

    return temp;
}

ThreadNode* leftmost(ThreadNode* node)
{
    if (node == NULL) return NULL;

    while (node->left != NULL) 
    {
        node = node->left;
    }

    return node;
}

ThreadNode* insert_NewThreadnode(ThreadNode* root, int data)
{
    ThreadNode* newNode = new_Threadnode(data);
    if (root == NULL) return newNode;

    ThreadNode* current = root;
    ThreadNode* parent = NULL;

    
    while (current != NULL) 
    {
        parent = current;

        if (data < current->data) 
        {
            if (current->left == NULL) break;  
            current = current->left;
        }

        else 
        {
            if (current->right == NULL || current->is_Thread) break;
            current = current->right;
        }
    }

    
    if (data < parent->data) 
    {
        parent->left = newNode;
        newNode->right = parent;
        newNode->is_Thread = 1;
    }

    else 
    {
        if (parent->is_Thread) 
        {
            newNode->right = parent->right; 
            newNode->is_Thread = 1;
        }
        parent->right = newNode;
        parent->is_Thread = 0;
    }

    return root;
}


ThreadNode* GenerateThreadTree(int inputData[])
{
    ThreadNode* troot = NULL;

    for (int i = 0; i < 15; i++) 
    {
        troot = insert_NewThreadnode(troot, inputData[i]);
    }

    return troot;
}


void ThreadTreeInOrder(ThreadNode* root) 
{
    ThreadNode* current = leftmost(root);  

    while (current != NULL) 
    {
        printf("%2d ", current->data); 

       
        if (current->is_Thread) 
        {
            current = current->right;
        }

        else 
        {
            current = leftmost(current->right);
        }
    }
}

int main(void) 
{
    int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,11 };

    
    TreeNode* root = GenerateBinaryTree(inputData);

    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

   
    ThreadNode* troot = GenerateThreadTree(inputData);

    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free(root);
    free(troot);

    return 0;
}

