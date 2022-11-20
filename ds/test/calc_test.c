/*****************************************************
 * Calculator                                        *
 * Assaf Ainhoren                                    *
 * Reviewer: Maor Fakliro                            *
 * date: 22.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/

#include <assert.h> /* assert */

#include "calc.h"

int main(void)
{
	status_ty return_val = SUCCESS;
	
	assert(4.2 == Calculate("2+2.2", &return_val));
	assert(1 == Calculate("1", &return_val));
	assert(0 == return_val);
	assert(20 == Calculate("12+8", &return_val));
	assert(0 == return_val);
	assert(22 == Calculate("12+8+2", &return_val));
	assert(123 == Calculate("(123)", &return_val));
	assert(0 == return_val);
	assert(4 == Calculate("(1/2)^-2",& return_val));
	assert(0 == return_val);
	assert(0 == Calculate("2-2", &return_val));
	assert(-1 == Calculate("2-3", &return_val));
	assert(3 == Calculate("2-3+4", &return_val));
	assert(31 == Calculate("2-3+4*7+4", &return_val));
	assert(6 == Calculate("2-3+4*7/4", &return_val));
	assert(21 == Calculate("2+3+4^2", &return_val));
	assert(16392 == Calculate("2^3+4^7", &return_val));
	assert(16896 == Calculate("2^3^2+4^7", &return_val));
	assert(513 == Calculate("2^3^2+1^7", &return_val));
	assert(16896.25 == Calculate("2^3^2+4^7+1^2^6*1/4", &return_val));
	assert(0.125 == Calculate("2^-3", &return_val));
    assert(0.25 == Calculate("2^-2", &return_val));
    assert(-8 == Calculate("-2^3", &return_val));
    assert(1 == Calculate("-2--3", &return_val));
    assert(6 == Calculate("(2+1)+3", &return_val));
    assert(6 == Calculate("2+(1+3)", &return_val));
    assert(8 == Calculate("2+(2+4)", &return_val));
    assert(64 == Calculate("2^(2+4)", &return_val));
    assert(1 == Calculate("1^(2+4)", &return_val));
    assert(12 == Calculate("3^1^(1+2)+5+4", &return_val));
    assert(12 == Calculate("(3^1^(1+2)+5+4)", &return_val));
    assert(12 == Calculate("[3^1^(1+2)+5+4]", &return_val));
    assert(12 == Calculate("{3^1^(1+2)+[5+4]}", &return_val));
    assert(13 == Calculate("1+[4+{4-2}*4]", &return_val));
    assert(13 == Calculate("   1   +[4+{4-2}*4]", &return_val));
    assert( 0 == return_val);
    assert(0 == Calculate("   1   +[4+{4-2}*]", &return_val));
    assert(31 == Calculate("2+(2+4)^2+1^2^3*3-[{4-2}*5]", &return_val));
    assert(0 == Calculate("2+(2+4)^^2+1^2^3*3-[{4-2}*5]", &return_val));
    assert(1 == return_val);
    assert(0 == Calculate("{2+2)", &return_val));
	assert(1 == return_val);
	Calculate("+=", &return_val);
	assert(1 == return_val);
	assert(0 == Calculate("+9  *", &return_val));
	assert(1 == return_val);
	Calculate("+2", &return_val);
	assert(0 == return_val);
	Calculate("- 6", &return_val);
	assert(0 == return_val);
	Calculate("2^(1/4)", &return_val);
	assert(0 == return_val);
	Calculate("2/0", &return_val);
	assert(1 == return_val);
	assert(31 == Calculate("2*4^2-+1", & return_val));
	assert(0 == return_val);
	
	return (0);
}




