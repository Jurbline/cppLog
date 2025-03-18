#include <iostream>
#include"../../include/Reactor/Acceptor.h"
#include<stdio.h>
#include"../../include/Reactor/EventLoop.h"

namespace SearchEngine
{

class EventLoop;
Acceptor::Acceptor(const string &ip,unsigned short port)
:_sock()
,_addr(ip,port)
{

}
Acceptor::~Acceptor()
{

}
void Acceptor::ready()
{
    bind();
    setReuseAddr();
    setReusePort();
    listen();
}
//地址复用
void Acceptor::setReuseAddr()
{
    int on = 1;
    int ret = setsockopt(_sock.fd(),SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    if(ret)
    {
        perror("setsockopt");
        return;
    }
}
//端口复用
void Acceptor::setReusePort()
{
    int on = 1;
    int ret = setsockopt(_sock.fd(),SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on));
    if(ret)
    {
        perror("setsockopt");
        return;
    }
}
void Acceptor::bind()
{
    int ret = ::bind(_sock.fd(),(struct sockaddr *)_addr.getInetAddrPtr(),
                     sizeof(struct sockaddr));
    if(ret == -1)
    {
        perror("bind");
        return;
    }
}
void Acceptor::listen()
{
    int ret = ::listen(_sock.fd(),128);//监听上限数目128
    if(ret == -1)
    {
        perror("listen");
        return;
    }
}
int Acceptor::accept()
{
    int connfd = ::accept(_sock.fd(),nullptr,nullptr);
    if(connfd == -1)
    {
        perror("accept");
        return -1;
    }
    return connfd;
}
int Acceptor::fd() const
{
    return _sock.fd();
}
}
