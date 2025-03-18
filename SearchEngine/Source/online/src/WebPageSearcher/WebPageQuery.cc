#include <iostream>
#include"../../include/WebPageSearcher/WebPageQuery.h"
#include<nlohmann/json.hpp>
#include<algorithm>
#include<iterator>
#include<math.h>
#include<sstream>
#include<fstream>
using std::istringstream;
using std::ifstream;
using std::inserter;
using std::set_intersection;
using std::make_pair;

namespace SearchEngine
{
WebPageQuery * WebPageQuery::_pQuery = nullptr;

WebPageQuery::WebPageQuery()
:_jieba()
,_sim(DICT_PATH,HMM_PATH,IDF_PATH,STOP_WORD_PATH)
{
    loadLibary();
}
WebPageQuery::~WebPageQuery()
{

}

vector<string> WebPageQuery::doQuery(const string & str)//用于执行查询，返回结果，KeyRecommander
{
    //cppjieba进行分词，分词后的结果存在results中
    vector<string> results = _jieba(str);
    size_t judeg = 0;
    //遍历容器，并在倒排索引表中查询
    for(auto & word : results)
    {
        auto it = _inverIndexTable.find(word);
        if(it == _inverIndexTable.end())
        {
            ++judeg;
        }
    }
    //judeg 的作用是记录分词结果中有多少个词语没有出现在倒排索引表中
    //如果所有词语都不在倒排索引表中，函数会提前返回一个空的结果，避免后续不必要的计算
    if(judeg == results.size())
    {
        return vector<string>();
    }
    //获取待查询结果的权重值，并准备作为基准向量
    vector<double> Base = getQueryWordsWeightVector(results);


    //余弦相似度进行排序
    unordered_map<int,vector<double>> resultVec;
    if(executeQuery(results,resultVec))//如果返回true说明查询到结果，并且存储在resultVec
                                       //如果返回false说明没查询到，也就不会走下面函数了
    {
        double X = 0.0;
        for(double x : Base)
        {
            X += x * x;//计算基准向量的模长 X
        }
        X = sqrt(X);
        vector<std::pair<int,double>> web_sort;
        //夹角越小优先级越高
        for(auto it = resultVec.begin();it != resultVec.end(); ++it)
        {
            int docid = it->first;
            double XY = 0.0,Y= 0.0;//计算点积 XY，计算文档向量的模长 Y
            for(size_t i = 0;i < it->second.size(); ++i)
            {
                XY += 1.0 * it->second[i] * Base[i];
                Y += 1.0 * it->second[i] * it->second[i];
            }
            Y = sqrt(Y);
            //计算余弦相似度 COS
            double COS = 1.0 * XY /(X * Y);
            web_sort.push_back(std::make_pair(docid,COS));
        }
        sort(web_sort.begin(),web_sort.end(),ComPair);//余弦相似度大的排在前面

        vector<int> web_fin;//存放排序之后的网页
                            
        for(auto it : web_sort)
        {
            web_fin.push_back(it.first);//将排序之后的文章id存放在web_fin中
        }
        size_t sz = web_fin.size();
        if(sz < 3)
        {
            //小于3篇就不管
        }
        else if(sz >= 3 && sz < 6)
        {
            web_fin.resize(3);//大于三篇按照3篇
        }
        else if(sz >= 6 && sz < 9)
        {
            web_fin.resize(6);
        }
        else if(sz >= 9 && sz < 12)
        {
            web_fin.resize(9);
        }
        else
        {
            web_fin.resize(12);//最多存12篇
        }
        //生成 JSON 格式的结果
        vector<string> rs = create_Json(web_fin,results);//给定文章id列表和查询词
        return rs;
    }
    else
    {
        return vector<string>();
    }
}

vector<double> WebPageQuery::getQueryWordsWeightVector(vector<string> & queryWords)//TF-IDF计算查询词的权重值
{
    vector<double> results;//归一化权重w'
    unordered_map<string,int> tf;//存储每个查询词的词频
    double N = _pageLib.size() + 1;//避免除0
    for(string & word : queryWords)
    {
        int & isExit = tf[word];
        if(isExit)
        {
            ++isExit;
        }
        else
        {
            isExit = 1;
        }
    }
    vector<double> tmp;//w1 w2 w3
    for(string & word : queryWords)
    {
        auto it = _inverIndexTable[word];
        //DF表示某个词在所有文章中出现的次数,即：包含该词语的文档数量
        double DF = it.size();
		//IDF表示逆文档频率
        double IDF = log(N/(DF + 1)) / log(2);
		//某个词在文章中出现的次数
        double TF = tf[word];
		//每个词的权重，w = TF * IDF;
        double w = 1.0 * TF * IDF;
		//存放每个词的权重到tmp中存起来
        tmp.push_back(w);
    }
    double Allw = 0.0;
    for(double w : tmp)
    {
        AllW += w * w;
    }
    AllW = sqrt(AllW);
    //归一化处理，并将结果存放在vector<double> results
    //中，然后返回
    for(double w : tmp)
    {
        double FinW = w / AllW;
        results.push_back(FinW);
    }
    return results;
}
//resultVec是传出参数，存放的是文章id与权重，其文章id是包含带查询词的文章id
//也就是最终可以展示给用户的文章
bool WebPageQuery::executeQuery(const vector<string> &queryWords,
                  unordered_map<int,vector<double>> & resultVec)//执行查询
{   
    vector<set<int>> existWed;
    bool flag = false;
    //将待查询短语分词后的每个词对应的文章id都存放在tmp中
    //然后将所有查询词的文章id都放在existWed中
    for(size_t i = 0; i < queryWords.size(); ++i)
    {
        string word = queryWords[i];
        auto it = _inverIndexTable[word];//set<pair<int,double>>
        set<int> tmp;
        for(auto it2 = it.begin();it2 != it.end(); ++it2)
        {
            int docid = it2->first;
            tmp.insert(docid);//存储文章id
            flag = true;
        }
        existWed.push_back(tmp);//将存储文章id的集合set放在vector中
    }
    //flag == flase说明待查询词不在倒排索引表中，也就是待查询词
    //不存在，从来没有在文章出现过（生僻词或者这些字组成的短语）
    if(flag == false)
    {
        return false;
    }
    //将待查询词分词后，将所有的分词的结果取交集
    //得到文章id就是分出的词出现的文章
    
    //逐步计算多个集合的交集，最终得到一个包含所有查询词（分词后的词语）
    //共同存在的文章 ID 的集合 SameWeb
    set<int> SameWeb = existWed[0];//初始化为第一个集合
    for(size_t i = 0;i < existWed.size(); ++i)//此处可以从1开始，少一次计算
    {
        set<int> tmp;
        //求交集的函数 set_intersection() 
        //求集合差的函数 set_difference() 
        //和合并两个集合的函数 set_union()
        set_intersection(SameWeb.begin(),SameWeb.end()//第一个有序区间
                         ,existWed[i].begin(),existWed[i].end()//第二个有序区间
                         inserter(tmp,tmp.end()));//输出插入到tmp中
        SameWeb.swap(tmp);
    }
    if(!SameWeb.size())//取交集之后没有文章
    {
        return false;
    }


    //SameWeb是包含待查询词的set集合，该集合
    //包含所有待查询词的文章id


    //为每个包含所有查询词的文章（文档）构建一个权重向量，
    //并将其存储在 resultVec 中。具体来说，
    //它遍历所有符合条件的文章 ID（存储在 SameWeb 中），
    //然后为每篇文章生成一个权重向量，该向量表示查询词在该文章中的权重
    for(auto it = SameWeb.begin(); it != SameWeb.end();++it)
    {
        int docid = *it;
        //it2的类型其实就是vector<double>，存放所有单词的权重
        auto & it2 = resultVec[docid];
        for(string word : queryWords)
        {
            auto it3 = _inverIndexTable[word];//unordered_map<string, set<std::pair<int, double>>>
                                              //词语 包含该词的文章 ID 及其权重
            for(auto it4 = it3.begin();it4 != it3.end(); ++it4)
            {
                //找到文章id，说明相似的文章，就将权重存起来
                //放在it2中存起来
                if(it4->first == docid)
                {
                    it2.push_back(it4->second);
                    break;
                }
            }
        }
    }
    return true;
    //假设查询词为 ["我", "爱", "武汉"]，某篇文章 docid=1 的权重向量为 [0.5, 0.3, 0.8]，表示
    //resultVec = {1, [0.5, 0.3, 0.8]}
}
//组装网页id 标题 链接 摘要，为了发送给用户
vector<string> WebPageQuery::create_Json(vector<int> &docidVec,
                           const vector<string> &queryWords)
{
    vector<string> result;
    string Line = "<---------------------------------------------------->\n";
    size_t id = 0;
    for(auto & docid : docidVec)
    {
        string res;
        string Summary = _pageLib[docid].Summary(queryWords);//摘要
        string Title = _pageLib[docid].getTile();
        string Url = _pageLib[docid].getUrl();
        char buf[65536] = {0};
        //sprintf：将文章信息格式化为字符串，存储在 buf 中
        //%ld：长整型占位符，%s：字符串占位符
        sprintf(buf,"%s所查询网页:%ld\n\t标题:%s\n\t链接:%s\n\t摘要:%s。\n",
                Line.c_str(),++id,Title.c_str(),Url.c_str(),Summary.c_str());
        res += buf;
        result.push_back(res);
        memset(buf,0,sizeof(buf));
    }
    return result;
}
void WebPageQuery::loadLibary()//loadLibrary加载库文件
{
    //加载偏移库，存储在容器中
    ifstream ifsOff;
    ifsOff.open("../offline/page/data/offset.dat");
    cout << "(WebPageQuery): loading offset.dat..." << endl;

    string line;
    while(ifsOff >> line)
    {
        int id = atoi(line.c_str());
        int begin;
        int end;
        ifsOff >> begin;
        ifsOff >> end;
        _offsetLib[id] = std::make_pair(begin,end);//unordered_map<int, pair<int, int>>
    }

    //加载网页库，存在容器中
    ifstream ifsPage;
    ifsPage.open("../offline/page/data/ripepage.dat");
    cout << "(WebPageQuery): loading ripepage.dat" << endl;

    for(auto it = _offsetLib.begin();it != _offsetLib.end(); ++it)
    {
        int begin = it->second.first();
        const size_t size = it->second.second;
        char buf[65536] = {0};
        string line;
        ifsPage.seekg(begin);
        ifsPage.read(buf,size);
        string doc = buf;
        _pageLib.insert(std::make_pair(it->first,webPage(doc,&_jieba,&_sim)));
    }

    //加载倒排索引库，存放在容器中
    ifstream ifsIndex;
    ifsIndex.open("../offline/page/data/invertIndex.dat");
    cout << "(WebPageQuery): loading invertIndex.dat ..." << endl; 

    string line2;
    string word;
    while(getline(ifsIndex,line2))
    {
        istringstream iss(line2);
        iss >> word;
        int docid;
        while(iss >> docid)
        {
            double w;
            iss >> w;
            _inverIndexTable[word].insert(std::make_pair(docid,w));
        }
    }
    ifsOff.close();
    ifsPage.close();
    ifsIndex.close();
}
};
