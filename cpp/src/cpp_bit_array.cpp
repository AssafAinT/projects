/****************************************************
* cpp_bit_array                                     *
* Assaf Ainhoren                                    *
* Reviewer: Herscho the king                        *
* date: 11.09.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <iostream>
#include <climits> // *CHAR_BIT
#include <cassert>
// #include "cpp_bit_array.hpp"
#include "bit_arraycpp_phase2.hpp"

const size_t NUM_OF_BITS_IN_BIT_ARR =  (sizeof(ilrd::BitArray) * CHAR_BIT);
const size_t MAX_NUM_BIT_ARRAY_TY = 0xffffffffffffffff;
namespace ilrd
{
    static bool BitArrayGetValue(size_t bitarray, size_t index)
    {
    
        return ((bitarray >> (index -1)) & 1);
    }

    static size_t BitArraySetBitOff(size_t bitarray, size_t index)
    {
        return (bitarray & (~((size_t)1 << (index - 1))));
    } 
    static size_t BitArraySetBit(size_t bitarray, size_t index, bool bit_value)
    {   
        return (BitArraySetBitOff(bitarray, index) | (bit_value << (index - 1)));
    }

    BitArray::BitProxy::BitProxy(size_t &bArr, size_t index): m_bitArrayproxy(&bArr), m_index(index)
    {
        //
    }

    BitArray::BitProxy& BitArray::BitProxy::operator=(bool val)
    {
        *m_bitArrayproxy = BitArraySetBit(*m_bitArrayproxy,
                                                    m_index, val);

        return *this;
    }
    BitArray::BitProxy& BitArray::BitProxy::operator=(const BitProxy& other)
    {
        *m_bitArrayproxy = *other.m_bitArrayproxy;

        return *this;
    }

    BitArray::BitArray(): m_bitArray(0)
    {
        //
    }
    BitArray::BitProxy::operator bool() const
    {
        return (BitArrayGetValue(*m_bitArrayproxy, m_index));
    }
    BitArray::BitProxy BitArray::operator[](size_t index) 
    {
        BitArray::BitProxy ret(m_bitArray, index);

        return ret;
        
    }
    bool BitArray::operator[](size_t index) const
    {
        return BitArrayGetValue(m_bitArray, index);
    }
}