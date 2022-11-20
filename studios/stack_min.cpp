#include <iostream>
#include <stack>

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


int main(void)
{
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
}