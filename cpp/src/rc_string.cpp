/****************************************************
* simple_string                                     *
* Assaf Ainhoren                                    *
* Reviewer: Haggai Newman                           *
* date: 3.10.2022                                   *
****************************************************/
/********************************libraries includes****************************/
#include <cstring> /* string lib, memmove*/
#include <cassert> /* assert */

#include "rc_string.hpp"

namespace ilrd
{
struct SharedStr
{
    size_t counter;  
    char m_str[1];   
};
}

namespace Rcstrutils
{
ilrd::SharedStr *AllocateRCString(const char *string)
{
    size_t string_size = strlen(string) + 1;
    size_t size_to_alloc = offsetof(ilrd::SharedStr, m_str) + string_size;
    
    ilrd::SharedStr *to_ret = static_cast<ilrd::SharedStr*>(operator new(size_to_alloc));
    memmove((to_ret->m_str), string, string_size);
    to_ret->counter = 1;
    
    return (to_ret);
}
void Deatach(ilrd::SharedStr *string)
{
    --string->counter;
    if ( 0 == string->counter)
    {
        delete string;
    }

}

}
namespace ilrd
{
RCString::RCString(const char *string):m_sharedStr(Rcstrutils::AllocateRCString(string))
{
    //
}
RCString::RCString(const RCString& other): m_sharedStr(other.m_sharedStr)
{
    ++other.m_sharedStr->counter;
} 
RCString::~RCString()
{
    Rcstrutils::Deatach(m_sharedStr);
}

RCString& RCString::operator=(const RCString& other)
{
    if (m_sharedStr != other.m_sharedStr)
    {
        Rcstrutils::Deatach(m_sharedStr);
        m_sharedStr = other.m_sharedStr;    
        ++m_sharedStr->counter;
    }


    return *this;
}
const char *RCString::Cstr() const
{
    return m_sharedStr->m_str;
}

char & RCString::operator[](size_t index)
{
    assert(this->Length() >= index);
    if ( 1 != m_sharedStr->counter)
    {
        ilrd::SharedStr *temp = Rcstrutils::AllocateRCString(m_sharedStr->m_str);
        Rcstrutils::Deatach(m_sharedStr);
        m_sharedStr = temp;
    }

    return m_sharedStr->m_str[index];
}
char RCString::operator[](size_t index) const
{
    assert(this->Length() >= index);
    
    return m_sharedStr->m_str[index];
}
size_t RCString::Length() const
{
    return strlen(Cstr());
}

bool operator==(const RCString& string1, const RCString& string2)
{
    return (0 == strncmp(string1.Cstr() ,string2.Cstr(), string1.Length()));
}
std::ostream& operator<<(std::ostream& os, const RCString& string)
{
    return (os << string.Cstr());
}
std::istream& operator>>(std::istream& is, RCString& string)
{
    char buff[1024];
    is >> buff;
    string = buff;

    return is;
}

bool operator!=(const RCString& string1, const RCString& string2)
{
    return (!(string1 == string2));
}
// to change to strcmp
bool operator>(const RCString& string1, const RCString& string2)
{
    return (0 < strncmp(string1.Cstr() ,string2.Cstr(), string1.Length()));
}
bool operator<(const RCString& string1, const RCString& string2)
{
    return (0 > strncmp(string1.Cstr() ,string2.Cstr(), string1.Length()));
}
}