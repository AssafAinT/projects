/*****************************************************
 * UID                                               *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 22.06.2022                                  *
 *****************************************************/
 

#define TIME_FUNCTION_FAIL -1

/********************************libraries includes****************************/
#include <pthread.h> /* mutex_t */
#include "uid.h"


static atomic_size_t uni_counter = 0;
static pthread_mutex_t uid_mutex = PTHREAD_MUTEX_INITIALIZER;

const uid_ty bad_uid = {0};

uid_ty UidCreate(void)
{
	uid_ty new_uid = {0};
	
	pthread_mutex_lock(&uid_mutex);
	new_uid.counter = atomic_fetch_add(&uni_counter, 1);
	pthread_mutex_unlock(&uid_mutex);
	
	if (TIME_FUNCTION_FAIL == (new_uid.time=time(NULL)))
	{
		new_uid = bad_uid;
	}
	new_uid.pid = getpid();
	return (new_uid);
	
}

int UidIsEqual(uid_ty uid1, uid_ty uid2)
{
	return ((uid1.pid == uid2.pid)&&
			(uid1.time == uid2.time)&&
			(uid1.counter == uid2.counter));
}


