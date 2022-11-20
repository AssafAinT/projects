/*********************************************************************** \
 *   Orginal Name : BitArray.hpp                                         *
 *   Name: Assaf Ainhoren                                                *
 *   Reviewer : May the Force be with me                                 *
 *   Date 08.11.22                                                       *
 ***********************************************************************/
#ifndef __ILRD_RD127_128_BIT_ARRAY_HPP__
#define __ILRD_RD127_128_BIT_ARRAY_HPP__

#include <iostream> //std
#include <cstddef> //size_t 
#include <string> // string
#include <exception> // throw exception
#include <algorithm> // stl algorithm
#include <numeric>//accumulate

static const size_t SIZE_T_BITS = (sizeof(size_t) *  (__CHAR_BIT__));

namespace utils
{
static bool BitArrayGetValue(size_t bitarray, size_t index)
{
    size_t mask = 1;
    return ((bitarray >> (index)) & (size_t)mask);
}
static size_t BitArraySetBitOff(size_t bitarray, size_t index)
{
    size_t mask = 1;
    return (bitarray & (~((size_t)mask << (index))));
} 
static size_t BitArraySetBit(size_t bitarray, size_t index, bool bit_value)
{   
    return (BitArraySetBitOff(bitarray, index) | ((size_t)bit_value << (index)));
}
}

using namespace utils;
namespace ilrd
{
    template <size_t bits>
    class BitArray
    {
        class BitProxy;
    public:
        explicit BitArray() noexcept;
        // cctor dtor operator= Compiler generated
        BitProxy operator[](size_t index) noexcept(false);
        bool operator[](size_t index) const noexcept(false);
        // bit wise operators
        BitArray& operator&=(const BitArray &other) noexcept;
        BitArray& operator^=(const BitArray &other) noexcept;
        BitArray& operator|=(const BitArray &other) noexcept;
        bool operator!=(const BitArray &other) const noexcept;
        bool operator==(const BitArray &other) const noexcept;
        
        BitArray& operator>>=(size_t other) noexcept;
        BitArray& operator<<=(size_t other) noexcept;
        
        BitArray &Set(bool val) noexcept; //set_all
        BitArray &Set(bool val ,size_t pos) noexcept(false); 
        
        bool Get(size_t pos) const noexcept(false);
        
        BitArray &Flip(size_t pos) noexcept(false);
        BitArray &Flip(void); //flip_all

        size_t Count() const noexcept; 

        std::string ToString(void) const noexcept(false);
    private:
        size_t m_bitArray[(bits / ((sizeof(size_t) * 
                                  __CHAR_BIT__)-(size_t)1lu)) +
                                   (size_t)1lu];
    
        class BitProxy
        {
            public:
                explicit BitProxy(BitArray<bits> &bArr, size_t index) noexcept;
                BitProxy &operator=(bool val) noexcept;
                BitProxy &operator=(const BitProxy &other) noexcept;
                operator bool() const noexcept;
            private:
                BitArray<bits> &m_bitProxi;
                size_t m_index;
        };//BitProxy
    }; //BitArray

    namespace detail
    {
        enum
        {
            MAX_CHAR = 0xff
        };
    /* count each on bit in the byte */
    /* static so we will not have double defenition*/
    static const int ByteCountOnTable256[256] = 
    {
    #   define C2(n)     n,     n + 1,     n + 1,     n + 2
    #   define C4(n) C2(n), C2(n + 1), C2(n + 1), C2(n + 2)
    #   define C6(n) C4(n), C4(n + 1), C4(n + 1 ), C4(n + 2)
        C6(0), C6(1), C6(1), C6(2)
    };
    template <size_t bits>
    class Iterator
    {
        public:
            explicit Iterator(BitArray<bits> &m_bitArray, size_t index) noexcept;
            Iterator &operator++() noexcept(false);
            Iterator &operator--() noexcept(false);
            Iterator &operator++(int) noexcept(false);
            bool operator==(const Iterator &other) const noexcept;
            bool operator!=(const Iterator &other) const noexcept;
            Iterator &operator*() noexcept;
            
        private: 
            BitArray<bits> &m_bitArray;
            size_t m_index;
            friend class FlipTor;
            friend class SetAll;
            friend class ToString;
            friend class ShiftTor;
            friend class ShiftTorRight;
            friend class ZeroItTor;
    };//Iterator
    template <size_t bits>
    class ReverseIterator
    {
        public:
            explicit ReverseIterator(BitArray<bits> &m_bitArray, size_t index) noexcept;
            ReverseIterator &operator++() noexcept(false);
            bool operator==(const ReverseIterator &other) const noexcept;
            bool operator!=(const ReverseIterator &other) const noexcept;
            ReverseIterator &operator*() noexcept;
            
