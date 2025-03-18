#ifndef __SE_WEBPAGE_H__
#define __SE_WEBPAGE_H__

#include"cppjieba/Simhasher.hpp"
#include<string>
#include<map>
#include<vector>
#include<set>

using std::set;
using std::map;
using std::vector;
using std::string;

namespace SearchEngine
{
class Configuration;
class WordSegmentation;

class webPage
{
public:
    webPage();
    webPage(string &doc,WordSegmentation *jieba,simhash::Simhasher *sim);
    ~webPage();

    int getDocid();
    string getTile();
    string getUrl();
    string summary(const vector<string> &queryWord);
    map<string,int> &getWordsMap();

private:
    //该函数中用到KMP
    void processDoc(const string & doc);
    void calaTopK(vector<string> & wordsVec,int k);
private:
    const static int TOP_NUM = 20;
    int _docid;//文章id
    string _docTitle;//文章标题
    string _docUrl;//文章链接
    string _docContent;//文章内容
    string _docSummary;//文章摘要
    vector<string> _topWords;//热刺
    map<string,int> _wordsMap;
    WordSegmentation *_jieba;//结巴指针
    simhash::Simhasher *_sim;//simhash指针
};
}
#endif
