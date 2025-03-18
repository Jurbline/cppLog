#include <iostream>
#include<string>
using namespace std;
bool isBalanced(string num) {
    int even = 0,odd = 0;
    for(int i = 0;i < num.size() ; ++i)
    {
        if(i % 2 == 0) 
        {
            even+=(num[i]);
            cout << "even = " << even << endl;
        }else {
            odd+=(num[i]);
            cout << "odd = " << odd << endl;
        }
    }
    if(even == odd) return true;
    else return false;
}
int main()
{
    string Num;
    cin >> Num;
    cout << isBalanced(Num);
    return 0;
}

