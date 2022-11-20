#include <iostream>
void foo(int a, int i = 3, float f = 4);
int main(void)
{
    std::cout << "This program is all about new and delete" << std::endl;
    float *f = new float(12.6);
    std::cout << "as you can see f is equal to " << f << std::endl;
    std::cout << "as you can see f is equal to " << *f << std::endl;
    delete f;
    f = NULL;
    std::cout << "as you can see f is equal to " << f << std::endl;
    f = new float[15];
    f[1] = 14.7;
    std::cout << "as you can see f is equal to " << f << std::endl;
    std::cout << "as you can see f is equal to " << f[1] << std::endl;
    delete[] f;
    
    /*int *ptr = (int *)malloc(1000 * sizeof(int));
    delete[] ptr;

    int *ptr2 = new int[1000];
    free(ptr2);*/
    /*int i;
    std::cout << "ghdfhjdfjklds" << std::endl;
    std::cin >> i;
    std::cerr << "ghdfhjdfjklds" << i;*/
    foo(8);

}

void foo(int a , int i, float f)
{
    std::cout << " " << a * i *f << std::endl;
    /*std::cout << "ghdfhjdfjklds" << int * i * float<< std::endl;*/
}