#include"../../include/Reactor/SocketIO.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace SearchEngine
{

SocketIO::SocketIO(int fd)
:_fd(fd)
{
}

SocketIO::~SocketIO()
{
    close(_fd);
}
int SocketIO::readn(char *buf,int len)
{
    int left = len;
    char *pstr = buf;
    int ret = 0;
    while(left > 0)
    {
        ret = read(_fd,pstr,left);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("read error -1");
            return -1;
        }
        else
        {
            pstr += ret;//已经读的
            left -= ret;//剩余读的
        }
    }
    return len - left;
}
int SocketIO::readLine(char *buf,int len)
{
    int left = len - 1;
    char *pstr = buf;
    int ret = 0,total = 0;
    while(left > 0)
    {
        //MSG_PEEK不清空缓冲区
        ret = recv(_fd,pstr,left,MSG_PEEK);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("readLine error -1");
            return -1;
        }
        else if (ret == 0)
        {
            break;
        }
        else
        {
            for(int idx = 0;idx < ret;++idx)
            {
                if(pstr[idx] == '\n')//读一行的内容，遇到换行符时，记录下当前长度
                                     //使用readn指令读取该长度，并且更新pstr的位置
                                     //返回已读长度
                {
                    int sz = idx + 1;
                    readn(pstr,sz);
                    pstr += sz;
                    *pstr = '\0';
                    return total + sz;
                }
            }
            readn(pstr,ret);//如果走到这里了就说明没有换行符（说明只有一行）
                            //于是就会读取全部内容
            total += ret;
            pstr += ret;
            left -= ret;
        }
    }
    *pstr = '\0';//手动分隔
    return total - left;
}
int SocketIO::writen(const char *buf,int len)
{
    int left = len;//left:剩余长度
    const char *pstr = buf;
    int ret = 0;
    while(left > 0)
    {
        ret = write(_fd,pstr,left);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("writen error -1");
            return -1;
        }
        else if(ret == 0)
        {
            break;
        }
        else
        {
            pstr += ret;//pstr = pstr + ret
            left -= ret;//left = left - ret
        }
    }
    return len - left;
}    


}
