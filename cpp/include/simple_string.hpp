/****************************************************
* simple_string_cpp                                 *
* Assaf Ainhoren                                    *
* Reviewer: Herscho the king                        *
* date: 11.09.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#ifndef __ILRD_RD127_128_SIMPLE_STRING_H__
#define __ILRD_RD127_128_SIMPLE_STRING_H__
#include <cstddef> // size_t

namespace ilrd
{
    class String
    {
    public:
        String(const char *string = ""); // default Ctor non explicit in purpose
        String(const String& other);             // Cctor
        ~String();                                // destructor
        String& operator=(const String& other);  // assignment operator

        const char *Cstr() const; 
        size_t Length() const;


    private:
        char *m_str;
        
    };
    bool operator>(const String& string1, const String& string2);
    bool operator<(const String& string1, const String& string2);
    bool operator==(const String& literal, const String& string);
    bool operator!=(const String& string1, const String& string2);

    std::ostream& operator<<(std::ostream& os, const String& string);
    std::istream& operator>>(std::istream& is, String& string);
}

#endif // __ILRD_RD127_128_SIMPLE_STRING_H__    