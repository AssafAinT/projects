/* max.h */
#define concat(a, b) a##b
#define TEMPLATE_MAX(T)\
T Max_##T(T a,T b)\     
{\   
    return a > b ? a : b;\   
}

/* main.c */
int i = 0;
TEMPLATE_MAX(int)
TEMPLATE_MAX(double)
TEMPLATE_MAX(size_t)

int main()
{
    int a = Max_int(5,6);
    float b = Max_double(5.5,6.5);
    int xy = 30;
    printf("%d", concat(x, y));
    
    return 0;
}