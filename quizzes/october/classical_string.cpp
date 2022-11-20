#include <iostream>
#include <cstring> /* string lib, memmove*/
#include <new>
#include <cassert> /* assert */
#include "classical_string.hpp"
namespace strutils
{
char *Allocate(const char *string)
{
    size_t string_size = strlen(string) + 1;

    char *new_str = new char[string_size];
    memmove(new_str, string, string_size);

    return (new_str);
}
}

namespace ilrd
{
String::String(const char *string): m_str(strutils::Allocate(string))
{
    //
}

String::String(const String& other): m_str(strutils::Allocate(other.m_str))
{
    //
}
String::~String()
{
    delete[] m_str;
    m_str=0; 

}

String& String::operator=(const String& other)
{
    char *temp = strutils::Allocate(other.m_str);

    delete[] m_str;
    
    m_str = temp;
    
    return *this;
}

char& String::operator[](size_t ind)
{
    assert(ind <= Length());

    return m_str[ind];
}

bool operator==(const String& literal, const String& string)
{
    return (0 == strcmp(literal.Cstr() ,string.Cstr()));
}
std::ostream& operator<<(std::ostream& os, const String& string)
{
    return (os << string.Cstr());
}
std::istream& operator>>(std::istream& is, String& string)
{
    char buff[1024];
    is >> buff;
    string = buff;

    return is;
}

bool operator!=(const String& string1, const String& string2)
{
    return (!(string1 == string2));
}
// to change to strcmp
bool operator>(const String& string1, const String& string2)
{
    return (0 < strcmp(string1.Cstr() ,string2.Cstr()));
}
bool operator<(const String& string1, const String& string2)
{
    return (0 > strcmp(string1.Cstr() ,string2.Cstr()));
}

const char *String::Cstr() const
{
    return m_str;
}
size_t String::Length() const
{
    return strlen(m_str);
}
}
