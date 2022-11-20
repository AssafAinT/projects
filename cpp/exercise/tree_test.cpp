#include <iostream>
#include <dirent.h> // readdir

#include "tree.hpp"
using namespace std;
using namespace ilrd;

int main(int argc, char **argv)
{
    
    const char *path = "/home/assaf/git/cpp/exercise/testitout";
    Tree *tree = new Tree(path); 
    tree->Print();

    delete tree;
    
    // DIR *folder;
    // struct dirent *entry;
    // int files = 0;

    // folder = opendir("/home/assaf/git/cpp/exercise/");
    // if(folder == NULL)
    // {
    //     perror("Unable to read directory");
    //     return(1);
    // }

    // while( (entry=readdir(folder)) )
    // {
    //     files++;
    //     printf("File %3d: %s\n",
    //             files,
    //             entry->d_name
    //           );
    // }

    // closedir(folder);


}