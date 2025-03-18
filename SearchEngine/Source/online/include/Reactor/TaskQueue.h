#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using std::queue;
using std::mutex;
using std::unique_lock;
using std::condition_variable;
using std::function;

namespace SearchEngine
{

using ElemType = function<void()>;
class TaskQueue
{
public:
    TaskQueue(size_t capa);
    ~TaskQueue();

    //生产与消费
    void push(ElemType &&task);
    ElemType pop();
    
    //判空判满
    bool empty() const;
    bool full() const;

    //唤醒消费者
    void wakeup();
private:
    size_t _capacity;
    queue<ElemType> _que;//存放任务
    mutex _mutex;
    condition_variable _notEmpty;//消费者
    condition_variable _notFull;//生产者
    bool _flag;//标识

};

}
#endif
