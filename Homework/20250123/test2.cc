#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

using namespace std;

// 函数：读取规则文件并存储到unordered_map中
void load_replacement_rules(const string& filename, unordered_map<string, string>& rules) {
    ifstream map_file(filename);
    string word, replacement;
    
    // 读取每一行并将每对单词和替换短语添加到map中
    while (map_file >> word) {
        // 读取替换短语
        getline(map_file, replacement);
        // 去掉替换短语前的空格
        while (!replacement.empty() && replacement[0] == ' ') {
            replacement.erase(0, 1);  // 删除前导空格
        }
        rules[word] = replacement;  // 存储规则
    }
}

// 函数：处理待转换的文本
void process_file(const string& filename, const unordered_map<string, string>& rules) {
    ifstream file(filename);
    string line;

    // 逐行读取并进行替换
    while (getline(file, line)) {
        stringstream ss(line);
        string word;
        bool first_word = true;

        // 逐个单词处理
        while (ss >> word) {
            if (!first_word) {
                cout << " ";  // 每个单词之间空格
            }
            first_word = false;

            // 查找是否有替换规则
            auto it = rules.find(word);  // 查找替换规则
            if (it != rules.end()) {
                cout << it->second;  // 替换为对应的短语
            } else {
                cout << word;  // 如果没有替换规则，输出原单词
            }
        }
        cout << endl;  // 换行
    }
}

int main() {
    unordered_map<string, string> replacement_rules;

    // 1. 加载规则文件
    load_replacement_rules("map.txt", replacement_rules);

    // 2. 处理待转换的文本文件
    process_file("file.txt", replacement_rules);

    return 0;
}

