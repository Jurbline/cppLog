#include <iostream>
#include"../../include/Reactor/TcpServer.h"

namespace SearchEngine
{

TcpServer::TcpServer(const string &ip,unsigned short port)
:_acceptor(ip,port)
,_loop(_acceptor)
{

}
TcpServer::~TcpServer()
{

}

//Server Start/Stop
void TcpServer::start()
{
    _acceptor.ready();//端口复用，地址复用，绑定，监听
    _loop.loop();//循环
}
void TcpServer::stop()
{
    _loop.unloop();
}

//回调的注册
void TcpServer::setAllCallback(TcpConnectionCallback &&cb
                    ,TcpConnectionCallback &&cb2
                    ,TcpConnectionCallback &&cb3)
{
    _loop.setNewConnectionCallback(std::move(cb));
    _loop.setMessageCallback(std::move(cb2));
    _loop.setCloseCallback(std::move(cb3));

}

}

