#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__
#include"DisallowCopyAssign.h"

#include<utility>
#include<fstream>
#include<string>
#include<iostream>
#include<map>
#include<sstream>

using std::pair;
using std::istringstream;
using std::cerr;
using std::endl;
using std::ifstream;
using std::map;
using std::string;
namespace SearchEngine
{
class Configuration
{
public:
    static Configuration *getInstance(const char* filePath);
    map<string,string> &getConfigs();

private:
    DISALLOWCOPYANDASSIGN(Configuration);
    explicit Configuration(const string &filePath);//防止类型转换
    ~Configuration();

private:
    static Configuration *_pInstance;
    string _configFilePath;//配置文件的路径，即conf/
    map<string,string> _configs;//配置文件
};
Configuration *Configuration::_pInstance = nullptr;
Configuration *Configuration::getInstance(const char* filePath)
{
    if(!_pInstance)
    {
        _pInstance = new Configuration(string(filePath));
    }
    return _pInstance;
}
Configuration::Configuration(const string &filePath)
:_configFilePath(filePath)//加载配置文件并初始化
{
    ifstream ifs;
    ifs.open(_configFilePath);
    if(!ifs.good())
    {
        cerr << "Load config error!!!" << endl;
        return;
    }
    string line,key,val;
    while(getline(ifs,line),!ifs.eof())
    {
        istringstream iss(line);
        iss >> key;
        iss >> val;
        pair<string,string> record(key,val);
        _configs.insert(record);
    }
    ifs.close();
}
map<string,string> &Configuration::getConfigs()
{
    return _configs;
}
}
#endif
