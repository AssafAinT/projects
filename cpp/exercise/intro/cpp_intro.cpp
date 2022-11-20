#include <iostream>

using namespace std;
/*
enum E {AA, BB, CC, DD};
enum E2 {TT, KK};
enum E e = 2;
enum E2 e2 = AA;
++e;

int i = e;*/
typedef struct List List_ty;
typedef struct Person Person_ty;

struct List
{
    string name; 
    void *next;
};

struct Person
{
    List_ty *personName;
    int age; 
    int id;
};
void *ll_find(List_ty *ll, int key);

void foo(List_ty *ll, int key, int age)
{
    void *vv = ll_find(ll, key);
    // instead of vv 
    Person_ty *p = static_cast<Person_ty *>(vv);
    p->age = age;
}
int main(void)
{
    bool b1 = true;
    bool b2;
    printf("%d\n", b2);
    int i = b1;
    i = 200;
    b2 = i;
    printf("the size of b2 is %d\n", sizeof(b2));
    printf("the size of b1 is %d\n", sizeof(b1));
    printf("%d\n", b2);
    printf("b1 is %d\n", b1);
}

void *ll_find(List_ty *ll, int key)
{
    return NULL;
}

