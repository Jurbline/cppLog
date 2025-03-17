#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/FileAppender.hh>

using namespace std;
using namespace log4cpp;

#define LogInfo(msg) Mylogger::getInstance()->info((string("[File: ") + __FILE__ + " | Function: " + __FUNCTION__ + " | Line: " + to_string(__LINE__) + "] " + msg).c_str())
#define LogError(msg) Mylogger::getInstance()->error((string("[File: ") + __FILE__ + " | Function: " + __FUNCTION__ + " | Line: " + to_string(__LINE__) + "] " + msg).c_str())
#define LogWarn(msg) Mylogger::getInstance()->warn((string("[File: ") + __FILE__ + " | Function: " + __FUNCTION__ + " | Line: " + to_string(__LINE__) + "] " + msg).c_str())
#define LogDebug(msg) Mylogger::getInstance()->debug((string("[File: ") + __FILE__ + " | Function: " + __FUNCTION__ + " | Line: " + to_string(__LINE__) + "] " + msg).c_str())


class Mylogger
{
public:
    static Mylogger *getInstance()
    {
        if(!_pInstance)
        {
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }
    static void Destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
	void warn(const char *msg)
    {
        root.warn(msg);
    }
	void error(const char *msg)
    {
        root.error(msg);
    }
	void debug(const char *msg)
    {
        root.debug(msg);
    }
	void info(const char *msg)
    {
        root.info(msg);
    }
	void fatal(const char *msg)
    {
        root.fatal(msg);
    }
	void crit(const char *msg)
    {
        root.crit(msg);
    }
	
private:
    static Mylogger *_pInstance;
    Category &root = Category::getRoot().getInstance("hkc");
	Mylogger()
    {
        PatternLayout *ppl = new PatternLayout();
        ppl->setConversionPattern("%d %c [%p] %m%n");
        FileAppender *pfa = new FileAppender("pfa","log.txt");
        pfa->setLayout(ppl);
        root.addAppender(pfa);
        root.setPriority(Priority::DEBUG);
    }
	~Mylogger()
    {
        Category::shutdown();
    }
    
private:
  //......
};

Mylogger *Mylogger::_pInstance = nullptr;

void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->debug("The log is debug message");
    log->warn("The log is warn message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");

    Mylogger::Destroy();
}

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}
int main()
{
    test0();
    test1();
    return 0;
}

