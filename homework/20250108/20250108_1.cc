#include <iostream>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

using namespace std;
using namespace log4cpp;

void test()
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
    //过滤器
    int idx = 0;
    while(idx <400)
    {
    root.setPriority(Priority::WARN);
    root.fatal("Fatal Message");
    root.alert("Alert Message");
    root.crit("Crit Message");
    root.error("Error Message");
    root.warn("Warn Message");
    root.notice("Notice Message");
    root.info("Info Message");
    root.debug("Debug Message");
    idx++;
    }
    Category::shutdown();
}
int main()
{
    test();
    return 0;
}

