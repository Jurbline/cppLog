#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include"TaskQueue.h"
#include<vector>
#include<thread>
#include<string>
#include<functional>

using std::function;
using std::string;
using std::vector;
using std::thread;

namespace SearchEngine
{
using Task = function<void()>;
class ThreadPool
{
public:
    ThreadPool(size_t threadNum,size_t queSize);
    ~ThreadPool();

    void start();
    void stop();

    //任务添加与获取
    void addTask(Task &&task);

private:
    Task getTask();
    //线程池交给工作线程执行的任务，即线程入口函数
    void doTask(string name);
private:
    size_t _threadNum;//子线程数目
    vector<thread> _threads;//存放子线程的容器
    size_t _queSize;//任务队列大小
    TaskQueue _taskQue;//任务队列
    bool _isExit;//标志线程池是否退出

};
}
#endif
