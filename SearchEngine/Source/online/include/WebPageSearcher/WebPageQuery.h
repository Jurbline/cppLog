#ifndef __SE_WEB_PAGE_QUERY_H__
#define __SE_WEB_PAGE_QUERY_H__
#include"cppjieba/Simhasher.hpp"
#include"WordSegmentation.h"
#include"WebPage.h"
#include<string>
#include<unordered_map>
#include<utility>
#include<vector>
#include<set>

using std::map;
using std::pair;
using std::set;
using std::unordered_map;
using std::string;

namespace SearchEngine
{
//单例模式
class WebPageQuery
{
public:
    static WebPageQuery *getWebQueryPtr()
    {
        if(_pQuery == nullptr)
        {
            _pQuery = new WebPageQuery();
            atexit(destroy);//当程序正常终止时，调用指定的函数destroy
        }
        return _pQuery;
    }
    static void destroy()
    {
        if(_pQuery)
        {
            delete _pQuery;
            _pQuery = nullptr;
        }
    }
    vector<string> doQuery(const string & str);//用于执行查询，返回结果，KeyRecommander
private:
    WebPageQuery();
    ~WebPageQuery();

private:
    void loadLibary();//loadLibrary加载库文件
    vector<double> getQueryWordsWeightVector(vector<string> & queryWords);//计算查询词的权重值
    bool executeQuery(const vector<string> &queryWords,
                      unordered_map<int,vector<double>> & resultVec);//执行查询
    vector<string> create_Json(vector<int> &docidVec,
                               const vector<string> &queryWords);
    string returnNoAnswer();
    static bool ComPair(const std::pair<int,double> &lhs,
                        const std::pair<int,double> &rhs)
    {
        return lhs.second > rhs.second;
    }

private:
    static WebPageQuery *_pQuery;
    WordSegmentation _jieba;
    simhash::Simhasher _sim;
    //此处可用数据库，目前暂未使用（数据量大一次性加载不到内存时需使用）
    //网页库（离线部分）
    unordered_map<int,webPage> _pageLib;
    //偏移库
    unordered_map<int,pair<int,int>> _offsetLib;
    //倒排索引库（短语/词 + 文章id + 权重）
    unordered_map<string,set<std::pair<int,double>>> _inverIndexTable;//_invertIndexTable

};
}
#endif
