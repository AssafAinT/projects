#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ext2.h"

int main(void)
{
    int fd = 0;

    fd = open("test.img", 0, 0);
}