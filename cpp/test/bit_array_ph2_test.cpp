#include <iostream>
#include <cassert>
#include "bit_array_ph2.hpp"

using namespace ilrd;
using namespace std;
#define SIZE 110

int main(void)
{
    const BitArray<64> bit_array;
    const BitArray<64> bit_array2;
    assert(!bit_array[63]);
    
 
    BitArray<64> bit_array3;
    BitArray<64> bit_array4;
    bit_array3[0] = bit_array4[0];
    bit_array3[2] = true;
    cout << bit_array3[2] << endl;

    assert(bit_array3[2]);

    BitArray<128> b1;
    for (int i = 0;i<128;++i)
    {
        b1[i] = true;
        assert(b1[i]);
    }

    for (int i = 0;i<128;++i)
    {
        cout << b1.Get(i) << endl;
    }

    cout << b1.Get(127) << endl;

    b1.Set(0 , 127);
    cout << b1.Get(127) << endl;
    
    b1.Flip(127);
    cout << b1.Get(127) << endl;

    b1.Flip();
    cout << "After flipall" << endl;

    for (int i = 0;i<128;++i)
    {
        std::cout << b1[i];
    }
    cout << "\n";

    b1.Flip();
    cout << "After flipall" << endl;

    for (int i = 0;i<128;++i)
    {
        std::cout << b1[i];
    }
    cout << "\n";

    b1.Set(false);
    cout << "After SetAll" << endl;
    for (int i = 0;i<128;++i)
    {
        std::cout << b1[i];
    }
    cout << "\n";

    b1.Set(true);
    cout << "After SetAll to 1" << endl;
    for (int i = 0;i<128;++i)
    {
        std::cout << b1[i];
    }
    cout << "\n";
    BitArray<128> b2;
    b2.Set(false);

    b1 &= b2;

    cout << "After &=" << endl;
    for (int i = 0;i<128;++i)
    {
        std::cout << b1[i];
    }
    cout << "\n";

    b1.Set(true);
    b1[0] = false;
    b2 ^= b1;
    cout << "After ^=" << endl;
    for (int i = 0;i<128;++i)
    {
        std::cout << b2[i];
    }
    cout << "\n";

    BitArray<64> b3;
    BitArray<64> b4;
    b3.Set(true);
    b4.Set(false);

    b4 |= b3;

    cout << "After |=" << endl;
    for (int i = 0;i<64;++i)
    {
        std::cout << b4[i];
    }
    cout << "\n";

    cout << (b3 == b4) << endl;

    BitArray<64> b5;
    BitArray<64> b6;

    b5.Set(true);
    b6.Set(true);
    cout << (b5 == b6) << endl;

    cout << (b3 == b6) << endl;

    BitArray<110> b7;
    b7.Set(true);
    BitArray<110> b8;
    b8.Set(false);

    cout << (b7 != b8) << endl;

    b8.Set(true);
    cout << b7.Count() << endl;
    // cout << (b7 != b8) << endl;
    cout << b8.ToString() << endl;
    b8[0] = false;
    cout << b8.ToString() << endl;
    // b8 <<= 4;
    // cout << b8.ToString() << endl;

    BitArray<8> shift_bit;
    shift_bit.Set(true);
    shift_bit <<= 4;
    cout << shift_bit.ToString() << endl;
    shift_bit.Set(true);
    shift_bit >>= 6;
    cout << shift_bit.ToString() << endl;

    BitArray<128> shift_bit_2;
    shift_bit.Set(false);
    shift_bit_2[64] = true;
    cout << shift_bit_2.ToString() << endl;
    shift_bit_2 >>= 1;
    cout << shift_bit_2.ToString() << endl;


       
    return 0;
}