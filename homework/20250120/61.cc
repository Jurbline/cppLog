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
template <typename ...Args>
void logMessage(Priority::PriorityLevel level, Args... args) 
{
    stringstream ss;
    addString(ss, args...);
    string logMessage = ss.str();
    switch(level)
    {
        case Priority::DEBUG:
            root.debug(logMessage);
            break;
        case Priority::INFO:
            root.info(logMessage);
            break;
        case Priority::WARN:
            root.warn(logMessage);
            break;
        case Priority::ERROR:
            root.error(logMessage);
            break;
        case Priority::FATAL:
            root.fatal(logMessage);
            break;
        default:
            root.info(logMessage);
            break;
    }
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
    LogInfo("This is an info message. number = " + to_string(number) + ", str = " + pstr);
    LogError("This is an error message. number = " + to_string(number) + ", str = " + pstr);
    LogWarn("This is a warn message. number = " + to_string(number) + ", str = " + pstr);
    LogDebug("This is a debug message. number = " + to_string(number) + ", str = " + pstr);
}
int main()
{
    Log4cpp();
    test1();
    Category::shutdown();
    return 0;
}

