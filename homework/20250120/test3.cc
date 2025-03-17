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

// 全局日志实例
Category& root = Category::getRoot();

// 日志初始化函数
void initLogging() {
    // 设置日志格式
    SimpleLayout* psl = new SimpleLayout();
    BasicLayout* pbl = new BasicLayout();
    PatternLayout* ppl = new PatternLayout();
    ppl->setConversionPattern("%d %c [%p] %m%n");

    // 设置日志目的地
    OstreamAppender* pos = new OstreamAppender("os", &cout);
    pos->setLayout(psl);
    FileAppender* pfa = new FileAppender("fa", "fa.txt");
    pfa->setLayout(pbl);
    RollingFileAppender* prfa = new RollingFileAppender("rfa", "rfa.txt", 4 * 1024, 3);
    prfa->setLayout(ppl);

    // 将输出添加到日志记录器
    root.addAppender(pfa);
    root.addAppender(pos);
    root.addAppender(prfa);

    // 设置日志级别
    root.setPriority(Priority::DEBUG);
}

// 简单的日志记录函数
void logMessage(Priority::PriorityLevel level, const string& message) {
    switch (level) {
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
            root.info(message);  // 默认使用 INFO 级别
            break;
    }
}

// 记录日志的函数，接受可变参数
template <typename... Args>
void logMessage(Priority::PriorityLevel level, Args... args) {
    stringstream ss;
    (ss << ... << args);  // 拼接所有参数为一条日志消息
    logMessage(level, ss.str());  // 调用实际的记录日志的函数
}

// 用来记录 INFO 日志的函数
void LogInfo(const string& fmt) {
    logMessage(Priority::INFO, fmt);
}

// 用来记录 ERROR 日志的函数
void LogError(const string& fmt) {
    logMessage(Priority::ERROR, fmt);
}

// 用来记录 WARN 日志的函数
void LogWarn(const string& fmt) {
    logMessage(Priority::WARN, fmt);
}

// 用来记录 DEBUG 日志的函数
void LogDebug(const string& fmt) {
    logMessage(Priority::DEBUG, fmt);
}

void test1() {
    int number = 100;
    const char* pstr = "hello, log4cpp";

    // 记录不同级别的日志
    LogInfo("This is an info message. number = " + to_string(number) + ", str = " + pstr);
    LogError("This is an error message. number = " + to_string(number) + ", str = " + pstr);
    LogWarn("This is a warn message. number = " + to_string(number) + ", str = " + pstr);
    LogDebug("This is a debug message. number = " + to_string(number) + ", str = " + pstr);
}

int main() {
    initLogging();  // 初始化日志系统
    test1();        // 测试日志记录
    Category::shutdown();  // 关闭日志系统
    return 0;
}

