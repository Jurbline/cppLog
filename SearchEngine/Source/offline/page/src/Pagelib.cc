#include <iostream>
#include"../include/Pagelib.h"
#include"../include/Configuration.h"
#include"../include/tinyxml2.h"
#include"../include/simhash/Simhasher.hpp"

#include<utility>
#include<map>
#include<regex>
#include<math.h>
#include<fstream>

using std::ofstream;
using std::regex;
using std::map; 
using std::cout;
using std::endl;
using namespace tinyxml2;

namespace SearchEngine
{
Pagelib::Pagelib()
:_config(Configuration::getInstance("conf/page.conf"))
,_jieba(_dict.getJieba())
{
    cout << endl << "Analyze RSS files now..." << endl << endl;
    create();//解析xml文件
    cout << endl << "Analyze RSS files success!!!" << endl << endl;
    cout << "Page deduplication now..." << endl << endl;
    PageDeDuplication();//网页去重
    cout << endl << "Page deduplication success!!!" << endl;
    cout << endl << "Handling Invert Index now..." << endl << endl;
    handleInvertIndex();//倒排索引
    cout << endl << "Handling Invert Index success!!!" << endl << endl;
    cout << "Storing the files ..." << endl << endl;
    store();//存储
    cout << "Successful stored!!!" << endl;

}
void Pagelib::create()
{
    DirScanner dir;
    dir(_config->getConfigs().find("XMLDIR")->second);
    for(string &fileName : dir.getFiles())
    {
        XMLDocument doc;
        doc.LoadFile(fileName.c_str());
        if(doc.ErrorID())
        {
            std::cerr << "LoadFile" << fileName.c_str() << "error!!!" << endl;
            return;
        }        
        //xml组成由rss->channel->item->*，定位到每个item类下
        XMLElement *itemNode = 
            doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");

            
        while(itemNode)
        {
            RSSItem rssItem;
            //去除多余"<xxx>"中的内容
            regex reg("<[^>]+>");//通用正则表达式
                                 
            if(itemNode->FirstChildElement("title"))
            {
                string title = itemNode->FirstChildElement("title")->GetText();
                title = regex_replace(title,reg,"");
                rssItem._title = title;
            }
            else
            {
                rssItem._title = "No title in this text!!!";
            }

            string link = itemNode->FirstChildElement("link")->GetText();
            rssItem._link = link;

            if(itemNode->FirstChildElement("description"))
            {
                string description = itemNode->FirstChildElement("description")->GetText();
                description = regex_replace(description,reg,"");
                rssItem._description = description;
            }
            else
            {
                rssItem._description = "No description in this text!!!";
            }

            _rss.push_back(rssItem);

            itemNode = itemNode->NextSiblingElement("item");
            
        }
    }
    
}
void Pagelib::store()
{
    ofstream ofs("data/ripepage.dat");//存放网页库
    if(!ofs)
    {
        perror("output page error!!!");
        return;
    }
    ofstream ofs1("data/offset.dat");//存放网页偏移库
    if(!ofs1)
    {
        perror("output offset error!!!");
        return;
    }

    for(size_t i = 0;i != _rss.size(); ++i)
    {
        size_t idx = i + 1;//让文章ID从1开始
        ofs1 << idx << " ";//文章id
        size_t beginpos = ofs.tellp();//定位文章起始位置
        ofs1 << beginpos << " ";//网页偏移库：文章id-起始位置-文章长度
        ofs << "<doc>" << endl;
        ofs << "\t<docid>" << i + 1 << "</docid>" << endl;//"\t"表示Tab
        ofs << "\t<title>" << _rss[i]._title << "</title>" << endl;
        ofs << "\t<url>" << _rss[i]._link << "</url>" << endl;
        ofs << "\t<description>" << _rss[i]._description << "</description>" << endl;
        ofs << "</doc>" << endl;
        size_t endpos = ofs.tellp();
        size_t len = endpos - beginpos;//文章长度（包括<xxx>）
        ofs << len << "\n";
    }
    cout << "Successful store the pagelib and offset!!!" << endl;
    ofstream ofs2;//倒排索引库
    ofs2.open("data/invertIndex.dat");
    for(auto &it : _invertIndex)
    {
        ofs2 << it.first << " ";
        for(auto it2 = it.second.begin();it2 != it.second.end(); ++it2)
        {
            ofs2 << it2->first << " " << it2->second << " ";
        }
        ofs2 << endl;
    }
    cout << "Successful store invertindex!!!" << endl;
    ofs.close();
    ofs1.close();
    ofs2.close();

}
void Pagelib::handleInvertIndex()
{
    unordered_map<string,unordered_map<int,double>> tf;//每个词在每篇文章中的词频
    int i = 0;
    //先将文章中的描述信息分词，然后根据（单词，文章id，词频）存入tf中
    for(auto it = _rss.begin();it != _rss.end();++it)
    {
        //让docid从1开始
        int docid = ++i;
        string doc = it->_description;
        vector<string> results = _jieba(doc);
        for(string & word : results)
        {
            auto & isExist = tf[word];
            if(isExist[docid])
            {
                ++isExist[docid];
            }
            else
            {
                isExist[docid] = 1;
            }
        }
    }
    //计算单词在每篇文章中的权重，并将其存入倒排索引表
    //此处使用TF-IDF方法
    unordered_map<int,double> docW;//存放 w1^2 + w2^2 + ...
    for(auto it = tf.begin(); it != tf.end(); ++it)
    {
        string word = it->first;
        size_t DF = it->second.size();// DF 存放的是包含该单词(word)的文章数量
        for(auto num = it->second.begin(); num != it->second.end(); ++num)//遍历单词对应的文章id与词频
        {
            int docid = num->first;//文章id
            int TF = num->second;//词频
            double IDF = log(1.0 * _DocicNum /(DF + 1))/log(2);//逆文档频率，表明该词对该文章的重要性
            double w = TF * IDF;//单词权重
            num->second = w;
            docW[docid] += w * w;//归一化的中间结果，单词对于文章的重要程度
                                 //计算公式：w'= w / sqrt(w1^2 + w2^2 + ...)
        }
    }
        //代码归一化
    for(auto it = tf.begin(); it != tf.end(); ++it)
    {
        string word = it->first;
        for(auto elem = it->second.begin(); elem != it->second.end(); ++elem)
        {
            int docid = elem->first;
            double sumW2 = docW[docid];//文章权重的平方和
            double w = elem->second;//（对应tf中的词频，这边已经是TF * IDF后的结果）单词的TF-IDF权重
            double FinW= w / sqrt(sumW2);//归一化权重
            _invertIndex[word].insert(std::make_pair(docid,FinW));
        }
    }
}
void Pagelib::PageDeDuplication()
{
    size_t topN = 20;//权重数量，即比较相似的词语数
    //利用simhash进行去重
    simhash::Simhasher simhasher(DICT_PATH,HMM_PATH,IDF_PATH,STOP_WORD_PATH);
    vector<pair<int,uint64_t>> Sim;
    
    cout <<  "去重前文章数目为：" << _rss.size() << endl;
    for(size_t i = 0;i < _rss.size() ; ++i)
    {
        uint64_t u = 0;
        simhasher.make(_rss[i]._description,topN,u);//根据前topN个权重计算降为后的hash值
        //结果hash值为u,存入Sim中
        Sim.push_back(std::make_pair(i,u));//make_pair会自动识别类型，无需手动输入
    }

    set<int> tmp;
    //以一个文章为基点，遍历所有文章，将文章的Simhash值进行两两比较（海明距离）
    //将描述信息更短的文章id存在tmp中，后面遍历Sim时，可以根据tmp中存放的文章id
    //删除对应Sim内的文章
    //这样便可以去重
    for(size_t it = 0 ; it < Sim.size() ; ++it)
    {
        int id1 = Sim[it].first;
        int sz1 = _rss[id1]._description.size();
        for(size_t it2 = (it + 1); it2 < Sim.size(); ++it2)
        {
            if(simhash::Simhasher::isEqual(Sim[it].second,Sim[it2].second))
            {
                int sz2 = _rss[Sim[it2].first]._description.size();
                if(sz1 >= sz2)
                {
                    tmp.insert(Sim[it2].first);
                }
                else
                {
                    tmp.insert(id1);
                    break;
                }
            }
        }
    }
    for(auto num : tmp)
    {
        num -= 0;
        int i = 0;
        for(auto it = _rss.begin();it != _rss.end();++it,++i)
        {
            if(num == i)
            {
                _rss.erase(it);//从rss中删除文章
                break;
            }
        }
    }
    _DocicNum = _rss.size();

    cout << "去重成功！" << endl;
    cout << "去重后文章数目：" << _rss.size() << endl;
}
}
