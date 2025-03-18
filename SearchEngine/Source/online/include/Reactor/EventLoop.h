#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include<sys/epoll.h>
#include<functional>
#include<memory>
#include<map>
#include<vector>
#include<mutex>

using std::vector;
using std::map;
using std::mutex;
using std::shared_ptr;
using std::function;
using std::lock_guard;

namespace SearchEngine
{
class Acceptor;
class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
using Functor = function<void()>;
class EventLoop
{
public:
    EventLoop(Acceptor &acceptor);
    ~EventLoop();

    //事件是否循环
    void loop();
    void unloop();
private:
    void waitEpollFd();//封装epoll_wait函数
    void handleNewConnection();//新连接请求
    void handleMessage(int fd);//老连接上数据的收发
    int createEpollFd();//封装epoll_create函数
    void addEpollReadFd(int fd);//放在红黑树上进行监听
    void delEpollReadFd(int fd);//取消在红黑树上的监听
public:
    void setNewConnectionCallback(TcpConnectionCallback &&cb);
    void setMessageCallback(TcpConnectionCallback &&cb);
    void setCloseCallback(TcpConnectionCallback &&cb);

    void handleRead();//封装了read函数
    void wakeup();//封装了write函数（read阻塞直到等到write写数据，所以这里是wakeup）
    int createEventFd();//封装了eventFd
    void doPendingFunctors();//执行所有任务（遍历vector）
    void runInLoop(Functor &&cb);//真正执行任务的函数

private:
    int _epfd;//epoll_create创建的文件描述符
    vector<struct epoll_event> _evtList;//存放就绪文件描述符
    bool _isLooping;//是否循环
    Acceptor &_acceptor;//获取Acceptor类中的accept函数（返回的内容）
    map<int,TcpConnectionPtr> _conns;//存放文件描述符与TcpConnection连接对象的键值对
                                     
    TcpConnectionCallback _onNewConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;

    int _efd;//eventfd创建的文件描述符
    vector<Functor> _pendings;//待执行的任务
    mutex _mutex;//互斥锁（用于互斥访问共享资源vector）

};

}
#endif
