#ifndef __SE_CACHE_MANAGER_H__
#define __SE_CACHE_MANAGER_H__
#include "LRUCache.h"
#include "../DisallowCopyAssign.h"

#include<iostream>

namespace SearchEngine
{

class CacheManager
{
public:
    static CacheManager *getInstance();
    ~CacheManager()
    {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void init(const string &filename);
    LRUCache& getCache(string);
    LRUCache& getCache2(string);

    void updateCache();
    void updateCache2();
private:
    explicit CacheManager();
private:
DISALLOWCOPYANDASSIGN(CacheManager);

    static CacheManager *_pInstance;
    vector<LRUCache> _caches;
    vector<LRUCache> _caches2;

};
}
#endif
