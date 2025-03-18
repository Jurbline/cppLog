#include <iostream>
#include"../../include/WebPageSearcher/WebPage.h"
#include"../../include/WebPageSearcher/KMP.h"
#include"../../include/WebPageSearcher/WordSegmentation.h"

#include<string>

namespace SearchEngine
{
webPage::webPage()
:_jieba()
,_sim()
{
    
}
webPage::webPage(string &doc,WordSegmentation *jieba,simhash::Simhasher *sim)
:_jieba(jieba)
,_sim(sim)
{
    processDoc(doc);
}
webPage::~webPage()
{

}

int webPage::getDocid()
{
    return _docid;
}
string webPage::getTile()
{
    if(_docTitle.size())
    {
        return _docTitle;
    }
    else
    {
        return nullptr;
    }
}
string webPage::getUrl()
{
    if(_docUrl.size())
    {
        return _docUrl;
    }
    else
    {
        return nullptr;
    }
}
string webPage::summary(const vector<string> &queryWord)
{
    //最终只是将_docContent中的第一句展示出来了
    //待优化成：根据待查找此，分成之后的词 前后各找10个字组合在一起
    //形成摘要
    KMP kmp;
    set<int> Pos;
    for(auto word : queryWord)
    {
        Pos.insert(_docContent.find(word));
    }
    vector<int> Post;
    for(auto num : Pos)//这里没用处
    {
        Post.push_back(num);
    }
    int pos = kmp(_docContent,"。");//使用 KMP 算法在 _docContent 中查找第一个句号（"。"）的位置
    return _docContent.substr(0,pos);//使用 substr 方法提取 _docContent 中从开头到第一个句号之间的子字符串。
                                     //返回这个子字符串作为摘要
}
map<string,int> &webPage::getWordsMap()
{
    string str = _docContent;
    vector<string> results = _jieba->operator()(str);

    for(string &word : results)
    {
        int & isExit = _wordsMap[word];//isExist（检查是否存在）
        if(isExit)
        {
            ++isExit;
        }
        else
        {
            isExit = 1;
        }
    }
    return _wordMap;
}

//本函数使用KMP算法，从字符串中寻找子串，然后获取对应的
//信息，比如：文章id、标题、链接等
void webPage::processDoc(const string & doc)
{
    //使用 KMP 算法找到 <docid> 标记在 doc 中的位置，并加上标记的长度，得到文档 ID 的起始位置
    //使用 KMP 算法找到 </docid> 标记在 doc 中的位置，得到文档 ID 的结束位置
    //从 doc 中提取出文档 ID 的子字符串，并将其转换为整数，存储到 _docid 成员变量中
    KMP kmp;
    string doc1 = "<docid>";
    string doc2 = "</docid>";
    int dm1 = kmp(doc,doc1) + doc.size();//这里kmp找到的是包括<docid>在内的起始位置，为了得到
                                         //docid，则需要加上"<docid>"的长度就是docid的起始位置
    int dm2 = kmp(doc,doc2);
    //atoi()的参数是 const char* 
    //,因此对于一个字符串str我们必须调用 c_str()的方法把这个string转换
    //成 const char*类型的,而stoi()的参数是const string*,不需要转化为 const char*；
    _docid = atoi(doc.substr(dm1,dm2 - dm1).c_str());

    string t1 = "<title>";
    string t2 = "</title>";
    int tm1 = kmp(doc,t1) + t1.size();
    int tm2 = kmp(doc,t2);
    _docTitle = doc.substr(tm1,tm2 - tm1);

    string u1 = "<url>";
    string u2 = "</url>";
    int um1 = kmp(doc, u1) + u1.size();
    int um2 = kmp(doc, u2);
    _docUrl = doc.substr(um1, um2 - um1);

    string d1 = "<description>";
    string d2 = "</description>";
    int dem1 = kmp(doc, d1) + d1.size();
    int dem2 = kmp(doc, d2);
    _docContent = doc.substr(dem1, dem2 - dem1);
}


void webPage::calaTopK(vector<string> & wordsVec,int k)
{
    vector<std::pair<string,double>> res;
    _sim->extract(_docContent,res,k);
    for(auto & it : res)
    {
        wordsVec.push_back(it.first);
    }
}
}
