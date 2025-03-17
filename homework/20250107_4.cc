#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    vector<int> temp;
    vector<int> temp1;
    vector<int> temp2;
    vector<int> temp3 = {6,6,6};
    temp.push_back(1);
    temp.push_back(2);
    temp1.push_back(3);
    temp2.push_back(4);
    vector<vector<int>> test;
    /* test.push_back({1,2,3}); */
    /* test.push_back({4,5,6}); */
    test.push_back(temp);
    test.push_back(temp1);
    test.push_back(temp2);
    test.push_back(temp3);
    for(size_t i = 0;i < test.size();i++)
    {//打印内层的vector和地址
        cout << "test[" << i << "] Address: " << &test[i] << endl;
        for(size_t j = 0;j < test[i].size();j++)
        {
            cout << "test[" << i << "][" << j << "] = " << test[i][j] << ",Address: "
            << &test[i][j] << endl;
        }
    }
    cout << endl << endl;
    //打印外层vector和地址
    for(size_t i = 0;i < test.size();++i)
    {
        cout << "The Address of OuterFace test[" << i << "]: " << &test[i] << endl;
        cout << "Size of OuterFace test[" << i << "]: " << test[i].size() << endl;
    }
    return 0;
}

