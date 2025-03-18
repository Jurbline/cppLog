#ifndef __DIRSCANNER_H__
#define __DIRSCANNER_H__

#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<iostream>
#include<vector>

using std::endl;
using std::cout;
using std::string;
using std::vector;

namespace SearchEngine
{

class DirScanner
{
public:
    DirScanner();
    ~DirScanner();
    void operator()(const string &dirname);
    vector<string> &getFiles();
    void traverse(const string &dirname);
private:
    vector<string> _files;//存储路径
};

}//end of namespace
#endif
