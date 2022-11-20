#ifndef __ILRD_RD127_128_BIT_ARRAY_HPP__
#define __ILRD_RD127_128_BIT_ARRAY_HPP__

#include <cstddef>
#include <iostream>

namespace ilrd
{
    class BitArray
    {
    class BitProxy;
    public:
        explicit BitArray();

        BitProxy operator[](size_t index);
        bool operator[](size_t index) const;
    private:
        size_t m_bitArray;
        class BitProxy
        {
        public:
            BitProxy(size_t &bArr, size_t index);
            BitProxy &operator=(bool val);
            BitProxy &operator=(const BitProxy &other);
            operator bool() const;

        private:
            size_t *m_bitArrayproxy;
            size_t m_index;
        };

    };
}
#endif //__ILRD_RD127_128_BIT_ARRAY_HPP__