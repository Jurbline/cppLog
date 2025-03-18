#ifndef __CONFIGURATION__
#define __CONFIGURATION__

#include "DisallowCopyAssign.h"
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using std::string;
using std::map;
using std::set;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::cerr;

namespace SearchEngine 
{
class Configuration
{
    //单例模式
public:
    static Configuration *getInstance();
    map<string,string> &getConfigs();//获取存放配置文件的map
    ~Configuration()
    {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
private:
    explicit Configuration(const string &filePath);//构造函数私有化

private:
    DISALLOWCOPYANDASSIGN(Configuration);
    static Configuration *_pInstance;
    static string _configFilePath;//配置文件的路径
    map<string,string> _configs;//配置文件的内容

};

}
#endif
