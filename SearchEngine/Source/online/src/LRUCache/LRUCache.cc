#include <iostream>
#include"../../include/LRUCache/LRUCache.h"

namespace SearchEngine
{
int LRUCache::get(string key,vector<string> &value)
{
    auto it = _cache.find(key);
    if(it == _cache.end())
    {
        return -1;
    }
    else
    {
        //splice实现list拼接的功能。将源list的内容部分或全部元素删除，拼插入到目的list
        //将某个节点移动到链表头部，表示该数据最近被使用过
        //1：目标位置，2：源链表，3：要移动的节点迭代器
        _nodes.splice(_nodes.begin(),_nodes,it->second);
        value = it->second->value;
        return 0;
    }
}
void LRUCache::put(string key,vector<string> value)
{
    auto it = _cache.find(key);
    if(it != _cache.end())
    {
        _nodes.splice(_nodes.begin(),_nodes,it->second);
        it->second->value = value;
        return;
    }
    _nodes.emplace_front(CacheNode(key,value));
    _cache[key] = _nodes.begin();//将新插入的节点在链表中的位置（迭代器）记录到哈希表 _cache 中
    if(_cache.size() > _capacity)
    {
        //从哈希表 _cache 中删除链表尾部节点的键。
        //从链表 _nodes 中移除尾部节点（最久未使用的节点）
        _cache.erase(_nodes.back().key);
        _nodes.pop_back;
    }
}
//将key与满足key的候选词val添加到待更新的链表中，也就是放在list尾部
void LRUCache::addRecord(string key,vector<string> val)
{
    CacheNode tmp(key,val);
    _pendingUpdateList.push_back(tmp);
}
//mergePending与update的效果其实没有什么区别，只是使用函数的
//对象不一样
//操作对象：另一个LRU对象的待更新列表
//合并，使用LRU算法，将lrucache._pendingUpdateList中的内容
//更新合并到list<CacheNode>中
void LRUCache::mergePending(const LRUCache &lrucache)
{
    for(auto &it : lrucache._pendingUpdateList)
    {
        put(it.key,it.value);
    }
}

//操作对象：另一个LRU对象的主缓存
//更新，使用LRU算法，将lrucache._cache中的内容
//更新合并到list<CacheNode>中
void LRUCache::update(const LRUCache &lrucache)
{
    for(auto &it : lrucache._cache)
    {
        string key = it.first;
        vector<string> val = it.second->value;
        put(key,val);
    }
}
}
