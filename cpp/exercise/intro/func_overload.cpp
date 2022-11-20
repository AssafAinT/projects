#include <iostream>
#include <dlfcn.h> // dlsym, dlerror , dlopen
using namespace std;

void Foo()
{
    cout << "Testing foo" << endl;
}
void Foo(int i)
{
    cout << "" << i << endl;
};
void Foo(char c)
{
    cout << "Testing foo char " << c << endl;
};
int main(void)
{
    Foo();
    //cout << " The address of foo is " << &Foo << endl;
    Foo(12);
    Foo('A');
    
    int *i = new int[1]{1};
    Foo(i[0]);
    Foo(i);
    delete[] i;
    i = NULL;
    Foo(nullptr);

    unsigned char *p = new unsigned char[1];
    Foo(p);
    void *handle = dlopen("/home/assaf/git/cpp/exercise/libsome_funcs.so", RTLD_LAZY);

    if (!handle)
    {
        cout << "Cannot open library: " << dlerror() << '\n';
        return 22;
    }

    typedef int (*Bla_ty)(int, int, int);
    typedef char (*Upper_ty)(char);

    Bla_ty bla = (Bla_ty)dlsym(handle, "Bla");
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        cout << "cannot open symbol " << dlerror() << '\n';   
        return -1;
    }

    Upper_ty upper = (Upper_ty)dlsym(handle, "UpperC");
    if (dlsym_error)
    {
        cout << "cannot open symbol " << dlerror() << '\n';   
        return -1;
    }
    int a = 0;
    int b = 0;
    int c = 0; 
    cout << "please enter 3 digits following enter" << endl;
    cin >> a >> b >> c;
    bla(a, b ,c);

    char ch = 'a';
    cout << "You entered " << ch << endl;
    cout << "The UpperC function returned " << upper(ch) << endl;

    dlclose(handle);

    return 0;
}
