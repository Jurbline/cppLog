#include"../include/DirScanner.h"
#include <iostream>

namespace SearchEngine
{
DirScanner::DirScanner()
{

}
DirScanner::~DirScanner()
{

}
void DirScanner::operator()(const string &dirname)
{
    traverse(dirname);
}
vector<string> &DirScanner::getFiles()
{
    return _files;
}
void DirScanner::traverse(const string &dirname)
{
    DIR *dir;
    struct dirent* direntptr;
    dir = opendir(dirname.c_str());
    if(!dir)
    {
        cout << "this" << dirname.c_str() << "is nullptr" << endl;
        return;
    }
    while((direntptr = readdir(dir)) != nullptr)
    {
        if(strncmp(direntptr->d_name,".",1) != 0 
           && strncmp(direntptr->d_name,"..",2) != 0)
        {
            _files.push_back(dirname + "/" +  direntptr->d_name);
        }
    }
    closedir(dir);
}
}//end of namespace
