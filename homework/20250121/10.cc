#include <iostream>
#include <list>
#include <string>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::list;
using std::string;

void test()
{
    list<char*> lst = {"hello","world","!"};
    vector<string> vec;
    for(auto item : lst)
    {
        vec.push_back(string(item));
    }
    for(auto &item : vec)
    {
        cout << item << " ";
    }
}
int main()
{
    test();
    return 0;
}

