#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

void test()
{
    vector<char> vc = {'H','E','L','L','O'};
    string str(vc.begin(),vc.end());
    cout << "str = " << str << endl;
}
int main()
{
    test();
    return 0;
}

