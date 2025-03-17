#include <iostream>
#include <list>
#include <deque>

using std::deque;
using std::list;
using std::endl;
using std::cout;

void func(const list<int> &lst,deque<int> &dqOdd,deque<int> &dqEven)
{
    for(auto it : lst)
    {
        if(it % 2 == 0)
        {
            dqEven.push_back(it);
        }
        else
        {
            dqOdd.push_back(it);
        }
    }
}
void test()
{
    list<int> lst = {1,2,3,4,5,6,7,8,9};
    deque<int> dqOdd;
    deque<int> dqEven;
    func(lst,dqOdd,dqEven);

    cout << "Odd: ";
    for(auto &it : dqOdd)
    {
        cout << it << " ";
    }
    cout << endl;
    cout << "Even: ";
    for(auto &it : dqEven)
    {
        cout << it << " ";
    }
    cout << endl;
}
int main()
{
    test();
    return 0;
}