        private: 
            Iterator<bits> iter;
            friend class ShiftTorRight;
            friend class ZeroItTor;
    };//ReverseIterator
    
    class ToString
    {
        public:
            ToString(std::string &o_str) noexcept(false): o_bit_str(o_str){}
            template <size_t bits>
            void operator()(const Iterator<bits>& other) noexcept(false)
            {
                o_bit_str += std::to_string(other.m_bitArray[other.m_index]);
            }
            std::string Cstr()
            {
                return o_bit_str.c_str();
            }
        private:
            std::string &o_bit_str;
    }; // class ToString

    class ShiftTor
    {
        public:
            ShiftTor(size_t shifts): m_shifts(shifts) {}
            template <size_t bits>
            void operator()(const Iterator<bits>& other) noexcept(false)
            {

                other.m_bitArray.Set(other.m_bitArray.
                                 Get(other.m_index + m_shifts), other.m_index);          
            }
        private:
        size_t m_shifts;

    };//class ShiftTor
    
    class ShiftTorRight
    {
        public:
            ShiftTorRight(size_t shifts): m_shifts(shifts) {}
            template <size_t bits>
            void operator()(const Iterator<bits>& other) noexcept(false)
            {

                other.m_bitArray.Set(other.m_bitArray.
                                 Get(other.m_index+ m_shifts), other.m_index - 1);          
            }
            template <size_t bits>
            void operator()(const ReverseIterator<bits>& other) noexcept(false)
            {

                other.iter.m_bitArray.Set(other.iter.m_bitArray.
                                      Get(other.iter.m_index - m_shifts),
                                      other.iter.m_index);          
            }
        private:
        size_t m_shifts;

    };//class ShiftTor
    
    class ZeroItTor
    {
        public:
            template <size_t bits>
            void operator()(const Iterator<bits>& other) noexcept(false)
            {
                other.m_bitArray.Set(0, other.m_index);          
            }

            template <size_t bits>
            void operator()(const ReverseIterator<bits>& other) noexcept(false)
            {
                other.iter.m_bitArray.Set(0, other.iter.m_index -1);          
            }

    };//class ZeroItTor

    class CountTor
    {
        public:
            CountTor(size_t &sum) : o_m_sum(sum){}
            void operator()(const size_t num) noexcept
            {
                o_m_sum += (ByteCountOnTable256[num & MAX_CHAR]) +
                (ByteCountOnTable256[(num >> 8) & MAX_CHAR]) +
                (ByteCountOnTable256[(num >> 16) & MAX_CHAR]) +
                (ByteCountOnTable256[(num >> 24) & MAX_CHAR]) + 
                (ByteCountOnTable256[(num >> 32) & MAX_CHAR]) +
                (ByteCountOnTable256[(num >> 40) & MAX_CHAR]) +
                (ByteCountOnTable256[(num >> 48) & MAX_CHAR]) +
                (ByteCountOnTable256[(num >> 56) & MAX_CHAR]);
            }
            size_t GetSum()
            {
                return o_m_sum;
            }
            private:

            size_t &o_m_sum;
        
    };// class CountTor

    class FlipTor
    {
        public:
            template <size_t bits>
            void operator()(const Iterator<bits>& other) noexcept(false)
            {
                other.m_bitArray.Flip(other.m_index);
            }
    };// class FlipTor

    class SetAll
    {
        public:
            SetAll(bool val):m_val(val) {}
            template <size_t bits>
            void operator()(const Iterator<bits>& other) noexcept(false)
            {
                other.m_bitArray.Set(m_val, other.m_index);
            }
        private:
            bool m_val;
    };// class SetAll
    
