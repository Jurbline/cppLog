#include <iostream>
#include <deque>
#include <vector>
#include <list>

using std::list;
using std::deque;
using std::vector;
using std::cout;
using std::endl;

void test()
{
    vector<int> vec;
    vector<int> vec2(6,888);
    vector<int> vec3 = {1,2,3,4,5};
    int arr[5] = {2,3,4,5,6};
    vector<int> vec4(arr , arr + 5);

    vector<int> vec5 {3,4,5,6,7};
    for(const auto &it1 : vec)
    {
        cout << it1 << " ";
    }
    cout << endl;
    for(const auto &it2 : vec2)
    {
        cout << it2 << " ";
    }
    cout << endl;
    for(const auto &it3 : vec3)
    {
        cout << it3 << " ";
    }
    cout << endl;
    for(const auto &it4 : vec4)
    {
        cout << it4 << " ";
    }
    cout << endl;
    for(const auto &it5 : vec5)
    {
        cout << it5 << " ";
    }
    cout << endl;
}

void test1()
{
    deque<int> deq;
    deque<int> deq2(6,888);
    deque<int> deq3 = {1,2,3,4,5};
    int arr[5] = {2,3,4,5,6};
    deque<int> deq4(arr , arr + 5);

    deque<int> deq5 {3,4,5,6,7};
    for(const auto &it1 : deq)
    {
        cout << it1 << " ";
    }
    cout << endl;
    for(const auto &it2 : deq2)
    {
        cout << it2 << " ";
    }
    cout << endl;
    for(const auto &it3 : deq3)
    {
        cout << it3 << " ";
    }
    cout << endl;
    for(const auto &it4 : deq4)
    {
        cout << it4 << " ";
    }
    cout << endl;
    for(const auto &it5 : deq5)
    {
        cout << it5 << " ";
    }
    cout << endl;
}

void test2()
{
    list<int> lst;
    list<int> lst2(6,888);
    list<int> lst3 = {1,2,3,4,5};
    int arr[5] = {2,3,4,5,6};
    list<int> lst4(arr , arr + 5);

    list<int> lst5 {3,4,5,6,7};
    for(const auto &it1 : lst)
    {
        cout << it1 << " ";
    }
    cout << endl;
    for(const auto &it2 : lst2)
    {
        cout << it2 << " ";
    }
    cout << endl;
    for(const auto &it3 : lst3)
    {
        cout << it3 << " ";
    }
    cout << endl;
    for(const auto &it4 : lst4)
    {
        cout << it4 << " ";
    }
    cout << endl;
    for(const auto &it5 : lst5)
    {
        cout << it5 << " ";
    }
    cout << endl;
}

int main()
{
    cout << "Vector" << endl;
    test();
    cout << endl << endl << "Deque" << endl;
    test1();
    cout << endl << endl << "List" << endl;
    test2();
    return 0;
}
