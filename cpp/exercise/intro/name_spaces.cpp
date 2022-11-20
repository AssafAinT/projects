namespace useless
{
unsigned int g_wasteful[400];
extern int g_notthere;
void Foo() {};


namespace wasteoftyme
{
void Foo() {};  
} // namespace wateoftyme
}// namespace useless

namespace stupid
{
void Foo() {}
void Bar() {} 
void DoNothing(unsigned int) {};
} // namespace stupid

namespace useless
{
void DoNothing(int) {}; 
}// namespace useless

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo() {}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    using wasteoftyme::Foo;
    Foo(); //try uncommenting this line, solve the errror 
    Bar(); // why this line is not generating errors
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
void DoUselessStuff()
{
    DoNothing(g_wasteful[3] + 1);
}
void Foo(int) {};
}// namespace useless

int main (void)
{
    DoStuff();
    return 0;
}