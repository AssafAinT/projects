#ifndef __ILRD_RL127_128_BST_H__
#define __ILRD_RL127_128_BST_H__
struct X 
{
    explicit X(); // Initializion function without arameters is named default constructor 
    explicit X(int a_, int b_ = 8); //Regular (non default) Ctor.
    ~X(); // Destructor
    X(const X& other_); //copy initialization function is called copy constructor or Cctor
    X& operator=(const X& other_); //assignment operator

    int m_a;
    const int m_b;
};

//Exercise 22
struct Y
{
    explicit Y();
    Y& operator=(const Y& other_);
    //Y(const Y& other_);
    X m_x;
    int m_i;
};

#endif