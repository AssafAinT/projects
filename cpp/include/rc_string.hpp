#ifndef __ILRD_RD127_128_RC_STRING_HPP__
#define __ILRD_RD127_128_RC_STRING_HPP__

#include <cstddef> // size_t
#include <iostream> //ostream

namespace ilrd
{ 
struct SharedStr;
class RCString
{
public:
    RCString(const char *string = ""); // default Ctor non explicit in purpose
    RCString(const RCString& other);             // Cctor
    ~RCString(); // destructor
                              
    RCString& operator=(const RCString& other);  // assignment operator
    char &operator[](size_t index);
    char operator[](size_t index) const;
    const char *Cstr() const; 
    size_t Length() const;
    
private:
   SharedStr *m_sharedStr;
   
};

bool operator<(const RCString& x1, const RCString& x2);
bool operator>(const RCString& x1, const RCString& x2);
bool operator==(const RCString& str1, const RCString& str2);

std::ostream& operator<<(std::ostream &os, const RCString& str);
std::istream& operator>>(std::istream &os, RCString& str);
}

#endif // __ILRD_RD127_128_RC_STRING_HPP__        
        