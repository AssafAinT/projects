#include <iostream> //std::cout
#include <list> // std::list
#include <dirent.h> // readdir
#include <exception>
#include <cerrno>
#include <unistd.h>
#include <cstring>
#include "tree.hpp"
#define REST "\033[0m"
#define BLUE "\033[1;34m"
namespace ilrd
{

class Directory : public IFile
{
    public:
    Directory(std::string path = "", size_t offset = 0, std::string directory = "");
    virtual ~Directory();
    void Print();
    
    private:
    size_t m_offset;
    std::string m_path;
    std::string directory_name;
    std::list<IFile *> Containers;
    Directory(const Directory& other);
};
class File : public IFile
{
    public:
    File(std::string filename = "", size_t offset = 0);
    virtual ~File();
    void Print();
    
    private:
    size_t m_offset;
    std::string m_file;
};

void Directory::Print()
{ 
    for ( size_t i = 0; i < m_offset; ++i)
    {
        std::cout << "│  ";   
    }
    
    std::cout << "├── "  << directory_name << std::endl;
    for (std::list<IFile *>::iterator it=Containers.begin(); it != Containers.end(); ++it)
    {

        (*it)->Print(); 
    }

}

void File::Print()
{
    for ( size_t i = 0; i < m_offset; ++i)
    {
        std::cout << "|  ";   
    }
    std::cout<< "└── "<< m_file << std::endl; 
}
Directory::Directory(std::string path, size_t offset, std::string directory) :
 m_offset(offset), m_path(path), directory_name(directory)
{
    DIR *dir = opendir(m_path.c_str());
    struct dirent *entry;
    if(dir == NULL)
    {
        perror("opendir");
        std::cout<< "Unable to read directory"<< std::endl;
        std::cout << errno << std::endl;
    }
    while( (entry=readdir(dir)) )
    {
        if (0 == memcmp(entry->d_name,".", 1))
        {
            continue;
        }
        if (entry->d_type == DT_REG)
        {
            Containers.push_back(new File(entry->d_name, m_offset + 1));
        }
        if (entry->d_type == DT_DIR)
        {
            Containers.push_back(new Directory(m_path + "/" + entry->d_name, m_offset + 1, entry->d_name));
        }
    }   
    closedir(dir); 
}
File::File(std::string filename, size_t offset) : m_offset(offset), m_file(filename)
{
//
}
void Tree::Print()
{
    root->Print();
}
Tree::Tree(const char *path) : root(new Directory(path, 0, path))
{ 
       
}
Tree::~Tree()
{
    delete root;
}
Directory::~Directory() 
{
    for (std::list<IFile *>::iterator it=Containers.begin(); it != Containers.end(); ++it)
    {
        delete *it; 
    }
    Containers.clear();
}
File::~File()
{
   
}
}
