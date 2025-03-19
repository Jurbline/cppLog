#include <iostream>
#include"../include/MyLog.h"
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/Priority.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/RollingFileAppender.hh>

using std::cout;
using std::endl;

namespace SearchEngine
{

Mylogger * Mylogger::_pInstance = nullptr;

Mylogger *Mylogger::getInstance()
{
    if(_pInstance == nullptr)
    {
        _pInstance = new Mylogger();
    }
    return _pInstance;
}   
void Mylogger::destroy()
{
    if(_pInstance)
    {
        delete _pInstance;
        _pInstance = nullptr;
    }
}
Mylogger::Mylogger()
:_mycat(log4cpp::Category::getRoot().getInstance("MyCategory"))
{
    using namespace log4cpp;

    //日志的格式
    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p]: %m%n");

    PatternLayout *ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p]: %m%n");
    //设置日志的目的地
    OstreamAppender * ostreamappender = new OstreamAppender("OstreamAppender",&cout);
    ostreamappender->setLayout(ptn1);//输出流

    FileAppender * fileappender = new FileAppender("FileAppender",
                                                   "log/server.log"
                                                   , 5 * 1024, 3);//5MB，最多3个文件
    fileappender->setLayout(ptn2);
    //日志记录器
    _mycat.addAppender(ostreamappender);//添加目的地，输出到屏幕
    _mycat.addAppender(fileappender);//添加目的地，输出到文件
    _mycat.setPriority(log4cpp::Priority::DEBUG);//添加目的地，输出到回滚文件
    //只有日志的优先级大于等于日志记录器Category的时候
    //也就是优先级大于DEBUG的时候，日志才会被记录，否则过滤
}
Mylogger::~Mylogger()
{
    cout << "~Mylogger()" << endl;
    log4cpp::Category::shutdown();
}
void Mylogger::warn(const char *msg)
{
	_mycat.warn(msg);
}

void Mylogger::error(const char *msg)
{
	_mycat.error(msg);
}

void Mylogger::info(const char *msg)
{
	_mycat.info(msg);
}

void Mylogger::debug(const char *msg)
{
	_mycat.debug(msg);
}

void Mylogger::setPriority(Priority p)
{
    switch(p)
    {
    case WARN:
        _mycat.setPriority(log4cpp::Priority::WARN);
        break;
    case ERROR:
        _mycat.setPriority(log4cpp::Priority::ERROR);
        break;
    case INFO:
        _mycat.setPriority(log4cpp::Priority::INFO);
        break;
    case DEBUG:
        _mycat.setPriority(log4cpp::Priority::DEBUG);
        break;
    }
}
}
