#ifndef __SE_TASK_H__
#define __SE_TASK_H__

#include"../Reactor/TcpConnection.h"
#include"../KeyRecommander/KeyRecommander.h"
#include"../WebPageSearcher/WebPageSearcher.h"

namespace SearchEngine
{

using MYMAP = unordered_map<std::pair<string, unsigned short>,
                            std::pair<int,vector<string>>>;
class CalculateTask
{
public:
    CalculateTask(const string &msg,
                  const TcpConnectionPtr &con,
                  KeyRecommander &key,
                  WebPageSearcher &web,
                  MYMAP &store)
    :_msg(msg)
    ,_con(con)
    ,_key(key)
    ,_web(web)
    ,_Store(store)
    {}
    void wordSearcher();
    void pageSearcher();
    void nextPageSearcher();
    void process();

private:
    string _msg;//从客户端返回的数据，也就是要查询的数据
    TcpConnectionPtr _con;//Tcp连接的对象
    KeyRecommander &_key;//关键字对象的引用
    WebPageSearcher &_web;//网页搜索对象的引用
    MYMAP &_Store;//存储的是客户端的ip，端口号，
                  //当前已显示到结果的索引，该搜索对应的所有原始结果（未分页的完整集合）
    // 用户搜索"分布式系统"得到5条结果
    //_Store[{"192.168.1.100", 54321}] = 
    //{3,{"结果1", "结果2", "结果3", "结果4", "结果5"}};已显示0-2条，下次从3开始，和所有结果
};
}
#endif
