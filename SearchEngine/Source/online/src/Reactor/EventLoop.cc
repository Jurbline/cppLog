#include <iostream>
#include<sys/eventfd.h>
#include<unistd.h>
#include"../../include/Reactor/Acceptor.h"
#include"../../include/Reactor/EventLoop.h"
#include"../../include/Reactor/TcpConnection.h"

using std::endl;
using std::cout;
using std::cerr;

namespace SearchEngine
{

class Acceptor;
class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
using Functor = function<void()>;
EventLoop::EventLoop(Acceptor &acceptor)
:_epfd(createEpollFd())
,_evtList(1024)
,_isLooping(false)
,_acceptor(acceptor)
,_conns()
,_efd(createEventFd())
,_pendings()
,_mutex()
{
    //获取listenfd
    int listenfd = _acceptor.fd();
    //将listenfd放在红黑树上进行监听
    addEpollReadFd(listenfd);
    //还要监听用于通知的文件描述符_efd
    addEpollReadFd(_efd);
}
EventLoop::~EventLoop()
{
    close(_epfd);
    close(_efd);
}

//事件是否循环
void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping)
    {
        waitEpollFd();
    }
}
void EventLoop::unloop()
{
    _isLooping = false;
}
void EventLoop::waitEpollFd()//封装epoll_wait函数
{
    int nready = 0;
    do{
    nready = epoll_wait(_epfd,&*_evtList.begin(),_evtList.size(),3000);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
    {
        cerr << "nready == -1" << endl;
        return;
    }
    else if(nready == 0)
    {
        cout << ">>epoll_wait timeout!!!" << endl;
    }
    else
    {
        //手动扩容vector
        if(nready == (int)_evtList.size())
        {
            _evtList.resize(2*nready);
        }
        for(int idx = 0;idx < nready;++idx)
        {
            int fd =_evtList[idx].data.fd;
            int listenfd = _acceptor.fd();
            if(fd == listenfd)//listenfd就绪
            {
                handleNewConnection();
            }
            else if(fd == _efd)//用于通知文件描述符就绪
            {
                if(_evtList[idx].events & EPOLLIN)
                {
                    handleRead();
                    //遍历vector
                    doPendingFunctors();
                }
            }
            else
            {
                if(_evtList[idx].events & EPOLLIN)
                {
                    //老的连接上有数据发送过来
                    handleMessage(fd);
                }
            }
        }
    }
}
void EventLoop::handleNewConnection()//新连接请求
{
    int connfd = _acceptor.accept();
    if(connfd < 0)
    {
        perror("handleNewConnection");
        return;
    }
    //放在红黑树上进行监听
    addEpollReadFd(connfd);
    //此时可以创建TcpConnection的对象
    TcpConnectionPtr con(new TcpConnection(connfd,this));

    //注册回调函数
    con->setNewConnectionCallback(_onNewConnection);
    con->setMessageCallback(_onMessage);
    con->setCloseCallback(_onClose);

    //键值放入map中
    _conns.insert({connfd,con});
    con->handleNewConnectionCallback();
}
void EventLoop::handleMessage(int fd)//老连接上数据的收发
{
    auto it = _conns.find(fd);
    if(it != _conns.end())
    {
        //先判断连接有没有断开
        bool flag = it->second->isClosed();
        if(flag)//连接断开，要执行连接断开的事件
        {
            it->second->handleCloseCallback();
            //将文件描述符从红黑树上删除
            delEpollReadFd(fd);
            //从map上删除
            _conns.erase(it);
        }
        else
        {
            it->second->handleMessageCallback();
        }
    }
    else
    {
        cout << "The Connection is not exist!!!" << endl;
        return;
    }
}
int EventLoop::createEpollFd()//封装epoll_create函数
{
    int fd = epoll_create(1);
    if(fd < 0)
    {
        perror("createEpollFd");
        return -1;
    }
    return fd;
}
void EventLoop::addEpollReadFd(int fd)//放在红黑树上进行监听
{
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;
    int ret = epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&evt);
    if(ret < 0)
    {
        perror("addEpollReadFd");
        return;
    }

}
void EventLoop::delEpollReadFd(int fd)//取消在红黑树上的监听
{
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;
    int ret = epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,&evt);
    if(ret < 0)
    {
        perror("delEpollReadFd");
        return;
    }
}
void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb)
{
    _onNewConnection = std::move(cb);
}
void EventLoop::setMessageCallback(TcpConnectionCallback &&cb)
{
    _onMessage = std::move(cb);
}
void EventLoop::setCloseCallback(TcpConnectionCallback &&cb)
{
    _onClose = std::move(cb);
}

void EventLoop::handleRead()//封装了read函数
{
    uint64_t one = 1;
    ssize_t ret = read(_efd,&one,sizeof(uint64_t));
    if(ret != sizeof(u_int64_t))
    {
        perror("handleRead");
        return;
    }
}
void EventLoop::wakeup()//封装了write函数（read阻塞直到等到write写数据，所以这里是wakeup）
{
    uint64_t one = 1;
    ssize_t ret = write(_efd,&one,sizeof(uint64_t));
    if(ret != sizeof(u_int64_t))
    {
        perror("handleRead");
        return;
    }
}
int EventLoop::createEventFd()//封装了eventFd
{
    int fd = eventfd(0,0);
    if(fd < 0)
    {
        perror("createEventFd");
        return -1;
    }
    return fd;
}
void EventLoop::doPendingFunctors()//执行所有任务（遍历vector）
{
    vector<Functor> tmp;
    {
        lock_guard<mutex> lg(_mutex);
        tmp.swap(_pendings);//交换，这样就可以让_pendings再接受新的任务
    }
    //此处的cb在进行回调的时候执行的“任务”也就是
    //在TcpConnection的sendInLoop函数中通过bind
    //绑定的this，以及send函数，以及msg就会被
    //触发，将数据发送给客户端
    //_loop->runInLoop(bind(&TcpConnection::send, this, msg));
    for(auto &cb : tmp)
    {
        cb();
    }

}
void EventLoop::runInLoop(Functor &&cb)//真正执行任务的函数
{
    //缩小锁的范围
    {
        lock_guard<mutex> lg(_mutex);
        //将任务放在_pendings中
        _pendings.push_back(std::move(cb));
    }
    //唤醒EventLoop进行数据的收发
    wakeup();
}

}


