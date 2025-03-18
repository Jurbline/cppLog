#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include"Socket.h"
#include"SocketIO.h"
#include"InetAddress.h"

#include<sys/types.h>
#include<sys/socket.h>
#include<functional>
#include<memory>

using std::function;
using std::shared_ptr;

namespace SearchEngine
{

class EventLoop;
class TcpConnection
:public std::enable_shared_from_this<TcpConnection>
{
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
public:
    explicit TcpConnection(int fd,EventLoop *loop);
    ~TcpConnection();
    void send(const string &msg);
    void sendInLoop(const string &msg);
    string receive();
    bool isClosed() const;

    //方便调试
    string toString();

    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
public:
    //回调函数的注册
    void setNewConnectionCallback(const TcpConnectionCallback &cb);
    void setMessageCallback(const TcpConnectionCallback &cb);
    void setCloseCallback(const TcpConnectionCallback &cb);
    
    //回调函数的执行
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();
private:
    EventLoop *_loop;//让TcpConnection知道EventLoop的存在
    SocketIO _sockIO;

    //调试用
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;

    TcpConnectionCallback _onNewConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

}
#endif
