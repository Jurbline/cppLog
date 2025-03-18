#include <iostream>
#include"../../include/KeyRecommander/KeyRecommander.h"
#include<string.h>
namespace SearchEngine
{
vector<string> KeyRecommander::doQuery()
{
    //candit存储查询之后获取的结果
    vector<std::pair<string,int>> candit = _pdict->doQuery(_sought);
    vector<string> finalResult;

    if(!candit.size())
    {
        return vector<string>();
    }
    Res myResult;
    for(auto &elem : candit)
    {
        if(_pdict->nBytesCode(elem.first[0]) == 3)//中文词组
        {
            //插入优先队列
            insertPrique(elem,myResult);
        }
    }
    //最终结果放入finalResult中，只有五个候选词
    //然后将优先队列清空
    initFinalResult(finalResult);
    //英文也做同样的操作，将优先级最高的五个存起来放入finalResult中
    for(auto &elem : candit)
    {
        if(_pdict->nBytesCode(elem.first[0]) == 1)//英文词组
        {
            insertPrique(elem,myResult);
        }
    }
    initFinalResult(finalResult);
    eraseFinalResult(finalResult);
    return finalResult;
}
void KeyRecommander::insertPrique(std::pair<string,int> &elem ,Res &myResult)
{
    bzero(&myResult,sizeof(myResult));//设置为0
    myResult._dist = _pdict->editDistance(_sought,elem.first);//获取编辑距离
    myResult._freq = elem.second;
    myResult._word = elem.first;
    _prique.push(myResult);
}
void KeyRecommander::initFinalResult(vector<string> &finalResult)
{
    int i = 0;
    while(!_prique.empty() && i++ < 5)
    {
        //只要_prique不为空，将优先级最高的五个候选词放在vector中存起来
        finalResult.emplace_back(_prique.top()._word);
        _prique.pop();
    }
    //清空_prique
    while(_prique.size())
    {
        _prique.pop();
    }
}
void eraseFinalResult(vector<string> &finalResult)
{
    size_t resultSize = finalResult.size();
    if(resultSize > 5)
    {
        auto it = finalResult.begin();
        finalResult.erase(it + 3,it + 5);
        finalResult.erase(it + 6,it + 8);
    }
}
bool KeyRecommander::myCompare::operator()(const CandidateResult & lhs
                                           , const CandidateResult &rhs) const
{
    //首先按照最小编辑距离进行比较,最小编辑距离越小，说明越接近查询的结果
    if(lhs._dist > rhs._dist)//距离更小的优先级更高
    {
        return true;
    }
    else if(lhs._dist == rhs._dist && lhs._freq < rhs._freq)//频率高优先级高
    {
        return true;
    }
    else if(lhs._dist == rhs._dist && lhs._freq == rhs._freq)
    {
        //英文字母顺序更小的优先级越高
        if(strcmp(lhs._word.c_str(),rhs._word.c_str()) > 0)
        {
            //例如a和b，a < b则strcmp返回小于0
            return true;
        }else{
            return false;//如果返回值小于 0，则表示 lhs 小于 rhs(a > A)
        }
    }
    else
    {
        return false;
    }
}
}
