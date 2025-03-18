#ifndef __PAGELIB_H__
#define __PAGELIB_H__

#include"DirScanner.h"
#include"WordSegmentation.h"
#include"DictProducer.h"
#include<iostream>
#include<vector>
#include<unordered_map>
#include<utility>
#include<set>
#include<string>

using std::string;
using std::set;
using std::unordered_map;
using std::vector;
using std::pair;


namespace SearchEngine
{
class Configuration;
struct RSSItem
{
    string _title;
    string _link;
    string _description;
};

class Compare
{
    bool operator()(const pair<int,double> & lhs, const pair<int,double> & rhs)
    {
        return lhs.first < rhs.first;
    }
};

class Pagelib
{
public:
    Pagelib();
    ~Pagelib()
    {}
private:
    void create();//创建RSS对象
    void store();
    void handleInvertIndex();//处理倒排索引
    void PageDeDuplication();//处理网页去重
private:
    int _DocicNum;//去重后文章数量
    vector<RSSItem> _rss;//解析后的rss
    Configuration * _config;
    DictProducer _dict;//文件路径
    WordSegmentation &_jieba;//分词对象
    unordered_map<string,set<pair<int,double>>> _invertIndex;//倒排索引
};
}
#endif
