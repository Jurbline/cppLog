#include <iostream>
#include"../../include/WebPageSearcher/WebPageSearcher.h"
namespace SearchEngine
{
WebPageSearcher::WebPageSearcher(string key)
:_sought(key)
{
    _pQuery = WebPageQuery::getWebQueryPtr();
}
WebPageSearcher::WebPageSearcher()
:_pQuery(WebPageQuery::getWebQueryPtr())
{

}
vector<string> WebPageSearcher::doQuery()
{
    vector<string> result = _pQuery->doQuery(_sought);
    return result;
}

void WebPageSearcher::setMVal(string sought ,TcpConnectionPtr con)
{
    _sought = sought;
    _conn = con;
}
}
