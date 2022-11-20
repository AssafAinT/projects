#include <stdio.h>
#include <dlfcn.h> // dlsym, dlerror , dlopen

int main(void)
{
    void *handle = dlopen("/home/assaf/git/cpp/exercise/libsome_funcs.so", RTLD_LAZY);

    if (!handle)
    {
        perror("dlopen failed");
        return 22;
    }

    typedef int (*Bla_ty)(int, int, int);
    typedef char (*Upper_ty)(char);

    Bla_ty bla = (Bla_ty)dlsym(handle, "Bla");
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        perror("dlsym error");
        return -1;
    }

    Upper_ty upper = (Upper_ty)dlsym(handle, "UpperC");
    if (dlsym_error)
    {
        perror("dlsym error");
        return -1;
    }
    int a = 0;
    int b = 0;
    int c = 0; 
    printf("please enter 3 digits following enter:\n");
    scanf("%d" "%d" "%d", &a, &b, &c);
    
    bla(a, b ,c);

    char ch = 'a';
    printf("you entered %c\n", ch);
    printf("the function UpperC returned following %c\n", upper(ch));

    dlclose(handle);

    return 0;
}
