#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>

class Mylogger {
public:
    static Mylogger *getInstance() {
        if (!_pInstance) {
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }

    static void destroy() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void warn(const char *msg) {
        _category.warn(msg);
    }

    void error(const char *msg) {
        _category.error(msg);
    }

    void debug(const char *msg) {
        _category.debug(msg);
    }

    void info(const char *msg) {
        _category.info(msg);
    }

private:
    Mylogger()
        : _category(log4cpp::Category::getInstance(std::string("Mylogger"))) {
        log4cpp::PatternLayout *patternLayout = new log4cpp::PatternLayout();
        patternLayout->setConversionPattern("[%d] [%p] [%c] %m%n");

        log4cpp::FileAppender *fileAppender = new log4cpp::FileAppender("fileAppender", "log.txt");
        fileAppender->setLayout(patternLayout);

        _category.setAppender(fileAppender);
        _category.setPriority(log4cpp::Priority::DEBUG);
    }

    ~Mylogger() {
        log4cpp::Category::shutdown();
    }

private:
    static Mylogger *_pInstance;
    log4cpp::Category &_category;
};

Mylogger *Mylogger::_pInstance = nullptr;

// 宏定义，用于实现像 printf 一样调用，同时自动添加文件名、函数名和行号
#define LogInfo(msg) Mylogger::getInstance()->info((std::string("[File: ") + __FILE__ + " | Function: " + __FUNCTION__ + " | Line: " + std::to_string(__LINE__) + "] " + msg).c_str())
#define LogError(msg) Mylogger::getInstance()->error((std::string("[File: ") + __FILE__ + " | Function: " + __FUNCTION__ + " | Line: " + std::to_string(__LINE__) + "] " + msg).c_str())
#define LogWarn(msg) Mylogger::getInstance()->warn((std::string("[File: ") + __FILE__ + " | Function: " + __FUNCTION__ + " | Line: " + std::to_string(__LINE__) + "] " + msg).c_str())
#define LogDebug(msg) Mylogger::getInstance()->debug((std::string("[File: ") + __FILE__ + " | Function: " + __FUNCTION__ + " | Line: " + std::to_string(__LINE__) + "] " + msg).c_str())

// 测试函数
void test0() {
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->warn("The log is warn message");
    log->debug("The log is debug message");

    Mylogger::destroy();
}

void test1() {
    LogInfo("This is an info message");
    LogError("This is an error message");
    LogWarn("This is a warning message");
    LogDebug("This is a debug message");
}

int main() {
    test0();
    test1();
    return 0;
}

