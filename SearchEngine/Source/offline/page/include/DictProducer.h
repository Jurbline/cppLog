#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__
#include"WordSegmentation.h"
namespace SearchEngine
{
class DictProducer
{
public:
    DictProducer()
    :_jieba()
    {
        
    }
    ~DictProducer()
    {}
    WordSegmentation &getJieba()
    {
        return _jieba;
    }
private:
    WordSegmentation _jieba;
};
}
#endif
