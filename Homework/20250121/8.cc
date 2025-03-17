#include <iostream>
#include <set>
#include <iterator>

using std::set;
using std::cout;
using std::cin;
using std::endl;

void test()
{
    int n,m;
    cin >> n >> m;
    set<int> A,B;

    int num;

    for(int i = 0;i < n; ++i)
    {
        cin >> num;
        A.insert(num);
    }

    for(int i = 0;i < m; ++i)
    {
        cin >> num;
        B.insert(num);
    }
    
    set<int> C;
    C.insert(A.begin(),A.end());
    C.insert(B.begin(),B.end());

    set<int>::iterator cit = C.begin();
    for(auto &item : C)
    {
        cout << item << " ";
    }
}

int main()
{
    test();
    return 0;
}

