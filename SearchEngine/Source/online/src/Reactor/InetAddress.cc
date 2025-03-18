#include <iostream>
#include"../../include/Reactor/InetAddress.h"
#include<strings.h>


namespace SearchEngine
{   

InetAddress::InetAddress(const string &ip,unsigned short port)
{
    ::bzero(&_addr,sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(const struct sockaddr_in &addr)
:_addr(addr)
{

}
string InetAddress::ip() const
{
    //网络字节序转换为本机字节序（ip地址）
    return string(inet_ntoa(_addr.sin_addr));
}
InetAddress::~InetAddress()
{

}
unsigned short InetAddress::port() const
{
    //网络字节序转换为本机字节序（端口）
    return ntohs(_addr.sin_port);
}
const struct sockaddr_in *InetAddress::getInetAddrPtr() const
{
    return &_addr;
}

}
