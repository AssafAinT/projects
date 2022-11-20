#include <iostream> // std::cout
#include <math.h> // sqrt
#include "shapes.hpp"
using namespace std;
namespace ShapeDrawing
{

void PrintCircle(int radius = 6);
void PrintSquare(size_t length = 6);
void PrintRecTangle(size_t length = 6, size_t height = 30);
static void DrawTabs(size_t tabs_amount);
void PrintCircle(int radius)
{
    // dist represents distance to the center
    float dist;

    // for horizontal movement
    for (int i = 0; i <= 2 * radius; i++) 
    {
        // for vertical movement
        for (int j = 0; j <= 2 * radius; j++) {
            dist = sqrt((i - radius) * (i - radius) +
                        (j - radius) * (j - radius));

            // dist should be in the range (radius - 0.5)
            // and (radius + 0.5) to print stars(*)
            if (dist > radius - 0.5 && dist < radius + 0.5)
            cout << "*";
            else
            cout << " ";     
        }
    cout << "\n";
    }
}
void PrintRecTangle(size_t length, size_t height)
{
    for (size_t i = 1; i <= length; ++i)
    {
        for (size_t j = 1; j <= height; ++j)
        {
            if (i == 1 || i == length ||
                j == 1 || j == height)
            {
                cout << "*";            
            }
            else
                cout << " ";
        }
        cout << endl;
    }
 
}
void PrintSquare(size_t length)
{
    PrintRecTangle(length, length);
}
static void DrawTabs(size_t tabs_amount)
{
    for (size_t i = 0; i < tabs_amount; ++i)
    {
        cout << "\t";
    }
}
}
namespace ilrd
{
    IShape& Shape:: Move()
    {
        ++(m_offset);

        return *this;
    }
    size_t Shape:: GetOffset() const
    {
        return m_offset;
    }

    void Line::Draw() const
    {
        ShapeDrawing::DrawTabs(GetOffset());
        cout << "Line ";
        cout << "----------------" << endl;
    }

    void Circle::Draw() const
    {
        ShapeDrawing::DrawTabs(GetOffset());
        cout << "Circle" << endl;
        ShapeDrawing::PrintCircle();
    }

    void Square::Draw() const
    {
        ShapeDrawing::DrawTabs(GetOffset());
        cout << "Square" << endl;
        ShapeDrawing::PrintSquare();
    }

 
    void Rectangle::Draw() const
    {
        ShapeDrawing::DrawTabs(GetOffset());
        cout << "Rectangle" << endl;
        ShapeDrawing::PrintRecTangle();
    }

    void IShape::DrawList(const std::list<IShape*> shapeList)
    {
        for (list<IShape *>::const_iterator iter = shapeList.begin();
                                            iter != shapeList.end();
                                            ++iter)
        {
            (*iter)->Draw();
        }
    }

}