    class And
    {
        public:
            And(size_t *BitArray) : m_BitArray(BitArray), offset(0){}
            void operator()(const size_t other) 
            {
                m_BitArray[offset] &= other;
                ++offset;                
            }
        private:
        size_t *m_BitArray;
        size_t offset;
    };
    class Xor
    {
        public:
            Xor(size_t *BitArray) : m_BitArray(BitArray), offset(0){}
            void operator()(const size_t other) 
            {
                m_BitArray[offset] ^= other;
                ++offset;                
            }
        private:
        size_t *m_BitArray;
        size_t offset;
    };
    class Or
    {
        public:
            Or(size_t *BitArray) : m_BitArray(BitArray), offset(0){}
            void operator()(const size_t other) 
            {
                m_BitArray[offset] ^= other;
                ++offset;                
            }
        private:
        size_t *m_BitArray;
        size_t offset;
    };
    class NotEq
    {
        public:
            NotEq(const size_t *BitArray) : m_BitArray(BitArray), offset(0){}
            bool operator()(const size_t other) 
            {
                return(m_BitArray[offset++] != other);
                
            }
        private:
        const size_t *m_BitArray;
        size_t offset;
    };
    template <size_t bits>
    Iterator<bits>::Iterator(BitArray<bits> &bArr, size_t index) noexcept :
                             m_bitArray(bArr), m_index(index)
    {

    }
    template <size_t bits>
    Iterator<bits> &Iterator<bits>::operator++(int num) noexcept(false)
    {
        if (bits >= m_index + num)
        {
            m_index + num;
        }
        else
        {
            throw(std::out_of_range("++ operator out of range"));
        }
        return *this;
    }
    template <size_t bits>
    Iterator<bits> &Iterator<bits>::operator++() noexcept(false)
    {
        if (bits > m_index)
        {
            ++m_index;
        }
        else
        {
            throw(std::out_of_range("++ operator out of range"));
        }
        return *this;
    }
     template <size_t bits>
    Iterator<bits> &Iterator<bits>::operator--() noexcept(false)
    {
        if (bits <= m_index  || 0 >= m_index)
        {
            throw(std::out_of_range("-- operator out of range"));
        }
        else
        {
            --m_index;
        }
        return *this;
    }
    template <size_t bits>
    Iterator<bits> &Iterator<bits>::operator*() noexcept
    {
        return (*this);
    }
    template <size_t bits>
    bool Iterator<bits>::operator==(const Iterator<bits> &other) const noexcept
    {
        return (m_bitArray == other.m_bitArray && m_index == other.m_index);
    }
    template <size_t bits>
    bool Iterator<bits>::operator!=(const Iterator<bits>&other) const noexcept
    {
        return !(this->operator==(other));
    }
    

    template <size_t bits>
    ReverseIterator<bits>::ReverseIterator(BitArray<bits> &bArr,
                                           size_t index) noexcept :
                                           iter(Iterator<bits> (bArr ,index))
    {

    }
    
    template <size_t bits>
    ReverseIterator<bits> &ReverseIterator<bits>::operator++() noexcept(false)
    {
        iter.operator--();
        return *this;
    }
    template <size_t bits>
    ReverseIterator<bits> &ReverseIterator<bits>::operator*() noexcept
    {
        return (*this);
    }
    template <size_t bits>
    bool ReverseIterator<bits>::operator!=(const ReverseIterator<bits>&other)
                                           const noexcept
    {
        return (iter.operator!=(other.iter));
    }
    }//namespace detail

    template<size_t bits>
    typename BitArray<bits>::BitProxy &BitArray<bits>::BitProxy::
                                      operator=(const BitProxy &other) noexcept
    {
        m_bitProxi = other.m_bitProxi;

        return *this;
    }

    template<size_t bits>
    typename BitArray<bits>::BitProxy &BitArray<bits>::BitProxy::
                                                    operator=(bool val) noexcept
    {
        m_bitProxi.Set(val, m_index);
        
        return *this;
        
    }
    template<size_t bits>
    BitArray<bits>::BitProxy::BitProxy(BitArray<bits> &bArr, size_t index) 
                                      noexcept: m_bitProxi(bArr), m_index(index)
    {
        //
    }

    template<size_t bits>
    BitArray<bits>::BitProxy::operator bool() const noexcept
    {
        return (m_bitProxi.Get(m_index));
    }

    template <size_t bits>
    BitArray<bits>::BitArray()noexcept: m_bitArray{0}{}
    
    template <size_t bits>
    typename BitArray<bits>::BitProxy BitArray<bits>::
                                        operator[](size_t index) noexcept(false)
    {  
        if (index >= bits)
        {
            throw(std::out_of_range("operator [] out of range"));
        }
        
        return BitArray<bits>::BitProxy (*this, index);
    }

    template <size_t bits>
    bool BitArray<bits>::operator[](size_t index) const noexcept(false)
    {
        if (index >= bits)
        {
            throw(std::out_of_range("operator const [] out of range"));
        }
        return((m_bitArray[index/SIZE_T_BITS]
              >> (SIZE_T_BITS - (index%SIZE_T_BITS))) & 1);
    }

    template <size_t bits>
    bool BitArray<bits>::operator==(const BitArray &other) const noexcept
    {
        return !(this->operator!=(other));
    }

