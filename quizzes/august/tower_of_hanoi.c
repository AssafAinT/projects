/****************************************************
* tower_of_hanoi                                    *
* Assaf Ainhoren                                    *
* date: 09.08.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
void TowerOfHanoi(int num_of_disks, char from_rod, char to_rod, char aux_rod);

int main(void)
{
    int num_of_disks = 4;
    TowerOfHanoi(num_of_disks, 'A', 'C', 'B');
    return (0);
}
void TowerOfHanoi(int num_of_disks, char from_rod, char to_rod, char aux_rod)
{
    if (1 == num_of_disks)
    {
        printf("Disk %d moved from %c to %c\n", num_of_disks, from_rod, to_rod);
        return;
    }
    TowerOfHanoi(num_of_disks-1, from_rod, aux_rod, to_rod);
    printf("Disk %d moved from %c to %c\n", num_of_disks, from_rod, to_rod);
    TowerOfHanoi(num_of_disks-1, aux_rod, to_rod, from_rod);
}