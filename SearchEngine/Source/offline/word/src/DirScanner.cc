#include <iostream>
#include "../include/DirScanner.h"
using std::cout;
using std::endl;
using std::string;
using std::vector;

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
    DIR* dir;
    struct dirent* direntptr;

    dir = opendir(dirname.c_str());
    if(!dir)
    {
        cout << "The file" << dirname.c_str() << "is not exist!!!" << endl;
        return;
    }
    while((direntptr = readdir(dir)) != nullptr)
    {
       if(strncmp(direntptr->d_name,".",1)!= 0//排除./和../文件夹 
          && strncmp(direntptr->d_name,"..",2)!= 0)
       {
           _files.push_back(dirname + "/" + direntptr->d_name);//存储文件路径
       }
    }
    closedir(dir);
}
}//end of namespace
