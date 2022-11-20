/****************************************/
/*										*/
/*			node1						*/
/*			Name : ofir krisple			*/
/*										*/
/****************************************/

   
#ifndef __ILRD_OL127_128_NODE_H__
#define __ILRD_OL127_128_NODE_H__

/************Structs Init************/

typedef struct node
{
    void *data;
    struct node *next;
}node_ty;

/************function************/

node_ty *CreateNewNode(void *data);
void DestroyNodeList(node_ty *head_node);
node_ty *InsertNode(node_ty *position, void *data);
node_ty *EndNode(node_ty *node);
node_ty *NextNode(node_ty *node);
node_ty *RemoveNode(node_ty *node);
void NodeSetData(node_ty *node, void *data);
void *NodeGetData(const node_ty *node);
size_t ListSize(const node_ty *head_node);
int listIsEmpty(node_ty *head_node);
int listIterIsEqual(const node_ty *node1, const node_ty *node2);
node_ty *Flip(node_ty *head_node);
int HasLoop(const node_ty *head_node);
node_ty *FinedIntersection(node_ty *head1, node_ty *head2);


#endif /* __ILRD_OL127_128_NODE_H__ */











