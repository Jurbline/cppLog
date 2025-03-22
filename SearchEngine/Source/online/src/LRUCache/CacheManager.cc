#include <iostream>
#include"../../include/LRUCache/CacheManager.h"

namespace SearchEngine
{
CacheManager *CacheManager::_pInstance = nullptr;

CacheManager::CacheManager()
{
}
CacheManager *CacheManager::getInstance()
{
    if(!_pInstance)
    {
        _pInstance = new CacheManager();
    }
    return _pInstance;
}
//若不想用LRU，这个部分可以换成Redis
void CacheManager::init(const string &filename)
{
    //将缓存的大小预设为7
    //预留vector的存储空间
    _caches.reverse(7);
    _caches2.reverse(7);

    for(int i = 0; i < 7 ;++i)
    {
        //关键字的候选词为5个
        _caches.emplace_back(LRUCache(5));
        //网页搜索部分的候选文章为3个
        _caches2.emplace_back(LRUCache(3));
    }
}
LRUCache& CacheManager::getCache(string name)
{
    int idx = stoi(name);
    return _caches[idx];
}
LRUCache& CacheManager::getCache2(string name)
{
    int idx = stoi(name);
    return _caches2[idx];
}
void CacheManager::updateCache()
{
    printf("\e[0;35m"
            "wordCache thread[0] got a task[update cache]\n"
            "\e[0m");
    //把所有子Cache的pendinglist的node依次插入主Cache中
    int cnt = 0;

    //共7个，1-6是次缓存
    for(int i = 1;i < 7; ++i)
    {
        //若次缓存的待更新节点为空，则cnt++
        if(!_caches[i]._pendingUpdateList.size())
        {
            ++cnt;
            continue;
        }
        //_cache[0]是主缓存，将每个次缓存的待更新链表中的数据
        //合并到主缓存的待更新列表中
        _caches[0].mergePending(_caches[i]);
        //将次缓存的待更新链表清空，防止数据的滞留（不影响下一次
        //待更新的数据）比如第一次待更新链表有效数据为A，若数据没有
        //清空，第二次待更新链表中会有残留的A，所以需要清空，因为
        //每一次待更新的数据是不一样的
        _caches[i]._pendingUpdateList.clear();
    }
    //该循环结束后，所有的数据都存在主缓存中

    if(cnt == 6)
    {
        printf("\e[0;35m"
                "wordCache thread[0] got a task[update cache]\n"
                "\e[0m");
        return;
    }

    //将主缓存中的数据同步更新到每个次缓存中，目的是保证每个缓存中的
    //数据都是一致的，这样客户端发送数据来了之后，使用任何一个缓存进行
    //查询的效果都是一样的，不然0号线程只有0号缓存中的数据，1号线程只有
    //1号缓存中的数据，那么0号线程查询1号缓存中的数据就查询不到了
    for(int i = 1;i < 7 ; ++i)
    {
        _caches[i].update(_caches[0]);
    }
     printf("\e[0;35m" 
            "wordCache thread[0] finished a task[update cache success]\n" 
            "\e[0m");
}

//这个updateCache2的作用与updateCache是完全一样的
void CacheManager::updateCache2()
{
     printf("\e[0;35m"
            "wordCache thread[0] finished a task[update cache success]\n"
            "\e[0m");

     //把所有子cache的pendinglist的node依次插入主cache中
     //然后情况pendingList
	 int cnt = 0;
     for(int i = 1; i < 7; ++i)
     {
         if (!_caches2[i]._pendingUpdateList.size())
         {
             ++cnt;
             continue;
         }
		 _caches2[0].mergePending(_caches2[i]);
		 _caches2[i]._pendingUpdateList.clear();
     }

     if (6 == cnt)
     {
         printf("\e[0;35m"
                "wordCache thread[0] finished a task[update cache success]\n"
                "\e[0m");
         return;
     }

     for(int i = 1; i < 7; ++i) {
         _caches2[i].update(_caches2[0]);
     }
     printf("\e[0;35m"
             "wordCache thread[0] finished a task[update cache success]\n"
             "\e[0m");
}

}

