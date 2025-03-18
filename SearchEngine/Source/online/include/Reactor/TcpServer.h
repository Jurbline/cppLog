#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "Acceptor.h"
#include "EventLoop.h"

namespace SearchEngine
{


class TcpServer
{
public:
    TcpServer(const string &ip,unsigned short port);
    ~TcpServer();

    //Server Start/Stop
    void start();
    void stop();

    //回调的注册
    void setAllCallback(TcpConnectionCallback &&cb
                        ,TcpConnectionCallback &&cb2
                        ,TcpConnectionCallback &&cb3);

private:
    Acceptor _acceptor;
    EventLoop _loop;

};

}
#endif
