#include <iostream>
#include <unordered_map>

using std::cout;
using std::endl;
using std::unordered_map;

class LRUCache;
struct DNode
{
    int _key,_value;

    DNode *prev;
    DNode *next;

    DNode()
    :_key(0)
    ,_value(0)
    ,prev(nullptr)
    ,next(nullptr)
    {

    }

    DNode(int key,int value)
    :_key(key)
    ,_value(value)
    ,prev(nullptr)
    ,next(nullptr)
    {
        
    }

};
class LRUCache
{
public:
    LRUCache(int capacity)
    :_capacity(capacity)
    {
        _head = new DNode(0,0);
        _tail = new DNode(0,0);
        _head->next = _tail;
        _tail->prev = _head;
    }

    void remove(DNode* node)
    {
        DNode* node_Prev = node->prev;
        DNode* node_Next = node->next;
        node_Prev->next = node_Next;
        node_Next->prev = node_Prev;
    }
    
    DNode* removeTail()
    {
        DNode *oldNode = _tail->prev;
        remove(oldNode);
        return oldNode;
    }

    void addNewNode(DNode* node)
    {
        node->next = _head->next;
        node->prev = _head;
        _head->next->prev = node;
        _head->next = node;
    }

int get(int key)
{
    if(lru.find(key) != lru.end())
    {
        DNode* node = lru[key];
        remove(node);
        addNewNode(node);
        return node->_value;
    }
    else
    {
        return -1;
    }
}

    void put(int key, int value)
    {
        if(lru.find(key) != lru.end())
        {
            DNode *node = lru[key];
            node->_value = value;
            remove(node);
            addNewNode(node);
        }
        else
        {
            if(lru.size() == _capacity)
            {
                DNode *oldTailNode = removeTail();
                lru.erase(oldTailNode->_key);
                delete oldTailNode;
            }
                DNode *newNode = new DNode(key,value);
                lru[key] = newNode;
                addNewNode(newNode);
        }
    }
    ~LRUCache()
    {
        lru.clear();
        delete _tail;
        delete _head;
    }
private:
    unordered_map<int,DNode*> lru;
    int _capacity;
    DNode* _head;
    DNode* _tail;
};
int main()
{
    return 0;
}

