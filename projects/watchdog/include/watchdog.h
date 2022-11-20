/****************************************************
* Watchdog                                          *
* Assaf Ainhoren                                    *
* Reviewer: Haggai Newman                           *
* date: 31.08.2022                                  *
* This program is a software watchdog timer -       *
* the watchdog detect software anomalies            *
* and reset the process if any occur.               *
****************************************************/
/********************************libraries includes****************************/
#include <stddef.h> /* size_t */

#include "utils.h" /* status_ty, bool_ty */
typedef enum 
{
    SUCCESSED = 0,
    FAILED = 1,
    SCHEDULER_CREATE_ERROR = 2,
    BAD_UID = 3,
    CREATE_WD_FAIL = 4,
    CREATE_THREAD_FAIL = 5,
    SET_ENV_FAIL = 6,
    FORK_FAIL = 7,
    EXEC_FAIL  =8,
    WD_CREATE_FAIL = 9
}wd_status_ty;

/****************************************************
* MakeMeImmortal:Create Watchdog over               *
*current block of code                              *
* params: time_interval - no. of seconds to polling *        
*   threshold - no. of retries before reset         * 
*   executable_name - exectuable to reset if needed * 
* Return: SUCCESSED if successful.                  *
* otherwise:                                        *
* according to the enum above, failure              *
*    could be a result of several sitation as       *
*    mentioned above                                *
*    in any case MakeMyImmortal return any other    *
*    value than SUCCESSES - the client program need *
* to call LetMeDie or else the program is unsafe.   * 
* Complexity:                                       *
   Time: O(1)                                       *
   Space: O(1)                                      *
****************************************************/
wd_status_ty MakeMeImmortal(size_t time_interval,
                         size_t threshold,
                         char *executable_name);
/*****************************************************
* LetMeDie:                                          *
* Frees all the resources of watchdog                *
* From this point the program is no longer protected *
* Complexity:                                        *
   Time: O(1)                                        *
   Space: O(1)                                       *
******************************************************/
void LetMeDie(void);
