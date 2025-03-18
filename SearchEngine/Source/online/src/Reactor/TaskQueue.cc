#include <iostream>
#include "../../include/Reactor/TaskQueue.h"
namespace SearchEngine
{
TaskQueue::TaskQueue(size_t capa)
:_capacity(capa)
,_que()
,_mutex()
, _notEmpty()
, _notFull()
, _flag(true)
{

}
TaskQueue::~TaskQueue()
{

}

//生产与消费
void TaskQueue::push(ElemType &&task)
{
    //上锁
    unique_lock<mutex> ul(_mutex);
    //判满
    while(full())
    {
        _notFull.wait(ul);//满则睡眠
    }
    //不满则存起来
    _que.push(std::move(task));
    //唤醒消费者
    _notEmpty.notify_one();
    //解锁（自动）
}
ElemType TaskQueue::pop()
{
    unique_lock<mutex> ul(_mutex);
    while(empty() && _flag)
    {
        _notEmpty.wait(ul);
    }
    if(_flag)
    {
        ElemType tmp = _que.front();//获取第一个元素然后删除
        _que.pop();
        _notFull.notify_one();
        return tmp;
    }
    else
    {
        return nullptr;
    }
}

//判空判满
bool TaskQueue::empty() const
{
    return _que.size() == 0;
}
bool TaskQueue::full() const
{
    return _que.size() == _capacity;
}

//唤醒消费者
void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notify_all();
}
}
