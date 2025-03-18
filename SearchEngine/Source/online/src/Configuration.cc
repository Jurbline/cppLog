#include <iostream>
#include "../include/Configuration.h"
namespace SearchEngine
{
    Configuration *Configuration::_pInstance = nullptr;//饱汉模式
    Configuration *Configuration::getInstance()
    {
        if(!_pInstance)
        {
            _pInstance = new Configuration("conf/server.conf");
        }
        return _pInstance;
    }
    Configuration::Configuration(const string &filePath)
    {
        //初始化配置文件
        //ifstream ifs;
        //ifs.open(filePath)
        ifstream ifs(filePath);
        if(!ifs.good())
        {
            cerr << "open server.conf fail" << endl;
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
    map<string,string> &Configuration::getConfigs()//获取存放配置文件的map
    {
        return _configs;
    }
}

