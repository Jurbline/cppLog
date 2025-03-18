#include"../include/DictProducer.h"

namespace SearchEngine
{
DictProducer::DictProducer()
:_jieba()
,_dir()
{
    _dir("data/CN/art");//传入要遍历的目录
    for(auto &fileName : _dir.getFiles())
    {
        _file.push_back(fileName);
    }
    buildCnDict();
    buildEnDict();
    store();
    
}
DictProducer::~DictProducer()
{
}
void DictProducer::buildEnDict()
{
    ifstream ifs;
    openFile(ifs,"data/EN/english.txt");
    string line;
    while(getline(ifs,line))
    {
        processLine(line);//对英文进行处理
        istringstream iss(line);
        string word;
        while(iss >> word)
        {
            int &isExist = _dict[word];
            if(isExist)
            {
                ++isExist;
            }
            else
            {
                isExist = 1;
                size_t id = _dict.size();
                _idMap[id] = word;
                insertEnindex(word,id);
            }
        }
    }
    ifs.close();

}
void DictProducer::buildCnDict()
{
    for(string & fileName : _file)
    {
        ifstream ifs;
        openFile(ifs,fileName);
        string line;
        while(ifs >> line)
        {
            vector<string> results = _jieba(line);
            for(string &elem : results)
            {
                if(elem.size() % CHSIZE == 0)//utf8中文占用3字节，检查是不是中文
                {
                    int &isExist = _dict[elem];// 若不存在，默认是0
                    if(isExist)
                    {
                        ++isExist;
                    }
                    else
                    {
                        isExist = 1;
                        size_t id = _dict.size();
                        _idMap[id] = elem;
                        insertIndex(elem,id);
                    }
                }
            }
        }
        ifs.close();
    }
}
void DictProducer::store()
{
    ofstream ofs_dict;
    inputFile(ofs_dict,"data/dict.dat");
    for(auto it = _dict.begin();it != _dict.end();++it)
    {
        ofs_dict << it->first << " " << it->second << endl;
    }
    ofstream ofs_index;
    inputFile(ofs_index,"data/index.dat");
    for(auto it = _index.begin();it != _index.end();++it)
    {
        ofs_index << it->first << " ";
        for(auto & st : it->second)
        {
            ofs_index << st << " ";
        }
        ofs_index << endl;
    }
    #if 1
    ofstream ofs_idMap;
    inputFile(ofs_idMap, "data/idMap.dat");
    for(auto it = _idMap.begin(); it != _idMap.end(); ++it )
    {
        ofs_idMap <<  it->first << " " << it->second << endl;
    }
    ofs_idMap.close();
#endif
    ofs_dict.close();
    ofs_index.close();
}
void DictProducer::insertIndex(const string &elem,size_t id)
{
    vector<string> results;
    _jieba.CutSmall(elem,results,1);
    for(string & it :results)
    {
        _index[it].insert(id);
    }
    
}
void DictProducer::processLine(string &line)
{
    for(auto & elem : line)
    {
        if(!isalpha(elem))//检查是不是英文单词
        {
            elem = ' ';
        }
        else if(isupper(elem))
        {
            elem = tolower(elem);//将大写转换为小写
        }
    }
}
void DictProducer::insertEnindex(const string &word,size_t id)
{
    for(size_t i = 0;i < word.size();++i)
    {
        string ch(1,word[i]);
        _index[ch].insert(id);
    }
}
void DictProducer::openFile(ifstream &ifs,const string &fileName)
{
    ifs.open(fileName);
    cout << "open >>>" << fileName << endl;
    if(!ifs)
    {
        perror("open file failed in Dict ifs");
        return;
    }
}
void DictProducer::inputFile(ofstream &ofs,const string &fileName)
{
    ofs.open(fileName);
    if(!ofs)
    {
        perror("open file failed in Dict ofs");
        return;
    }
}
}//end of namespace
