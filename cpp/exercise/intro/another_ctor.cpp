#include "structs.hpp"

int main(void)
{
    X x1;
    Y y2;
    Y y3(y2);
    Y y4;

    y4 = y2;
    
    return 0;
}