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

// #if _cplusplus<201104
// #define noexcept throw()
// #endif //#if _cplusplus<201104

namespace ilrd
{
    template <size_t bits>
    class BitArray
    {
        class BitProxy;
    public:
        explicit BitArray() noexcept;

        BitProxy operator[](size_t index) noexcept(false);
        bool operator[](size_t index) const noexcept(false);
        // bit wise operators
        BitArray& operator&=(const BitArray &other) noexcept;
        BitArray& operator^=(const BitArray &other) noexcept;
        BitArray& operator|=(const BitArray &other) noexcept;
        
        bool operator!=(const BitArray &other) const noexcept;
        bool operator==(const BitArray &other) const noexcept;
        //adv
        BitArray& operator>>=(size_t other) noexcept;
        BitArray& operator<<=(size_t other) noexcept;
        
        BitArray &Set(bool val ,size_t pos) noexcept(false);
        BitArray &Set(bool val) noexcept;
        
        bool Get(size_t pos) const noexcept(false);
        
        BitArray &Flip(size_t pos) noexcept(false);
        BitArray &Flip(void) ;

        size_t Count() const noexcept; 
        std::string ToString(void) const noexcept(false);
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

    }; //BitArray

    namespace detail
    {
        class Iterator
        {
            public:
                explicit Iterator(size_t *bArr, size_t index) noexcept;
                Iterator &operator++(int) noexcept(false);
                Iterator &operator++() noexcept(false);
                bool operator==(const Iterator &other) const noexcept;
                Iterator &operator*() const noexcept;
            private: 
                size_t *m_bitProxi;
                size_t m_index;
        };//Iterator
        class ToString
        {
            public:
                ToString() noexcept(false);
                void operator()(const Iterator &other) noexcept(false);
            private:
                std::string bit_str;
        }; // class ToString
        class ShiftTor
        {
            public:
                ShiftTor() noexcept;
                size_t operator()(const Iterator& other) noexcept(false);
            private:
                size_t mask;
        };//class ShiftTor
        class CountTor
        {
            public:
                CountTor() noexcept;
                size_t operator()(const Iterator& other) noexcept(false);
            private:
                size_t sum;
        };// class CountTor
    }//namespace detail

} // namespace ilrd

#endif // __ILRD)RD127_128_BIT_ARRAY_HPP__
