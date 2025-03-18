#include<iostream>
#include<time.h>
#include<sys/timerfd.h>
#include<unistd.h>
#include<poll.h>
#include"../../include/TimerManager/TimerFd.h"
namespace SearchEngine
{
TimerFd::TimerFd(int initsec,int perisec,TimerFdCallback &&cb)
:_timerfd(createTimerFd())
,_initsec(initsec)
,_perisec(perisec)
,_cb(std::move(cb))
,_isStarted(false)
{

}
TimerFd::~TimerFd()
{
    if(_timerfd)
    {
        setTimerFd(0, 0);
        close(_timerfd);
    }
}
void TimerFd::start()
{
    /*struct pollfd 
      {
      int fd;
      short events;//POLLIN/POLLOUT/POLLERR
      short revents;//传出的参数值
      };
    */
    struct pollfd pfd;
    pfd.events = POLLIN;
    pfd.fd = _timerfd;

    setTimerFd(_initsec,_perisec);

    _isStarted = true;
    while(_isStarted)
    {
        int nready = poll(&pfd, 1 , 20000);
        //要监视的元素数量为1
        //-1:阻塞等，#define INFTIM -1 Linux中没有定义此宏
        //0:立即返回，不阻塞进程
        //>0:等待指定毫秒数，如当前系统时间精度不够毫秒，向上取值。
        //函数返回值：满足监听条件的文件描述符的数目。
        if(nready == -1 && errno == EINTR)
        {
            continue;
        }
        else if(nready == -1)
        {
            perror("poll nready == -1");
            return;
        }
        else if(nready == 0)
        {
            std::cout << "poll timeout!!!" << std::endl;
        }
        else
        {
            if(pfd.events & POLLIN)
            {
                handleRead();//写了Read
                if(_cb)
                {
                    _cb();//执行任务的函数
                }
            }
        }
    }
}
void TimerFd::stop()
{
    _isStarted = false;
    setTimerFd(0, 0);
}
void TimerFd::handleRead()
{
    uint64_t one = 1;
    //fd：文件描述符；
    //buf:存放读到的数据；
    //count：想读的数据的最大长度;
    int ret = read(_timerfd, &one, sizeof(one));
    //返回值：实际读到的数据的长度，那么这个长度是小于等于count的
    //，失败的时候返回-1，返回值为0，数据读完
    //（读到文件、管道、socket末尾 ---对端关闭）；
    if(ret != sizeof(one))
    {
        perror("handleRead");
        return;
    }
    
}
int TimerFd::createTimerFd()
{
    int fd = timerfd_create(CLOCK_REALTIME,0);
    //clockid:可设置为
    //CLOCK_REALTIME：相对时间，从1970.1.1到目前的时间。更改系统时间会更改获取的值，它以系统时间为标。
    //CLOCK_MONOTONIC：绝对时间，获取的时间为系统重启到现在的时间，更改系统时间对齐没有影响。
    //flags: 可设置为
    //TFD_NONBLOCK（非阻塞）;TFD_CLOEXEC（同O_CLOEXEC）linux内核2.6.26版本以上都指定为0.
    if(fd < 0)
    {
        perror("createTimerFd");
        return -1;
    }
    return fd;
}
void TimerFd::setTimerFd(int initsec,int perisec)
{
    struct itimerspec value;
    value.it_value.tv_sec = initsec;//定时器起始时间，比如：12:00:00开始，或者相对某个时间点开始计时
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = perisec;//定时器周期时间，前后两次超时时间差
    value.it_interval.tv_nsec = 0;//精确到纳秒数
    int fd = timerfd_settime(_timerfd, 0, &value, nullptr);
    //fd: timerfd_create对应的文件描述符
    //flags: 0表示是相对定时器;TFD_TIMER_ABSTIME表示是绝对定时器
    //new_value:设置超时时间，如果为0则表示停止定时器。
    //old_value:一般设为NULL, 不为NULL,则返回定时器这次设置之前的超时时间
    if(fd < 0)
    {
        perror("setTimerFd");
        return;
    }
}
}
