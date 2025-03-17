#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>  // 用于std::accumulate

using namespace std;

// 定义Person类，用于存储选手的姓名和成绩
class Person {
public:
    string name;            // 选手姓名
    deque<int> score_deque; // 存储10个评委的打分（使用deque）

    // 默认构造函数，姓名为 "null"，分数为全0
    Person() : name("null"), score_deque(10, 0) {}

    // 参数化构造函数，传入姓名
    Person(const string& name) : name(name), score_deque(10, 0) {}
};

int main() {
    // 存储5名选手
    vector<Person> contestants = {
        Person("A"), Person("B"), Person("C"), Person("D"), Person("E")
    };
    
    // 模拟10个评委的打分（假设这里的打分已经有了，实际情况应根据输入动态获取）
    vector<vector<int>> score_lists = {
        {90, 88, 85, 92, 86, 87, 91, 89, 84, 93}, // 选手A的分数
        {76, 80, 78, 79, 75, 74, 72, 77, 81, 78}, // 选手B的分数
        {88, 87, 90, 85, 82, 91, 89, 86, 88, 87}, // 选手C的分数
        {70, 72, 74, 71, 73, 75, 69, 76, 77, 72}, // 选手D的分数
        {95, 94, 93, 91, 96, 92, 97, 93, 95, 94}  // 选手E的分数
    };
    
    // 将每个选手的打分放入相应的Person对象中
    for (size_t i = 0; i < contestants.size(); ++i) {
        contestants[i].score_deque = deque<int>(score_lists[i].begin(), score_lists[i].end());
    }
    
    // 遍历每个选手，计算去掉最高和最低分后的平均分
    for (const auto& contestant : contestants) {
        // 将分数排序，去掉最高分和最低分
        deque<int> sorted_scores = contestant.score_deque;
        sort(sorted_scores.begin(), sorted_scores.end());
        
        // 去掉最高分和最低分
        sorted_scores.pop_back();  // 去掉最高分
        sorted_scores.pop_front(); // 去掉最低分
        
        // 计算剩余分数的总和
        int sum = accumulate(sorted_scores.begin(), sorted_scores.end(), 0);
        
        // 计算平均分
        double average = sum / static_cast<double>(sorted_scores.size());
        
        // 输出结果
        cout << "选手 " << contestant.name << " 的平均分是: " << average << endl;
    }

    return 0;
}

