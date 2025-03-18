#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include"../DisallowCopyAssign.h"

#include<unordered_map>
#include<set>
#include<utility>
#include<string>
#include<vector>

using std::unordered_map;
using std::set;
using std::vector;
using std::pair;
using std::string;

namespace SearchEngine
{
class Dictionary
{
public:
    static Dictionary *getInstance();
    void destroy();
    vector<pair<string,int>> doQuery(const string &key);

    void handleWord(const string &input,vector<string> &words);//中英文字符按块切分
    size_t nBytesCode(const char ch);//求取一个字符占据的字节数
    size_t length(const string &str);//求取一个字符串的字符长度
    int editDistance(const string &lhs,const string &rhs);//中英文通用的最小距离编辑算法
    int triple_min(const int &a,const int &b,const int &c);
    
    void loadDict();
    void loadIndex();
    void loadIdMap();

    ~Dictionary();

private:
    DISALLOWCOPYANDASSIGN(Dictionary);
    Dictionary() = default;
private:
    static Dictionary *_pdict;
    unordered_map<string,int> _dict;//单词+所有文章中频率
    unordered_map<string,set<int>> _index;//字+单词id集合
    unordered_map<int,string> _idMap;//单词id+单词
};
}
#endif
