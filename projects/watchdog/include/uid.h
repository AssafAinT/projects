#ifndef __ILRD_OL127_128_UID_H__
#define __ILRD_OL127_128_UID_H__
/*****************************************************
 * UID                                               *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 19.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/

#include <unistd.h> /* pid_t */
#include <time.h> /* time_t */
#include <stddef.h> /* size_t */
#include <stdatomic.h> /* atomic_t */
#include <sys/types.h> 

struct uid
{
    pid_t pid;
    time_t time;
    atomic_size_t counter;
};

typedef struct uid uid_ty;

extern const uid_ty bad_uid;
/********************************Function Declaration**************************/
/*****************************************************
* Description: Creating UID.                         *
* Return value: The UID struct.                      *
*			upon failure : BADUID                    *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(n).                                       *
*****************************************************/
uid_ty UidCreate(void);
/*****************************************************
* Description: Computing if two UID'S are equal      *
* Return value: 1 if equal. otherwise 0              *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/

int UidIsEqual(uid_ty uid1, uid_ty uid2);

#endif /* __ILRD_OL127_128_UID_H__ */
