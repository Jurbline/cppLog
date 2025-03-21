#ifndef __SE_PROTOCOL_PARASER__
#define __SE_PROTOCOL_PARASER__

#include<sstream>

using std::string;
using std::istringstream;

namespace SearchEngine
{
class ProtocolParser
{
public:
    ProtocolParser(string msg)
    :_msg(msg)
    {
        doParaser();
    }
    void doParaser();
public:
    int _id;
    string _sought;
private:
    string _msg;

};
void ProtocolParser::doParaser()
{
    istringstream is(_msg.c_str());
    string s;
    is >> s;
    _id = atoi(s.c_str());
    is >> s;
    _sought = s;
}
}
#endif
