#include <time.h> /* time_t */
#include <stdio.h> /* fgets, puts */

static const time_t g_five_seconds = 5;

int main(void)
{
    time_t start = time(&start);
    while (g_five_seconds >= time(NULL) - start) 
    {
        puts("But Why!?!?!?!?");
    }
    puts("continue entering commands");
    return 0;
}