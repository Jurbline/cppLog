#include <iostream>
#include <deque>
#include <string>

using std::string;
using std::deque;
using std::endl;
using std::cin;
using std::cout;

void test()
{
    deque<string> deq;
    string str;
    cout << "pls input a string(Break:-1): ";
    while(cin >> str)
    {
        if(str != "-1")
        {
            deq.push_back(str);
        }
        else
        {
            break;
        }
    }
    for(auto &it : deq)
    {
        cout << it << " ";
    }

}
int main()
{
    test();
    return 0;
}

