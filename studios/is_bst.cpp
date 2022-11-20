#include <iostream>
#include <bits/stdc++.h>
using namespace std;
 
/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct node_ty 
{
    int data;
    struct node_ty* left;
    struct node_ty* right;
};
 
/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
node_ty* newNode(int data)
{
    node_ty* node
        = (node_ty*)malloc(sizeof(node_ty));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return (node);
}

int MaxValue(node_ty* node)
{
    if (NULL == node)
    {
        return INT16_MIN;
    }

    int value = node->data;
    int LeftMax = MaxValue(node->left);
    int RightMax = MaxValue(node->right);

    return std::max(value ,std::max(LeftMax, RightMax));
}
 
int MinValue(node_ty* node)
{
    if (NULL == node)
    {
        return __INT16_MAX__;
    }

    int value = node->data;
    int LeftMin = MinValue(node->left);
    int RightMin = MinValue(node->right);

    return std::min(value ,std::min(LeftMin, RightMin));
}

bool IsBst(node_ty *node) 
{
    if (NULL == node)
    {
        return true;
    }

    if (NULL != node->left &&
        MaxValue(node->left) > node->data)
    {
        return false;
    }

    if (NULL != node->right &&
        MinValue(node->right) < node->data)
    {
        return false;
    }

    if (!IsBst(node->left) || !IsBst(node->right))
    {
        return false;
    }

    return true;

}
int main(void)
{
    node_ty* root = newNode(4);
    root->left = newNode(2);
    root->right = newNode(5);
    root->right->left = newNode(7);
    root->left->left = newNode(1);
    root->left->right = newNode(3);
 
    // Function call
    if (IsBst(root))
        printf("Is BST");
    else
        printf("Not a BST");
 
    return 0;
}