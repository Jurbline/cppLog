#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__
namespace SearchEngine
{


class NonCopyable
{
protected:
    NonCopyable() {}
    ~NonCopyable() {}
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
};

}
#endif
