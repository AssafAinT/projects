/*****************************************************
 * UID                                               *
 * Assaf Ainhoren                                    *
 * Reviewer:                                         *
 * date: 19.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/
#include <assert.h>
#include "uid.h"
/*********************************Testing**************************************/
int main()
{
	uid_ty prog_uid = UidCreate();
	uid_ty same_prog_uid = UidCreate();
	
	assert (1 == UidIsEqual(prog_uid, prog_uid));
	assert (0 == UidIsEqual (prog_uid, same_prog_uid));
	assert (1 == UidIsEqual (bad_uid, bad_uid));
	
	return (0);
}

