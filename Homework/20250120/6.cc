#include <iostream>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <sstream>

using namespace std;
using namespace log4cpp;
Category &root = Category::getRoot();
void Log4cpp()
{
    //日志格式
    SimpleLayout *psl = new SimpleLayout();
    BasicLayout *pbl = new BasicLayout();
    PatternLayout *ppl = new PatternLayout();
    ppl->setConversionPattern("%d %c [%p] %m%n");
    //日志目的地
    OstreamAppender *pos = new OstreamAppender("os",&cout);
    pos->setLayout(psl);
    FileAppender *pfa = new FileAppender("fa","fa.txt");
    pfa->setLayout(pbl);
    RollingFileAppender *prfa = new RollingFileAppender("rfa","rfa.txt",4*1024,3);
    prfa->setLayout(ppl);
    //记录器
    Category &root = Category::getRoot().getInstance("test1");
    root.addAppender(pfa);
    root.addAppender(pos);
    root.addAppender(prfa);
    root.setPriority(Priority::DEBUG);
}
template <typename T>
void addString(stringstream &ss,const T &value)
{
    ss << value;
}
template <typename T,typename ...Args>
void addString(stringstream &ss,const T &value,Args... args)
{
    ss << value;
    addString(ss,args...);
}
void logMessage(Priority::PriorityLevel level,const string &message)
{
    switch (level) 
    {
    case Priority::DEBUG:
        root.debug(message);
        break;
    case Priority::INFO:
        root.info(message);
        break;
    case Priority::WARN:
        root.warn(message);
        break;
    case Priority::ERROR:
        root.error(message);
        break;
    case Priority::FATAL:
        root.fatal(message);
        break;
    default:
        root.info(message);
        break;
    }
}
template <typename ...Args>
void logMessage(Priority::PriorityLevel level,Args... args)
{
    stringstream ss;
    (ss << ... << args);
    addString(level,ss.str());
}
void LogInfo(const string &rhs)
{
    logMessage(Priority::INFO,rhs);
}
void LogError(const string &rhs)
{
    logMessage(Priority::ERROR,rhs);
}
void LogWarn(const string &rhs)
{
    logMessage(Priority::WARN,rhs);
}
void LogDebug(const string &rhs)
{
    logMessage(Priority::DEBUG,rhs);
}
void test1() 
{
    int number = 100;
    const char *pstr = "hello, log4cpp";
    LogInfo("This is an info message. number = %d, str = %s\n", number, pstr);
    LogError("This is an error message. number = %d, str = %s\n", number, pstr);
    LogWarn("This is a warn message. number = %d, str = %s\n", number, pstr);
    LogDebug("This is a debug message. number = %d, str = %s\n", number, pstr);
}
int main()
{
    Log4cpp();
    test1();
    Category::shutdown();
    return 0;
}

