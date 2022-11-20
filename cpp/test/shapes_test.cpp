
#include <iostream> //cout
#include "shapes.hpp"

using namespace ilrd;
using namespace std;
int main(void)
{
    Circle c1;
    c1.Draw();
    c1.Move();

    Line l1;
    l1.Draw();
    l1.Move();

    Square s1;
    s1.Draw();
    s1.Move();

    Rectangle r;
    r.Draw();
    r.Move();
    r.Move();
    r.Move();
    

    list<IShape*> shapeList;
    shapeList.push_back(&s1);
    shapeList.push_back(&r);
    shapeList.push_back(&c1);
    shapeList.push_back(&l1);

    IShape::DrawList(shapeList);

    return 0;
}