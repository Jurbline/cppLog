#ifndef __SE_TIMER_FD_H__
#define __SE_TIMER_FD_H__
#include<functional>

using std::function;
namespace SearchEngine
{
class TimerFd
{
    using TimerFdCallback = function<void()>;
public:
    TimerFd(int initsec,int perisec,TimerFdCallback &&cb);
    ~TimerFd();
    void start();
    void stop();
private:
    void handleRead();
    int createTimerFd();
    void setTimerFd(int initsec,int perisec);
private:
    int _timerfd;
    int _initsec;//起始时间
    int _perisec;//周期时间
    TimerFdCallback _cb;//用于注册回调函数
    bool _isStarted;//标志是否启动

};
}
#endif