    template <size_t bits>
    bool BitArray<bits>::operator!=(const BitArray<bits> &other) const noexcept
    {
        detail::NotEq noty(m_bitArray);
        return(std::any_of(other.m_bitArray, other.m_bitArray +
                     ((bits / SIZE_T_BITS) + 1) ,noty));
    }
    template <size_t bits>
    BitArray<bits>& BitArray<bits>::operator&=(const BitArray<bits> &other) noexcept
    {
        detail::And andy(m_bitArray);
        std::for_each(other.m_bitArray, other.m_bitArray +
                    ((bits / SIZE_T_BITS) + 1) ,andy);
        return *this;
    }
    template <size_t bits>
    BitArray<bits> &BitArray<bits>::operator^=(const BitArray &other) noexcept
    {
        detail::Xor xory(m_bitArray);
        std::for_each(other.m_bitArray, other.m_bitArray + 
                     ((bits / SIZE_T_BITS) + 1) ,xory);
        return *this;
    }
    template <size_t bits>
    BitArray<bits> &BitArray<bits>::operator|=(const BitArray &other) noexcept
    {
        detail::Or ory(m_bitArray);
        std::for_each(other.m_bitArray, other.m_bitArray + 
                      ((bits / SIZE_T_BITS) + 1) ,ory);
        return *this;
    }

    template <size_t bits>
    BitArray<bits> &BitArray<bits>::operator>>=(size_t other) noexcept
    {
        detail::ShiftTorRight shifty(other);
        detail::ZeroItTor zeroy;
        detail::ReverseIterator<bits> start(*this, bits -1);
        detail::ReverseIterator<bits> end_shift_iter(*this,other);
        detail::ReverseIterator<bits> end(*this,0);

        std::for_each(start, end_shift_iter, shifty);
        std::for_each(end_shift_iter, end, zeroy);
        return *this;
    }
    template <size_t bits>
    BitArray<bits> &BitArray<bits>::operator<<=(size_t other) noexcept
    {
        detail::ShiftTor shifty(other);
        detail::ZeroItTor zeroy;
        detail::Iterator<bits> iter(*this, 0);
        detail::Iterator<bits> end_shift_iter(*this, bits - (other));
        detail::Iterator<bits> end_iter(*this, bits);

        std::for_each(iter, end_shift_iter, shifty);
        std::for_each(end_shift_iter, end_iter, zeroy);
        return *this;
    }
    template <size_t bits>
    BitArray<bits> &BitArray<bits>::Set(bool val ,size_t pos) noexcept(false)
    {
        if (pos >= bits)
        {
            throw(std::out_of_range("get pos out of range"));
        }

        m_bitArray[pos/ SIZE_T_BITS] = BitArraySetBit(m_bitArray[pos/ SIZE_T_BITS],
                                     (pos % SIZE_T_BITS), val);
        return (*this);
    }

    template <size_t bits>
    BitArray<bits> &BitArray<bits>::Set(bool val) noexcept
    {
        detail::Iterator<bits> iter(*this, 0);
        detail::Iterator<bits> end_iter(*this, bits);

        std::for_each(iter,end_iter , detail::SetAll(val));
        return (*this);
    }
    template <size_t bits>
    BitArray<bits> &BitArray<bits>::Flip(size_t pos) noexcept(false)
    {
        this->Set(!(this->Get(pos)), pos);

        return *this;
    }

    template <size_t bits>
    BitArray<bits> &BitArray<bits>::Flip(void) 
    {
        detail::Iterator<bits> iter(*this, 0);
        detail::Iterator<bits> end_iter(*this, bits);

        std::for_each(iter,end_iter , detail::FlipTor());

        return *this;
    }
    template <size_t bits>
    bool BitArray<bits>::Get(size_t pos) const noexcept(false)
    {
        if (pos >= bits)
        {
            throw(std::out_of_range("get pos out of range"));
        }
        return(BitArrayGetValue(m_bitArray[pos/ SIZE_T_BITS],
                                (pos % SIZE_T_BITS)));
    }
    template <size_t bits>
    size_t BitArray<bits>::Count() const noexcept
    {
        size_t sum = 0;
        detail::CountTor county(sum);

        std::for_each(m_bitArray, m_bitArray +
                     ((bits / SIZE_T_BITS) + 1), county);

        return sum;
    }
    template <size_t bits>
    std::string BitArray<bits>::ToString(void) const noexcept(false)
    {
        std::string result;
        detail::ToString stringy(result);
        detail::Iterator<bits> iter(*const_cast<BitArray<bits> *>(this), 0);
        detail::Iterator<bits>end_iter(*const_cast<BitArray<bits>*>(this), bits);

        std::for_each(iter, end_iter , stringy);
        
        return stringy.Cstr();
    }

} // namespace ilrd

#endif // __ILRD)RD127_128_BIT_ARRAY_HPP__