#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct node 
{
    int data;
    struct node* left;
    struct node* right;
}node_ty;
 
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
node_ty* NewNode(int data)
{
    node_ty* node = (struct node*)malloc(sizeof(struct node));
    if (NULL == node)
    {
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return (node);
}
 
int PrintAncestor(node_ty* head, int key)
{
    if (NULL == head)
    {
        return 0;
    }
    if (key == head->data)
    {
        return 1;
    }
    if (PrintAncestor(head->left, key) || PrintAncestor(head->right, key))
    {
        printf("%d ", head->data);
        return 1;
    }

    return 0;
}
 
int main(void)
{
    node_ty* root = NewNode(1);
    root->left = NewNode(2);
    root->right = NewNode(3);
    root->left->left = NewNode(4);
    root->left->right = NewNode(5);
    root->left->right->right = NewNode(12);
    root->left->left->left = NewNode(7);
 
    printf("\nAncestorPrint of root 7 \n");
    PrintAncestor(root, 12);
    printf("\n");
    return 0;
}