#include <iostream>
#include "../../include/Reactor/ThreadPool.h"

using std::cout;
using std::endl;

namespace SearchEngine
{

thread_local const char *tname = "name_test";

ThreadPool::ThreadPool(size_t threadNum,size_t queSize)
:_threadNum(threadNum)
,_threads()
,_queSize(queSize)
,_taskQue(_queSize)
,_isExit(false)
{

}
ThreadPool::~ThreadPool()
{

}

void ThreadPool::start()
{
    for(size_t idx = 1;idx < _threadNum - 1;++idx)
    {
        //给每个线程一个名字
        _threads.push_back(thread(&ThreadPool::doTask,this,std::to_string(idx)));
    }
}
void ThreadPool::stop()
{
    //任务执行完毕之后，才能让主线程继续向下执行
    while(!_taskQue.empty())
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    _isExit = true;
    //唤醒所有在_notEmpty条件变量上的线程
    _taskQue.wakeup();
    //回收工作线程
    for(auto &th : _threads)
    {
        th.join();
    }
}

//任务添加与获取
void ThreadPool::addTask(Task &&task)
{
    if(task)
    {
        _taskQue.push(std::move(task));
    }
}

Task ThreadPool::getTask()
{
    return _taskQue.pop();
}
//线程池交给工作线程执行的任务，即线程入口函数
void ThreadPool::doTask(string name)
{
    tname = name.c_str();
    printf("\e[0;32m" "calculate thread[%s] created\n" "\e[0m",tname);
    while(!_isExit)
    {
        //获取任务
        Task taskcb = getTask();
        if(taskcb)
        {
            string out = "calculate thread[" + string(tname) + "] got a task";
            printf("\e[0;32m" "%s\n" "\e[0m", out.c_str());
            //执行任务
            //taskcb->process();//多态
            taskcb();
        }
        else
        {
            cout << "taskcb == nullptr" << endl;
        }
    }
}
}
