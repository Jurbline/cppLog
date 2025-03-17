#include <iostream>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    // 双向链表节点
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    
    unordered_map<int, Node*> cache;  // 哈希表，key -> node
    int capacity;  // 缓存容量
    Node* head;    // 虚拟头节点
    Node* tail;    // 虚拟尾节点
    
    // 从链表中移除节点
    void remove(Node* node) {
        Node* prev_node = node->prev;
        Node* next_node = node->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
    }
    
    // 将节点添加到链表头部
    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    
    // 删除链表尾部的节点（最久未使用的节点）
    Node* removeTail() {
        Node* tail_node = tail->prev;
        remove(tail_node);
        return tail_node;
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node(0, 0);  // 创建虚拟头节点
        tail = new Node(0, 0);  // 创建虚拟尾节点
        head->next = tail;
        tail->prev = head;
    }

    // 获取缓存中某个键的值
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);  // 将该节点移除
            addToHead(node);  // 再次将该节点移到链表头部
            return node->value;
        }
        return -1;
    }

    // 插入或更新一个键值对
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // 更新值并将节点移到头部
            Node* node = cache[key];
            node->value = value;
            remove(node);
            addToHead(node);
        } else {
            // 如果容量已满，移除尾部节点
            if (cache.size() == capacity) {
                Node* tail_node = removeTail();
                cache.erase(tail_node->key);
                delete tail_node;
            }
            // 创建新节点并将其添加到头部
            Node* new_node = new Node(key, value);
            cache[key] = new_node;
            addToHead(new_node);
        }
    }

    // 析构函数，释放内存
    ~LRUCache() {
        for (auto& pair : cache) {
            delete pair.second;
        }
        delete head;
        delete tail;
    }
};

int main() {
    LRUCache cache(2);

    cache.put(1, 1);  // 缓存是 {1=1}
    cache.put(2, 2);  // 缓存是 {1=1, 2=2}

    cout << cache.get(1) << endl;  // 返回 1

    cache.put(3, 3);  // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    cout << cache.get(2) << endl;  // 返回 -1 (未找到)

    cache.put(4, 4);  // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    cout << cache.get(1) << endl;  // 返回 -1 (未找到)
    cout << cache.get(3) << endl;  // 返回 3
    cout << cache.get(4) << endl;  // 返回 4

    return 0;
}

