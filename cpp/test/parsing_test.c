#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsing.h"

int main(int argc, char* argv[])
{    
    int file_inode = 0, len;
    char buf[0x3401 /*0x3401*/];
    buf[sizeof(buf)-1] = '\0';

    if (argc < 3)
    {
        printf("Enter device name & file name\n");
        exit(1);
    }

    if ((file_inode = Open(argv[1], argv[2])) < 0)
    {
        perror(argv[1]);
        exit(1);
    }

    if ((len = Read(file_inode, buf, sizeof(buf)-1)) > 0)
    {
        strcpy(buf+sizeof(buf)-2, "\n");
        puts(buf);
    }

    printf("%s",buf);

    return 0;
}