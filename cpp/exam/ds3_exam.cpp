#include <iostream>
#include <unordered_set>
#include <cstring>
#include "ds3_exam.hpp"
using namespace std;
//ex2
TwoSum SumOfTwo(int *arr, size_t arr_size, int sum_to_find)
{
    bool found = false;
    TwoSum ret = {0, 0};
    unordered_set<int> my_set;

    for (size_t i = 0; i < arr_size; ++i)
    {
        my_set.insert(arr[i]);    
    }
    for (size_t i = 0; i < arr_size && !found; ++i)
    {
        if (my_set.find(sum_to_find - arr[i]) != my_set.end())
        {
            found = true;
            ret.first = arr[i];
            ret.second = sum_to_find - arr[i];
        }
    }

    return ret;

}
//ex3 
bool FindCharNoCondition(char *arr, size_t arr_size, char character)
{
    size_t Lut[256] = {0};
    
    for (size_t i = 0; i < arr_size; ++i)
    {
        ++Lut[arr[i]];
    }

    return (Lut[character] >= 1);

}

//ex4
void Swap(int *arr , size_t start, size_t end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        ++start;
        --end;
    }
}
// swapping in juggling like and not n times rotating
void ArrayRotation(int *arr , size_t arr_size, size_t d)
{
    d %= arr_size;
    Swap(arr, 0, arr_size-1);
    Swap(arr, 0, d-1);
    Swap(arr, d, arr_size -1);
}
//ex4


//ex7 

int IsValidParantheses(char *str)
{
    char LUT[256] = {'\0'};
    int is_valid = 2;
    
    std::stack<char> ch_stack;
    
    InitParenthesesLut(LUT);

    for ( ; '\0' != *str && 2 == is_valid; ++str)
    {
        if(*str == '[' || *str == '{' || *str == '(')
        {
            ch_stack.push(*str);
        }
        else if(*str == ']' || *str == '}' || *str == ')')
        {
            if(ch_stack.empty() || ch_stack.top() != LUT[*str])
            {
                is_valid = 0;
            }
            else
            {
                ch_stack.pop();
            }
        }
    }
    
    if(2 == is_valid)
    {
        is_valid = ch_stack.empty();
    }
    return is_valid;
}


//ex8 Recursion

int Multiply(int x, int y)
{
    if (x < y)
    {
        return Multiply(y, x);
    } 
    else if (0 != y)
    {
        return (x + Multiply(x, y-1));
    }
    else
    {
        return 0;
    }
}

int Division(int x, int y)
{
    if (x < y)
    {
        return 0;
    }
    return (1 + Division(x - y, y));
}
int AddOneBitwise(int num, size_t count)
{
    
    if (0 == (num & 1))
    {
        num ^= 1;
        return (num << count);
    }
    return AddOneBitwise(num >> 1, count +1);
    
}
int AddOne(int num)
{
    size_t count = 0;
    if (num < 0)
    {
        return (((-1 * num) -1) * -1);
        
    }
    return (AddOneBitwise(num, count));
}

//ex9 
Node *QsortList(Node *list, int pivot)
{
    Node *tail = list;
 
    
    Node *curr = list;
    while (curr != NULL)
    {
        Node *next = curr->next;
        if (curr->data < pivot)
        {
            curr->next = list;
            list = curr;
        }
 
        else 
        {
            tail->next = curr;
            tail = curr;
        }
        curr = next;
    }
    tail->next = NULL;
 
    
    return list;
}

//ex13

int main(void)
{
    //ex1
    Array arr;
    arr.Setval(0, 20);
    cout << arr.Getval(0) << endl;
    arr.Setval(1, 202);
    cout << arr.Getval(1) << endl;
    arr.Setval(1, 205);
    cout << arr.Getval(1) << endl;
    arr.Setall(99);
    cout << arr.Getval(1) << endl;
    //ex1

    //ex2
    int arr2[5] = {1, 2, 17, 33, 55};
    //TwoSum ts1 = SumOfTwo(arr2, 5, 12); // will give 0
    TwoSum ts1 = SumOfTwo(arr2, 5, 72);
    cout << ts1.first << " " << ts1.second << endl;
    //ex2

    char arr_ch[] = "ABCDEFG";
    cout << FindCharNoCondition(arr_ch, 6, 'A') << endl;

    //ex4 
    int arr_ex4[5] = {10, 12, 33, 55, 89};

    for (size_t i = 0; i < 5; ++i)
    {
        cout << arr_ex4[i] << " ";
    }
    cout << endl;

    ArrayRotation(arr_ex4, 5, 2);
    for (size_t i = 0; i < 5; ++i)
    {
        cout << arr_ex4[i] << " ";
    }
    cout << endl;

    //ex5
    bool map[ROWS][COLS] = {{1, 1, 0, 0, 0},
                            {0, 1, 0, 0, 1},
                            {1, 0, 1, 1, 1},
                            {0, 0, 1, 0, 0},
                            {1, 0, 1, 0, 1}};

    std::cout << "Testing Island and num of islands is :" <<
    Island(map) << std::endl;

    bool map2[ROWS][COLS] = {{1, 1, 1, 0, 0},
                            {0, 1, 0, 0, 1},
                            {1, 0, 1, 1, 1},
                            {1, 0, 1, 0, 0},
                            {1, 0, 1, 0, 1}};
    std::cout << "Testing Island and num of islands is :" <<
    Island(map2) << std::endl;

    //ex6
    MinStack s1;

    s1.push(12);
    s1.push(-12);
    s1.push(0);
    s1.push(-65);
    s1.push(4);

    cout << s1.top() << endl;

    s1.min();
    s1.pop();

    cout << s1.top() << endl;
    s1.pop();
    cout << s1.top() << endl;
    s1.min();



    //ex7
    //TODO:: to complete


    //ex8 
    cout << Multiply(6, 10) << endl;
    cout << Division(12, 6) << endl;
    cout << AddOne(-267) << endl;

    //ex 9 
    Node* head = newNode(3);
    head->next = newNode(5);
    head->next->next = newNode(8);
    head->next->next->next = newNode(2);
    head->next->next->next->next = newNode(10);
    head->next->next->next->next->next = newNode(2);
    head->next->next->next->next->next->next = newNode(1);
 
    
    head = QsortList(head, 7);
    printList(head);
   
    //ex 10
    std::unordered_set<std::string> dict;
    dict.insert("live");
    dict.insert("vile");
    dict.insert("veil");
    dict.insert("evil");
    
    char word[5] = "live";
    StringPermutation(dict, word);

    TreeNode *head_tree = NULL;
    head_tree = NodeInsertRec(head_tree, 12);
    head_tree->right = NodeInsertRec(head_tree, 22);


    TreeNode *head_tree1 = NULL;
    head_tree1 = InsertNode(head_tree1, 12);
    head_tree1->right = InsertNode(head_tree1, 22);

    /*
    IS VALID PARANTHESES TEST*/
    char parentheses1[] = "invalid( patanh)[Asa))]these";
    char parentheses2[] = "Valid[Pa](rant{}{})eses()";

    assert(1 == IsValidParantheses(parentheses2));
    assert(0 == IsValidParantheses(parentheses1));


    return 0;

}