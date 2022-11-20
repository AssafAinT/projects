/****************************************************
* tree                                              *
* Assaf Ainhoren                                    *
* date: 11.09.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#ifndef ILRD_RD127_TREE_HPP
#define ILRD_RD127_TREE_HPP
#include <iostream>
#include <list>
namespace ilrd
{
class IFile
{
    public:
    virtual ~IFile() {};
    virtual void Print() =0;
};
class Tree
{
    public:
    Tree(const char *path = "");
    virtual ~Tree();
    void Print();
    private:
    IFile *root;
};
}
#endif /* ILRD_RD127_TREE_HPP */