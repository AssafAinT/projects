#include <iostream>
#include <dlfcn.h> // dlopen, dlsym
#include <string.h> // stricmp

using namespace std;
int main(int argc, char *argv[])
{
    
    void *handle = dlopen("/home/assaf/git/cpp/exercise/libshared.so", RTLD_LAZY);

    if (!handle)
    {
        cout << "Cannot open library: " << dlerror() << '\n';
        return 22;
    }
    if (0 == strcmp ("Bla", argv[1]))
    {
        typedef void (*Bla_t)();
        Bla_t useBla = (Bla_t)dlsym(handle, "_Z3Blav");
        const char *dlsym_error = dlerror();
        if (dlsym_error)
        {
           cout << "cannot open symbol " << dlerror() << '\n';   
           return -1;
        }
        useBla();
    }
    if (0 == strcmp ("Foo", argv[1]))
    {
        typedef void (*Foo_t)();
        Foo_t useFoo = (Foo_t)dlsym(handle, "_Z3Foov");
        const char *dlsym_error = dlerror();
        if (dlsym_error)
        {
            cout << "cannot open symbol " << dlerror() << '\n';   
            return -1;
        }
        useFoo();
    }


    dlclose(handle);
    return 0;
}