#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include<arpa/inet.h>
#include<string>

using std::string;

namespace SearchEngine
{

class InetAddress
{
/*
struct sockaddr_in
{
    sa_family_t sin_family; // address family: AF_INET
    in_port_t sin_port; // port in network byte order
    struct in_addr sin_addr; // internet address
};

struct in_addr
{
    uint32_t s_addr; // address in network byte order
};
*/
public:
    InetAddress(const string &ip,unsigned short port);
    InetAddress(const struct sockaddr_in &addr);
    string ip() const;
    ~InetAddress();
    unsigned short port() const;
    const struct sockaddr_in *getInetAddrPtr() const;
private:
    struct sockaddr_in _addr;

};

}//end of namespace
#endif
