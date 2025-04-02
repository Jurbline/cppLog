#include "../../include/SearchEngineServer/CalculateTask.h"
#include "../../include/ProtocolParser.h"
#include "../../include/LRUCache/LRUCache.h"
#include "../../include/LRUCache/CacheManager.h"
#include "../../include/SearchEngineServer/SearchEngineServer.h"
#include "../../include/Reactor/TcpConnection.h"
#include "../../include/Reactor/InetAddress.h"
#include "../../include/MyLog.h"
#include <iostream>

namespace SearchEngine
{

extern thread_local const char *tname;
//用于多线程环境中为不同线程存储独立的状态或标识符（如线程名）
void CalculateTask::wordSearcher()
{
    //先在缓存中进行查找，如果缓存命中，直接获取缓存中的值；否则进行关键字查找
    LRUCache lru = CacheManager::getInstance()->getCache(string(tname));
    vector<string> tmp;
    int ret = lru.get(_key._sought, tmp);

    if(ret == 0)//缓存命中了
    {
        string res;
        res = "[关键字推荐][cache]\n";
        int cnt = 1;
        for(auto& val : tmp)
        {
            res += std::to_string(cnt) + "." + val + " ";
            ++cnt;
        }
        res += "\n";
        _con->sendInLoop(res);
        LogInfo("[LogInfo]word query");
        //写回cache
        CacheManager::getInstance()->getCache(string(tname)).put(_key._sought, tmp);
        //再加到pendinglist上，等待定时器通知主缓存去更新同步
        CacheManager::getInstance()->getCache(string(tname)).addRecord(_key._sought, tmp);
    }
    else
    {
        //没找到，则查询，查询后更新对应
        vector<string> finals = _key.doQuery();
        if(!finals.size())
        {
            _con->sendInLoop("未找到适配关键词，请重新输入。\n");
        }
        else
        {
            string res = "[关键字推荐]\n";
            int cnt = 1;
            for(auto &val : finals)
            {
                res += std::to_string(cnt) + "." + val + " ";
                ++cnt;
            }
            res += "\n";
            _con->sendInLoop(res);
            LogInfo("[LogInfo]word query");
            //写回cache块
            CacheManager::getInstance()->getCache(string(tname)).put(_key._sought, finals);
            CacheManager::getInstance()->getCache(string(tname)).addRecord(_key._sought, finals);
        }
    }       
}
void CalculateTask::pageSearcher()
{
    string longLine = "<-------------------------------------------------------------->\n";
    LRUCache lru = CacheManager::getInstance()->getCache2(string(tname));

    vector<string> tmp;
    int ret = lru.get(_web._sought, tmp);
    if(ret == 0)
    {
        //缓存命中
        string send = tmp[0] + "[cache]\n";
        //tmp[0] 是缓存中的网页内容
        //[cache]标注让用户知道这个结果是从缓存中直接获取的，而不是实时查询的
        _con->sendInLoop(send);
        LogInfo("[LogInfo]page query");
        //写回自己的cache
         CacheManager::getInstance()->getCache2(string(tname)).put(_web._sought, tmp);
         //再加到pendinglist上，等定时器通知主缓存去更新同步
         CacheManager::getInstance()->getCache2(string(tname)).addRecord(_web._sought, tmp);
    }
    else
    {
        //缓存没命中
        vector<string> finals = _web.doQuery();
        if(finals.size() == 0)
        {
            _con->sendInLoop("未找到适配文章，请重新输入。\n");
            return;
        }
        else
        {
            InetAddress addr = _con->getPeerAddr();
            string ip = addr.ip();
            unsigned port = addr.port();
            string Line;

            if(finals.size() > 3)
            {
                size_t i = 0;
                for(;i < finals.size(); ++i)
                {
                    //超过3条处理分页
                    if(i < 3)
                    {
                        Line += finals[i];
                    }
                    else
                    {
                        break;
                    }
                }
                _Store[std::make_pair(ip, port)] = std::make_pair(i, finals);
            }
            else
            {
                for(auto word : finals)
                {
                    Line += word;
                }
                //在_Store中标记为-1表示无需分页
                _Store[std::make_pair(ip, port)] = std::make_pair(-1, finals);
            }
            Line += longLine;
            _con->sendInLoop(Line);
            LogInfo("[LogInfo]page query");
            vector<string> tmp;
            tmp.push_back(Line);
            //写回自己的cache块
            CacheManager::getInstance()->getCache2(string(tname)).put(_web._sought, tmp);
            //添加到pendinglist上，等定时器通知主缓存去更新同步
            CacheManager::getInstance()->getCache2(string(tname)).addRecord(_web._sought, tmp);
        }
    }
}
void CalculateTask::nextPageSearcher()
{
    string longLine = "<-------------------------------------------------------------->\n";
    string Line;
    InetAddress addr = _con->getPeerAddr();
    string ip = addr.ip();
    unsigned port = addr.port();
    auto p = std::make_pair(ip, port);
    auto it = _Store[p];
    if(it.first == -1)
    {
        //first == -1表示上次搜索结果不足3条（无需分页）
        _con->sendInLoop("当前网页搜索暂无其他内容\n");
    }
    else
    {
        size_t cur = it.first;//当前索引位置
        auto vc = it.second;// 完整结果集
        for(size_t i = 0; i < 3; ++i)
        {
            if(++cur >= vc.size())
            {
                //循环处理
                //当到达结果集末尾时，取模运算实现循环显示
                cur %= vc.size();
            }
            Line += vc[cur];
        }
        Line += longLine;
        _con->sendInLoop(Line);

        // 更新客户端状态
        _Store[std::make_pair(ip, port)] = std::make_pair(cur, vc);
    }
}
void CalculateTask::process()
{
    ProtocolParser parser(_msg);// 解析客户端消息
    //检查命令是否在有效集合内
    set<int> cmdSet = {1, 2, 3, 4, 5, 6};
    if(cmdSet.end() == cmdSet.find(parser._id))
    {
        //发送错误提示
		string send = "错误命令，请输入：\n\
			\"1 查询内容\" 请求推荐关键字\n\
			\"2 查询内容\" 查询网页\n\
			\"3\"          往下翻页\n\
			\"4\"          往上翻页\n\
			\"5\"          回到首页\n\
			\"6\"          去往尾页\n";
		_con->sendInLoop(send);
    }
    else
    {
        //收到消息："1 人工智能"
        //解析：ID=1, sought="人工智能"
        if (1 == parser._id) //关键字推荐模块
		{
			_key.setKrValue(parser._sought, _con);
            wordSearcher();
        } 
		else if (2 == parser._id) //网页搜索模块
		{
            _web.setMVal(parser._sought, _con);
            pageSearcher();
        }
        else
        {
            //3, 4, 5, 6可以写在一个switchPage函数里
            InetAddress addr = _con->getPeerAddr();
            string ip = addr.ip();
            unsigned port = addr.port();
            auto p = std::make_pair(ip, port);
            auto it = _Store[p];
            if(it.second.size() == 0)
            {
                _con->sendInLoop("当前网页搜索暂无其他内容\n");
            }
            else
            {
                if(it.first == -1)//结果不足三条，无需分页
                {
                    _con->sendInLoop("当前网页搜索暂无其他内容\n");
                }
                else//分页逻辑实现
                {
                    string longLine = "<------------------------------------------->\n";
                    string Line;
                    size_t cur = it.first;//获取索引
                    auto vc = it.second;

                    if(parser._id == 3)//向前翻页
                    {
                        for(size_t i = 0; i < 3; ++i)
                        {
                            if(cur >= vc.size())
                            {
                                cur %= vc.size();
                            }
                            Line += vc[cur];
                            ++cur;
                        }
                    }
                    else if(parser._id == 4)//向后翻页
                    {
                        for(size_t i = 0;i < 6; ++i)
                        {
                            if(--cur == -1)
                            {
                                cur = vc.size() - 1;
                            }
                        }
                        for(size_t i = 0;i < 3; ++i)
                        {
                            if(cur >= vc.size())
                            {
                                cur %= vc.size();
                            }
                            Line += vc[cur];
                            ++cur;
                        }
                    }
                    else if(parser._id == 5)//头页
                    {
                        cur = 0;
                        for(size_t i = 0;i < 3; ++i)
                        {
                            Line += vc[cur++];
                        }
                    }
                    else if(parser._id == 6)//去往尾页
                    {
                        cur = vc.size() - 3;
                        for(size_t i = 0;i < 3; ++i)
                        {
                            Line += vc[cur++];
                        }
                        cur = 0;//重置位置到首页，为了后续循环
                    }
                    Line += longLine;
                    _con->sendInLoop(Line);
                    //更新i为cur
                    _Store[std::make_pair(ip, port)] = std::make_pair(cur, vc);
                }
            }
        }
    }
}
}
