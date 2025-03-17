#include <iostream>
#include <vector>

using std::vector;
using std::endl;
using std::cout;

void test()
{
    cout << "Non-Empty vector" << endl << endl;
    vector<int> vec = {1,2,3,4};
    cout << "vec.at(0) = " << vec.at(0) << endl;
    cout << "vec[0] = " << vec[0] << endl;
    cout << "vec.front() = " << vec.front() << endl;
    cout << "*vec.begin() = " << *vec.begin() << endl;

    cout << "Empty vector" << endl << endl;
    vector<int> vec1;
    cout << "vec1.at(0) = " << vec1.at(0) << endl;
    cout << "vec1[0] = " << vec1[0] << endl;
    cout << "vec1.front() = " << vec1.front() << endl;
    cout << "*vec1.begin() = " << *vec1.begin() << endl;
}
int main()
{
    test();
    return 0;
}

