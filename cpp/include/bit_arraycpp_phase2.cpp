/***********************************************************************                 
*   Orginal Name : BitArray.hpp                                         *
*   Name: Mark Galperin                                                 *
*   Reviewer :                                                          *
*   Date 08.11.22                                                       *
*   Info : phase 1 - we are using nested class (Proxy design pattern),  * 
*    to enable full contoll off the inner class and not give the user   *
*    option to change it, the inner class is a represtaition of a bit   *
*    in part of the bit array.                                          *
***********************************************************************/
#ifndef __ILRD_RD127_128_BIT_ARRAY_HPP__
#define __ILRD_RD127_128_BIT_ARRAY_HPP__

#include <cstddef> //size_t 
#include <string> // string
#include <exception> // 

#if _cplusplus<201104
#define noexcept throw()
#endif //#if _cplusplus<201104

namespace ilrd
{
    template <size_t bits>
    class BitArray
    {
        class BitProxy;
    public:
        explicit BitArray() noexcept;

        BitProxy operator[](size_t index) throw(std:range_error);
        bool operator[](size_t index) const throw(std:range_error);
        // bit wise operators
        BitArray& operator&=(const BitArray &other) noexcept;
        BitArray& operator^=(const BitArray &other) noexcept;
        BitArray& operator|=(const BitArray &other) noexcept;
        bool operator!=(const BitArray &other) const noexcept;
        bool operator==(const BitArray &other) const noexcept;
        //adv
        BitArray& operator>>=(size_t other) noexcept;
        BitArray& operator<<=(size_t other) noexcept;
        
        BitArray &Set(bool val size_t pos) throw(std::range_error);
        BitArray &Set(bool val) noexcept;
        
        bool Get(size_t pos) const throw(std::range_error);
        
        BitArray &Flip(size_t pos) throw(std::range_error);
        BitArray &Flip(void) 
        
        std::string ToString(void) const throw(std::bad_alloc);
    private:
        size_t m_bitArray[(bits / ((sizeof(size_t) * __CHAR_BIT__) - 1 )) + 1];
    
        class BitProxy
        {
            public:
                explicit BitProxy(size_t *bArr, size_t index) noexcept;
                BitProxy &operator=(bool val) noexcept;
                BitProxy &operator=(const BitProxy &other) noexcept;
                operator bool() const noexcept;
            private:
                size_t *m_bitProxi;
                size_t m_index;
        };//BitProxy
        class Iterator
        {
            public:
                explicit Iterator(BitProxy &bit) noexcept();
                Iterator &operator++(int) throw(std::range_error);
                Iterator &operator++() throw(std::range_error);
                bool operator==(const Iterator &other) const noexcept;
                BitProxy &operator*() const noexcept;
            private: 
                BitProxy bit;
        };//Iterator
        class ToString
        {
            public:
                ToString() throw(std::bad_alloc);
                void operator()(const Iterator &other) throw(std::bad_alloc);
            private:
                std::string bit_str;
        };
    }; //BitArray


} // namespace ilrd

#endif // __ILRD)RD127_128_BIT_ARRAY_HPP__