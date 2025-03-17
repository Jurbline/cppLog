#include <iostream>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

using std::cout;
using std::endl;
using namespace log4cpp;//引出命名空间

void test()
{
    //1、日志的格式
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d %c [%p]: %m%n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p]: %m%n");
    
    //2、日志的目的地
    OstreamAppender *pos = new OstreamAppender("12", &cout);
    pos->setLayout(ppl1);

    FileAppender *pfa = new FileAppender("file", "wd.txt");
    pfa->setLayout(ppl2);
    
    //3、日志记录器
    Category &root = Category::getRoot().getInstance("MyCat");
    root.addAppender(pos);//添加目的地，输出到屏幕
    root.addAppender(pfa);//添加目的地，输出到文件

    //4、过滤器（优先级）
    /* root.setPriority(Priority::DEBUG); */
    root.setPriority(Priority::ERROR);//设置日志记录器的优先级

    //只有日志的优先级大于等于日志记录器Category的时候，这个
    //日志才能被记录，否则日志就会被过滤
    root.emerg("This is a emerg message");//0
    root.error("This is a error message");//300
    root.warn("This is a warn message");//400
    root.debug("This is a debug message");//700

    //回收资源
    Category::shutdown();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

