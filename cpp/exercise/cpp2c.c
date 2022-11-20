#include <stdio.h>
#include <stdlib.h> /*malloc, free*/
struct Point     
{     
//public:         
    //Point(int x,int y);     
//private:         
    int m_x;         
    int m_y;     
};
    
static void PointInit(struct Point *pt)     
{          
    pt->m_x = 0; 
    pt->m_y = 0; 
}          

struct A     
{         

}; 

struct B     
{     
//private:         
    int x;         
    int y;         
    struct Point p;         
}; 

static void Bla(void)
{
    printf("Bla\n");
}

void BCtor(struct B *Bpt)     
{    
    Bpt->x = 0;
    Bpt->y = 0;      
    PointInit(&Bpt->p); 
}        
static struct B Cctor(struct B *pt1)     
{          
    struct B pt2;
    pt2.x = pt1->x; 
    pt2.y = pt1->y;
    pt2.p = pt1->p;

    return pt2;
}


static void Dtor(void)     
{          
    printf("dtor");  
}
static void BDtor(struct B *pt1)     
{          
    (void)pt1;
    printf("BDtor\n");  
}

void SetX(struct B *pt1, int inX)
{
    pt1->x = inX;
}

void SetY(struct B *pt1, int inY)
{
    pt1->y = inY;
}

struct B* CreateB(void)
{
    struct B *b = malloc(sizeof(struct B));
    if (NULL == b)
    {
        return NULL;
    }
    BCtor(b);

    return b;
}
void DeleteB(struct B *b)
{
    free(b);
    b = NULL;
}

void DFoo(void)
{
    printf("Dfoo\n");
}
void Foo(void) 
{     
    struct B array1[100];
    for (size_t i = 0; i < 100; ++i)
    {
        BCtor(&array1[i]);
    }     
        // ...      
    struct B* array2 = (struct B*)malloc(sizeof(struct B)* 100);
    for (size_t i = 0; i < 100; ++i)
    {
        BCtor(&array2[i]);
    }
    for (size_t i = 0; i < 100; ++i)
    {
        BDtor(&array1[i]);
    }
    DeleteB(array2);
    //INSTEAD OF DELETE
} 
//vptr
struct VtblBase
{
    void(* base_dtor_ptr)();
    void(* base_foo_ptr)();

};
struct VtblDerived
{
    struct VtblBase vtbl_b;
};
struct Base
{
    void *vptr;
    int x;
    int y;
};
struct Derived
{
    struct Base base;
    int z;
};


void BaseDtor(struct Base *pt1)     
{          
    (void)pt1;
    printf("BaseDtor\n");  
}
void DerivedDtor(struct Derived *pt1)     
{          
    (void)pt1;
    printf("DerivedDtor\n");  
}
struct VtblBase vtbl_b = {BaseDtor, Foo};
struct VtblDerived vtbl_d = {{DerivedDtor, DFoo}};
//vptr init
//ex12
struct Base BaseCtor(struct Base* base, int x, int y)
{
    //replace mill

    struct Base this = {&vtbl_b, x, y};

    return this;
    
}
struct Derived DerivedCtor(struct Derived* derived, int x, int y, int z)
{
    //replace mill
    struct Derived this = {BaseCtor(&derived->base, x, y),z};
    derived->base.vptr = &vtbl_d;

    return this;
    
}
int main(void)     
{        
    struct A a;         
    struct B b; 
    BCtor(&b);

    struct B b2 = Cctor(&b);         
    printf("%d\n", b2.x);
    
    b2 = b;             
    SetX(&b,1256);
    SetY(&b,125116);
    Bla();
    printf("%d\n%d\n", b.x, b.y);
    

    struct B* p = CreateB();
    SetX(p,1256);
    SetY(p,125116);
    printf("%d\n%d\n", p->x, p->y);
    DeleteB(p);
    Foo();
    Bla();
    

    struct Base base = BaseCtor(&base, 14, 5);
    printf("Base.x: %d\n", base.x);
    
    struct Derived der = DerivedCtor(&der, 33, 5, 121);
    
    printf("%ld\n", sizeof(der));
    printf("der.base.x: %d\n", der.base.x);
    printf("der.base.y: %d\n", der.base.y);
    printf("der.z: %d\n", der.z);
    

    //ex 15
    struct Base* pBase = (struct Base *)malloc(sizeof(struct Derived));
    DerivedCtor((struct Derived *)pBase, 5, 6 ,7); 
    ((struct VtblBase *)(pBase->vptr))->base_foo_ptr();


    return 0;
    
    DerivedDtor(&der);
    BaseDtor(&base);
    BDtor(p);   
    Dtor();
    
    
}    

// int main(void)
// {
// struct A
// {
//     char reserved;
// };

// struct B
// {
//     int x;
//     int y;
// };  
//     printf("%d\n",sizeof(struct A));
//     printf("%d\n",sizeof(struct B));


//     return 0;
// }