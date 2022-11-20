#include <iostream> // std::cout
#include <cassert> // assert
#include "simple_string.hpp"



int main(void)
{
    ilrd::String s1("hello");
    std::cout << "s1 is: " << s1.Cstr() << std::endl;
    ilrd::String s2(s1);
    std::cout << "s2 is: " << s2.Cstr() << std::endl;
    ilrd::String s3;
    std::cout << "s3 is: " << s3.Cstr() << std::endl;
    s3 = s2;
    std::cout << "after assignment s3 is: " << s3.Cstr() << std::endl;

    std::cout << "using << operator s3 is:" << s3 << std::endl;

    std::cout << "123 equal to s3? "<< ("123" == s3) << std::endl;
    std::cout << "s2 equal to s3? "<< (s2 == s3) << std::endl;

    ilrd::String s4("Boomchakalak");
    std::cout << "s4 > s3? "<< (s4 > s3) << std::endl;

    std::cout << "s4 < s3? "<< (s4 < s3) << std::endl;

    const char *s5 ="hello";
    const char *s6 = "hello";
    std::cout << "Is hello world bigger than hello? "<< (s5 == s6) << std::endl;
    assert((s5 == s6));
    std::cout << "Is hello world bigger than hello? "<< (s5 == s6) << std::endl;

    //std::cin >> s2;
    //std::cout << "using << operator s2 is:" << s2 << std::endl;
    ilrd::String s7;
    std::cin >> s7;
    std::cout << "using << operator s7 is:" << s7 << std::endl;
    return 0;

    

}