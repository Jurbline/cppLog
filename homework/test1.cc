#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 创建一个存放 vector<int> 的 vector
    vector<vector<int>> vec_of_vec;

    // 向 vec_of_vec 中添加一些 vector<int>
    vec_of_vec.push_back({1, 2, 3});
    vec_of_vec.push_back({4, 5, 6});
    vec_of_vec.push_back({7, 8, 9});

    // 遍历 vec_of_vec 并打印每个内层 vector 和它的内存地址
    for (size_t i = 0; i < vec_of_vec.size(); i++) {
        cout << "vec_of_vec[" << i << "] - Address: " << &vec_of_vec[i] << endl;
        for (size_t j = 0; j < vec_of_vec[i].size(); j++) {
            cout << "  vec_of_vec[" << i << "][" << j << "] = " << vec_of_vec[i][j]
                 << " - Address: " << &vec_of_vec[i][j] << endl;
        }
    }

    // 体会 vector 元素和对象的内存位置
    cout << "\nFinal vector structure:" << endl;
    for (size_t i = 0; i < vec_of_vec.size(); i++) {
        cout << "Address of vector " << i << ": " << &vec_of_vec[i] << endl;
        cout << "Size of vector " << i << ": " << vec_of_vec[i].size() << endl;
        cout << "Address of internal vector elements:" << endl;
        for (size_t j = 0; j < vec_of_vec[i].size(); j++) {
            cout << "  Element " << j << ": " << &vec_of_vec[i][j] << endl;
        }
    }

    return 0;
}

