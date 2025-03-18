#include <iostream>
#include"../../include/Reactor/TcpConnection.h"
#include"../../include/Reactor/EventLoop.h"
#include<sstream>
using std::cout;
using std::endl;
using std::ostringstream;

namespace SearchEngine
{


TcpConnection::TcpConnection(int fd,EventLoop *loop)
:_loop(loop)
,_sock(fd)
,_sockIO(fd)
,_localAddr(getLocalAddr())
,_peerAddr(getPeerAddr())
{

}
TcpConnection::~TcpConnection()
{

}
void TcpConnection::send(const string &msg)//就是通过socketIO中的writen函数写数据，让原本阻塞的read函数运行
{
    _sockIO.writen(msg.c_str(),msg.size());
}
void TcpConnection::sendInLoop(const string &msg)
{
    if(_loop)
    {
        _loop->runInLoop(bind(&TcpConnection::send,this,msg));//将发送信息的能力给EventLoop
    }
}
string TcpConnection::receive()
{
    char buff[65535] = {0};
    _sockIO.readLine(buff,sizeof(buff));
    return string(buff);
}
bool TcpConnection::isClosed() const
{
    char buff[10] = {0};
    //如果接收缓冲区中没有数据，且对端没有关闭连接，recv 会一直阻塞，直到：
    //有数据到达
    //对端关闭连接（返回 0）
    //发生错误（返回 -1）
    int ret = recv(_sock.fd(),buff,sizeof(buff),MSG_PEEK);
    return (ret == 0);
}

//方便调试
string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "---->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();

    return oss.str();
}

InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    //获取本端地址的函数getsockname
    int ret = getsockname(_sock.fd(),(struct sockaddr *)&addr,&len);
    if(ret == -1)
    {
        perror("getsockname");
    }
    return InetAddress(addr);
}
InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    //获取对端地址的函数getpeername
    int ret = getpeername(_sock.fd(),(struct sockaddr *)&addr,&len);
    if(ret == -1)
    {
        perror("getpeername");
    }
    return (addr);
}
//回调函数的注册
void TcpConnection::setNewConnectionCallback(const TcpConnectionCallback &cb)
{
    _onNewConnection = cb;
}
void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
    _onMessage = cb;
}
void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
    _onClose = cb;
}

//回调函数的执行
void TcpConnection::handleNewConnectionCallback()
{
    if(_onNewConnection)
    {
        _onNewConnection(shared_from_this());
    }
    else
    {
        cout << "_onNewConnection == nullptr" << endl;
    }
}
void TcpConnection::handleMessageCallback()
{
    if(_onMessage)
    {
        _onMessage(shared_from_this());
    }
    else
    {
        cout << "_onMessage == nullptr" << endl;
    }
}
void TcpConnection::handleCloseCallback()
{
    if(_onClose)
    {
        _onClose(shared_from_this());
    }
    else
    {
        cout << "_onClose == nullptr" << endl;
    }

}
}
