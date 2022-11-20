#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treenode{
    int value;
    struct treenode *left;
    struct treenode *right;
}treenode;

treenode *createnode(int value){
    treenode* result = malloc(sizeof (treenode));
    if (result !=NULL){
        result->left = NULL;
        result->right = NULL;
        result->value = value;
    }
    return result;
}

void PrintTabs(int numtabs){
    for(int i=0; i<numtabs; i++){
        printf("   ");
    }
}
void PrintTree_rec(treenode *root, int level){
    if (root ==NULL){
        PrintTabs(level);
        printf("---<empty tree>\n");
        return;
    }

    PrintTabs(level);
    printf("value = %d\n", root->value);
    PrintTabs(level);
    printf("left\n");

    PrintTree_rec(root->left, level +1);
    PrintTabs(level);
    printf("right\n");

    PrintTree_rec(root->right, level+1);
    PrintTabs(level);
    printf("done\n");
}

void PrintTree(treenode* root){
    PrintTree_rec(root, 0);
}

bool InsertNumber(treenode** rootptr, int value){
    treenode* root = *rootptr;
    if (root ==NULL){
        /*TREE EMPTY*/
        (*rootptr) = createnode(value);
        return true;
    }
    if (value == root->value){
        return false; 
    }
    if (value< root->value){
        return InsertNumber(&(root->left), value);
    }
    else {
        return InsertNumber(&(root->right), value);
    }

}

bool FindNumber(treenode* root, int value){
    if (root ==NULL){
        return false;
    }
    if(root->value==value){
        return true;
    }
    if(value < root->value){
        return FindNumber(root->left, value);
    }
    else {
        return FindNumber(root->right, value);
    }
}

int maxDepth(treenode* root)
{
    if (root == NULL)
        return 0;
    else
    {
        int lDepth = maxDepth(root->left);
        int rDepth = maxDepth(root->right);

        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}

int main() {

    treenode *root = NULL;

    InsertNumber(&root, 15);
    InsertNumber(&root, 11);
    InsertNumber(&root, 19);
    InsertNumber(&root, 6);
    InsertNumber(&root, 16);
    InsertNumber(&root, 24);

    PrintTree(root);

    printf("The tree has the depth of %d\n", maxDepth(root));

    printf("%d (%d)\n", 16, FindNumber(root, 16));
    printf("%d (%d)\n", 15, FindNumber(root, 15));
    printf("%d (%d)\n", 19, FindNumber(root, 19));
    printf("%d (%d)\n", 111, FindNumber(root, 111));

    free(root);


    return 0;
}
