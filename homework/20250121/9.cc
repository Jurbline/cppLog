#include <iostream>
#include <map>
#include <string>

using std::map;
using std::string;
using std::cout;
using std::cin;
using std::endl;

void test()
{
    int ItemNum;
    cin >> ItemNum;
    map<string,map<string,int>> SaleDetails;//水果名,<产地，数量>
    for(int i = 0; i < ItemNum; ++i)
    {
        string Fruit,Address;
        int Number;

        cin >> Fruit >> Address >> Number;
        
        auto isExist = SaleDetails.find(Address);
        if(isExist == SaleDetails.end())
        {
            SaleDetails[Address] = map<string,int>();
        }

        if(SaleDetails[Address].find(Fruit) == SaleDetails[Address].end())
        {
            SaleDetails[Address][Fruit] = 0;
        }

        SaleDetails[Address][Fruit] += Number;
    }
        for(const auto &add : SaleDetails)
        {
            cout << add.first << endl;
            for(const auto &fru : add.second)
            {
                cout << "    |----" << fru.first << "(" << fru.second << ")" << endl;
            }
        }
}

int main()
{
    test();
    return 0;
}

