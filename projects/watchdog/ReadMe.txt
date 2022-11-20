31/08/2022
WatchDog - A way To Protect your Program.
 
This program is a software watchdog timer - 
the watchdog detect software anomalies            
and reset the process if any occur. 

Accroding to the header file attached to this software - 
until next update in any case MakeMyImmortal return any other value
than SUCCESSES - 
the client program need to call LetMeDie or else the program is unsafe. 

New Update! - 01/09/2022
Makefile included - 
inorded to run the program with make file - 
1.open your terminal (ctrl+alt+t)

2.position your cd in watchdog directory
3. export your library path to pwd:
	export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
	
4.For testing purposes, place your <program_name>.c file in this directory. the Makefile
   will do the rest. 
5.write down EX=<program_name> 
	#EX=<program_name> without .c
	#To run with VLG: VLG=vlg
	#To see reachable blocks with VLG: VLG=vlgs

there is also a manual compilation option:

first we need to compile the watchdog process - 

write down : 
gd process/watchdog_process.c -I include/ src/uid.c src/scheduler_heap.c src/pqueue_heap.c src/task.c src/heap.c src/dynamic_vector.c src/utils.c -D _POSIX_C_SOURCE=200112L -o watchdog_process -pthread -D_X_OPEN_SOURCE=500

now that your watchdog_process is compiled:
we need to get the library ready :
1.
export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH

2.
gcc -c -Wall -Werror -fpic src/watchdog.c -iquote include/ src/uid.c src/pqueue_heap.c src/scheduler_heap.c src/heap.c src/dynamic_vector.c src/task.c src/utils.c

3.
gcc -shared -o libwatchdog.so *.o

4. compile your own program with the watchdog:
gd -L. -I include/ -o <executablename> <clientpath> -lwatchdog

5.loading the watchdog_process with the lib:
gd process/watchdog_process.c -L. -I include/ -lwd -D _POSIX_C_SOURCE=200112L -o watchdog_process -pthread -D_X_OPEN_SOURCE=500 -o watchdog_process

5. run the program
LD_LIBRARY_PATH=. <executablename>

compilation aliases:

# gcc compilation aliases: c89, c99, debug mode, release mode
alias gd='gcc -ansi -pedantic-errors -Wall -Wextra -g'
alias gc='gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3'
alias gd9='gcc -std=c99 -pedantic-errors -Wall -Wextra -g'
alias gc9=gcc -std=c99 -pedantic-errors -Wall -Wextra -DNDEBUG -O3'

#Valgrind alias
alias vlg='valgrind --leak-check=yes --trackorigins=yes'


for any suggestions, improvments, etc:
assafain@gmail.com

© Assaf Ainhoren Tesler
