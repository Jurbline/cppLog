#ifndef __SE_LRUCACHE_H__
#define __SE_LRUCACHE_H__

#include<string>
#include<unordered_map>
#include<vector>
#include<list>

using std::list;
using std::vector;
using std::string;
using std::unordered_map;
namespace SearchEngine
{
class LRUCache
{
    friend class CacheManager;
public:
    LRUCache(int capacity)
    :_capacity(capacity)
    {

    }
    //get 时，通过 _cache 直接找到节点迭代器，无需遍历链表。
    //从缓存中获取键 key 对应的值
    //如果存在，通过迭代器将节点移动到链表头部，并填充 val。如果不存在，返回失败

    //put 时，更新 _cache 并调整链表顺序。
    //将键值对插入缓存，若键已存在则更新
    int get(string key,vector<string> &val);
    void put(string key,vector<string> value);

    //将记录添加到待更新列表 _pendingUpdateList
    void addRecord(string key,vector<string> val);
    //将另一个LRUCache实例的待更新列表合并到当前实例
    void mergePending(const LRUCache &lrucache);

    //用另一个LRUCache实例的数据更新当前缓存
    void update(const LRUCache &lrucache);

private:
    struct CacheNode
    {
        CacheNode(string k, vector<string> v)
        :key(k)
        ,value(v)
        {

        }
        //Example:key为武汉，则value就是满足key的所有值
        string key;//待查询的词
        vector<string> value;//符合条件的值，存放在容器中
    };
private:
    //size_t _capacity
    unordered_map<string,list<CacheNode>>::size_type _capacity;
    //结点，用于存放元素（双向链表）插入新数据时，节点被添加到链表头部
    list<CacheNode> _nodes;
    //存放元素以及元素在节点中的迭代器的键值对（哈希表）
    //快速定位键对应的节点在链表中的位置，保证 get 和 put 操作的时间复杂度为 O(1)
    unordered_map<string,list<CacheNode>::iterator> _cache;
    //待更新节点（暂存需要延迟合并或批量处理的缓存更新）
    //后续通过 mergePending 合并到主缓存，避免频繁操作主缓存，提升性能
    list<CacheNode> _pendingUpdateList;
};
}
#endif
