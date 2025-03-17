#include <iostream>
#include <list>
#include <deque>

void separateElements(const std::list<int>& inputList, std::deque<int>& evenDeque, std::deque<int>& oddDeque) {
    // 使用迭代器遍历 list
    for (std::list<int>::const_iterator it = inputList.begin(); it != inputList.end(); ++it) {
        if (*it % 2 == 0) {
            evenDeque.push_back(*it);  // 偶数加入 evenDeque
        } else {
            oddDeque.push_back(*it);   // 奇数加入 oddDeque
        }
    }
}

int main() {
    // 示例输入的 list
    std::list<int> inputList = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // 初始化两个 deque
    std::deque<int> evenDeque;
    std::deque<int> oddDeque;

    // 调用函数进行分离
    separateElements(inputList, evenDeque, oddDeque);

    // 输出偶数队列
    std::cout << "偶数队列: ";
    for (std::deque<int>::iterator it = evenDeque.begin(); it != evenDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 输出奇数队列
    std::cout << "奇数队列: ";
    for (std::deque<int>::iterator it = oddDeque.begin(); it != oddDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

