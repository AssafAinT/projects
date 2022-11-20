#include <ctype.h>
#include <string.h>
#include <stdio.h>
char Lowercase(int c)
{
    return (c | 32);
}
void Swap(char *a, char *b);
void ReverseWord(char *str)
{
    char *head = str;
    char *tail = str;

    while ('\0' != *tail)
    {
        if (*tail == ' ')
        {
            Swap(head, tail - 1);
            head = tail + 1;
            ++tail;
        }
        else
        {
            ++tail;
        }
    }
    head = str;
    Swap(head, tail-1);

}

void Swap(char *a, char *b)
{
    while (a < b)
    {
        
        
        char temp = Lowercase(*a);; 
        *a = Lowercase(*b);
        *b = temp;
        ++a;
        --b;
    }
}

int main(void)
{
    char buf[] = "hello MadaFakaWORD";
    printf("%s\n", buf);
    ReverseWord(buf);
    char buf2[] = "hell oa bambam MadaFakaWORD";
    printf("%s\n", buf2);
    ReverseWord(buf2);
    printf("%s\n", buf);
    printf("%s\n", buf2);
}


