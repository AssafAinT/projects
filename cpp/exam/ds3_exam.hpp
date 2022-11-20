#ifndef __ILRD_OL127_128_EXAM_HPP__
#define __ILRD_OL127_128_EXAM_HPP__

#include <iostream>
#include <map>
#include <stack>
#include <cassert>
#include <queue>
struct TwoSum
{
    int first, second;
};

struct Node
{
    int data;
    Node *next;
};
Node *newNode(int data)
{
    Node* new_node = new Node;
    new_node->data  = data;
    new_node->next = NULL;
    return new_node;
}
void printList(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        std::cout << temp->data<< " ";
        temp = temp->next;
    }
    std::cout<< '\n';
}
class Array
{
    public:
        Array();
        void Setval(int ind, int val);
        void Setall(int val);
        int Getval(int ind);
    private:
        std::map<int ,int> m_arr;
        bool to_set_all;
        int set_value;
};
Array::Array(): to_set_all(false), set_value(0) {}

void Array::Setval(int ind, int val)
{
    if (to_set_all)
    {
        to_set_all = false;
    }
    m_arr[ind] = val;
}
void Array::Setall(int val)
{
    to_set_all = true;
    set_value = val;
}

int Array::Getval(int ind)
{
    if (to_set_all)
    {
        return set_value;
    }

    if (m_arr.find(ind) != m_arr.end())
    {
        return m_arr[ind];
    }

    return INT16_MIN;
}
//ex4
#define ROWS 5
#define COLS 5
void DFSIslands(bool mat[ROWS][COLS], long c_row, long c_col)
{
    if (0 > c_row || 0 > c_col || ROWS - 1 < c_row || COLS - 1 < c_col||
       mat[c_row][c_col] != 1 )
    {
        return ; 
    }

    if (mat[c_row][c_col] == 1)
    {
        mat[c_row][c_col] = 0;
        DFSIslands(mat, c_row-1, c_col);
        DFSIslands(mat, c_row+1, c_col);        
        DFSIslands(mat, c_row, c_col + 1);        
        DFSIslands(mat, c_row, c_col - 1);        
        DFSIslands(mat, c_row + 1, c_col + 1);        
        DFSIslands(mat, c_row - 1, c_col - 1);                
        DFSIslands(mat, c_row + 1, c_col - 1);        
        DFSIslands(mat, c_row - 1, c_col + 1);        
        
    }

}

size_t Island(bool mat[ROWS][COLS])
{
    size_t count = 0;
    for (long i = 0; i < ROWS; ++i)
    {
        for (long j = 0; j < COLS; ++j)
        {
            if (mat[i][j] == 1)
            {
                ++count;
                DFSIslands(mat, i, j);
            }
        }
    }
    return count;
}
using namespace std;

class MinStack
{
    public:

    int top(void);
    void push(int x);
    void pop(void);
    void min(void);

    private:
    int m_min;
    stack<int> m_stack;

};

int MinStack::top(void)
{

    if (m_stack.empty())
    {
        cout << "Empty MinStack " << endl;
        return INT16_MAX;
    }
    int top = m_stack.top();

    return (top < m_min) ? m_min : top;
}

void MinStack::push(int x)
{
    if (m_stack.empty())
    {
        cout << "Empty MinStack " << endl;
        m_stack.push(x);
        m_min = x;
        return ;
    }
    else if (x < m_min)
    {
        m_stack.push(2*x - m_min);
        m_min = x;
    }
    else
    {
        m_stack.push(x);
    }
}

void MinStack::pop(void)
{
    if (m_stack.empty())
    {
        cout << "Empty MinStack " << endl;
        return ;
    }
    int top = m_stack.top();
    m_stack.pop();
    if (top < m_min)
    {
        m_min = 2 *m_min - top;
    }
    
}

void MinStack::min(void)
{
    if (m_stack.empty())
    {
        cout << "Empty MinStack " << endl;
        return ;
    }
    else
    {
        cout << "MIn elem is " << m_min << endl;
    }
}
class Anagram
{
    public:
        void ShowAnagram();
    private:
    std::stack<std::string> m_stack;
};

void CharSwap(char *c1, char *c2);
void StringPermutation(std::unordered_set<std::string> &dict, char *string);
void RecStringPermutation(std::unordered_set<std::string> &dict, char *string, size_t start, size_t end);


void StringPermutation(std::unordered_set<std::string> &dict, char *string)
{
    size_t len = 0;
    assert(NULL != string);
    
    len = strlen(string);

    RecStringPermutation(dict, string, 0, len -1 );
}

void RecStringPermutation(std::unordered_set<std::string> &dict, char *string, size_t start, size_t end)
{
    size_t i = 0;

    if (end == start)
    {

        if (dict.find(string) != dict.end())
        {
            std::cout<< string << std::endl;
        }
        return;
    }
    for (i = start ; i <= end; ++i)
    {
        CharSwap(string + start, string + i);
        RecStringPermutation(dict, string, start + 1, end);
        CharSwap(string + start, string + i);
    }
}
void CharSwap(char *c1, char *c2)
{
    char temp = '\0';
    temp = *c1;
	*c1 = *c2;
	*c2 = temp;
	
}


struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *NodeInsertRec(TreeNode *root, int val)
{
    if (NULL == root)
    {
        root = new TreeNode;
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    if (val < root->val)
    {
        root->left = NodeInsertRec(root->left, val);
    }
    else
    {
        root->right = NodeInsertRec(root->right, val);
    }

    return root;
}
TreeNode* CreateNode(int data)
{
    TreeNode* newNode = new TreeNode();
    
    newNode->val = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* InsertNode(TreeNode* root, int data)
{
    // If the tree is empty, assign new node address to root
    if (root == NULL)
    {
        root = new TreeNode();
        root->left = NULL;
        root->right = NULL;
        return root;
    }
 
   
    std::queue<TreeNode*> q;
    q.push(root);
 
    while (!q.empty()) 
    {
        TreeNode* temp = q.front();
        q.pop();
 
        if (temp->left != NULL)
            q.push(temp->left);
        else {
            temp->left = CreateNode(data);

            return root;
        }
 
        if (temp->right != NULL)
            q.push(temp->right);
        else {
            temp->right = CreateNode(data);
            return root;
        }
    }
}


static void InitParenthesesLut(char *LUT)
{
    LUT['}'] = '{';
    LUT[']'] = '[';
    LUT[')'] = '(';
}

#endif
