#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void test()
{
    //初始化
    /* vector<int> number;//1、无参对象 */
    /* vector<int> number(10, 3);//2、count个value元素 */
    //3、迭代器范围(左闭右开的区间)
    int arr[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    vector<int> number(arr,  arr + 10);//[arr, arr + 10)
    //4、拷贝构造与移动构造
    //5、大括号形式
    vector<int> number1 {1, 4, 7, 10, 2, 5, 8, 9, 3, 6};

    //遍历
    //1、使用下标
    for(size_t idx = 0; idx != number.size(); ++idx)
    {
        cout << number[idx] << "  ";
    }
    cout << endl;

    //2、未初始化的迭代器
    vector<int>::iterator it;
    for(it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    //3、已初始化的迭代器
    vector<int>::iterator it2 = number.begin();
    for(; it2 != number.end(); ++it2)
    {
        cout << *it2 << "  ";
    }
    cout << endl;

    for(auto it3 = number.begin(); it3 != number.end(); ++it3)
    {
        cout << *it3 << "  ";
    }
    cout << endl;

    //4、增强for循环
    for(auto &elem : number)
    {
        cout << elem << "  ";
    }
    cout << endl;

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


