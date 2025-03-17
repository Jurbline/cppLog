#include <iostream>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <cstdarg>
#include <cstdio>

using namespace std;
using namespace log4cpp;

// 全局日志实例
Category &root = Category::getRoot();

// 日志初始化函数
void initLogging() {
    // 日志格式
    SimpleLayout *psl = new SimpleLayout();
    BasicLayout *pbl = new BasicLayout();
    PatternLayout *ppl = new PatternLayout();
    ppl->setConversionPattern("%d %c [%p] %m%n");

    // 日志目的地
    OstreamAppender *pos = new OstreamAppender("os", &cout);
    pos->setLayout(psl);
    FileAppender *pfa = new FileAppender("fa", "fa.txt");
    pfa->setLayout(pbl);
    RollingFileAppender *prfa = new RollingFileAppender("rfa", "rfa.txt", 4 * 1024, 3);
    prfa->setLayout(ppl);

    // 记录器设置
    root.addAppender(pfa);
    root.addAppender(pos);
    root.addAppender(prfa);

    // 设置日志级别
    root.setPriority(Priority::DEBUG);
}

// 日志记录函数模板，用于可变参数
template <typename... Args>
void logMessage(Priority::PriorityLevel level, const char *format, Args... args) {
    char buffer[1024];  // 用于存储格式化后的日志信息
    snprintf(buffer, sizeof(buffer), format, args...);

    // 根据日志级别记录日志
    switch (level) {
        case Priority::DEBUG:
            root.debug(buffer);
            break;
        case Priority::INFO:
            root.info(buffer);
            break;
        case Priority::WARN:
            root.warn(buffer);
            break;
        case Priority::ERROR:
            root.error(buffer);
            break;
        case Priority::FATAL:
            root.fatal(buffer);
            break;
        default:
            root.info(buffer);
            break;
    }
}

// 日志宏定义，方便调用
#define LogInfo(fmt, ...) logMessage(Priority::INFO, fmt, __VA_ARGS__)
#define LogError(fmt, ...) logMessage(Priority::ERROR, fmt, __VA_ARGS__)
#define LogWarn(fmt, ...) logMessage(Priority::WARN, fmt, __VA_ARGS__)
#define LogDebug(fmt, ...) logMessage(Priority::DEBUG, fmt, __VA_ARGS__)

void test1() {
    int number = 100;
    const char *pstr = "hello, log4cpp";
    
    LogInfo("This is an info message. number = %d, str = %s", number, pstr);
    LogError("This is an error message. number = %d, str = %s", number, pstr);
    LogWarn("This is a warn message. number = %d, str = %s", number, pstr);
    LogDebug("This is a debug message. number = %d, str = %s", number, pstr);
}

int main() {
    initLogging();  // 初始化日志系统
    test1();        // 测试日志记录
    Category::shutdown();  // 关闭日志系统
    return 0;
}

