#ifndef __DIRSCANNER_H__
#define __DIRSCANNER_H__

#include<sys/types.h>
#include<dirent.h>
#include<iostream>
#include<vector>
#include<string.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

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
    vector<string> _files;
};
}
#endif
