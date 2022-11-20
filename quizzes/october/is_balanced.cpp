/****************************************************
* is_Balanced                                       *
* Assaf Ainhoren                                    *
* Reviewer: Herscho the king                        *
* date: 11.09.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <iostream>

struct node_ty 
{
    int val;
    node_ty *left;
    node_ty *right; 
};
int height(node_ty *node);
int max(int h1, int h2);
bool IsBalanced(node_ty *node);
bool TreeIsBalanced(node_ty *node);
node_ty *CreateNewNode(int data);

int main(void)
{
    node_ty *root = CreateNewNode(1);
    root->left = CreateNewNode(2);
    root->right = CreateNewNode(3);
    root->left->left = CreateNewNode(4);
    root->left->right = CreateNewNode(5);
    root->left->left->left = CreateNewNode(7);

    printf("%d\n",IsBalanced(root));
    

    return (0);
}

bool TreeIsBalanced(node_ty *node)
{
    if (-1 == IsBalanced(node))
    {
        return false;
    }
    return true;
}

int height(node_ty *node)
{
    if (NULL == node)
    {
        return 0;
    }
    return 1 + (max(height(node->right), height(node->left)));
}
int max(int h1, int h2)
{
    return (h1 > h2 ? h1 : h2);
}
bool IsBalanced(node_ty *node)
{
    if (NULL == node)
    {
        return true;
    }
    int left_h = height(node->left);
    int right_h = height(node->right);
    if (abs(left_h - right_h) <= 1 &&
        IsBalanced(node->left) && IsBalanced(node->right))
    {
        return true;
    }
    return false;
}

node_ty *CreateNewNode(int data)
{
    node_ty *node = new node_ty;
    
    node->val = data;
    node->left = NULL;
    node->right = NULL;

    return(node);
}