#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__

#include"DirScanner.h"
#include"WordSegmentation.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<string>
#include<set>

#define CHSIZE 3

using std::istringstream;
using std::ofstream;
using std::ifstream;
using std::unordered_map;
using std::pair;
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::set;

namespace SearchEngine
{

class WordSegmentation;
class DictProducer
{
public:
    DictProducer();
    ~DictProducer();
    void buildEnDict();
    void buildCnDict();
    void store();

private:
    void insertIndex(const string &elem,size_t id);
    void processLine(string &line);
    void insertEnindex(const string &elem,size_t id);
    void openFile(ifstream &ifs,const string &fileName);
    void inputFile(ofstream &ofs,const string &fileName);
private:
    vector<string> _file;//路径
    unordered_map<string,int> _dict;//词频
    unordered_map<string,set<int>> _index;//单词+id
    unordered_map<int,string> _idMap;//序号+单词本身
    WordSegmentation _jieba;//cppjieba
    DirScanner _dir;
};
}
#endif
