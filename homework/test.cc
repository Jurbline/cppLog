#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// 记录单词和它的频率
struct Record {
    string _word;
    int _frequency;

    // 构造函数，初始化 word 和 frequency
    Record(const string &word) : _word(word), _frequency(1) {}
};

// 字典类，用来读取文件并统计单词的频率
class Dictionary {
public:
    void read(const string &filename);  // 读取文件并统计频率
    void store(const string &filename); // 将结果写入文件

private:
    vector<Record> word_count;  // 存储单词和频率

    // 清理字符串中的非字母字符，保留字母并转化为小写
    string clean_word(const string &word);
    int find_word(const string &word);  // 查找单词是否已存在
};

string Dictionary::clean_word(const string &word) {
    string cleaned_word = "";

    // 遍历每个字符，如果是字母则保留
    for (int i = 0; i < word.length(); i++) {
        char c = word[i];
        // 只保留字母字符
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            cleaned_word += (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;  // 转换为小写
        }
    }

    return cleaned_word;
}

int Dictionary::find_word(const string &word) {
    // 查找该单词是否已经存在
    for (int i = 0; i < word_count.size(); i++) {
        if (word_count[i]._word == word) {
            return i;  // 返回该单词的位置
        }
    }
    return -1;  // 如果没有找到该单词，返回 -1
}

void Dictionary::read(const string &filename) {
    ifstream ifs(filename);  // 打开文件
    if (!ifs) {  // 检查文件是否成功打开
        cerr << "open file " << filename << " error" << endl;
        return;
    }

    string line;
    while (getline(ifs, line)) {  // 逐行读取文件
        istringstream iss(line);  // 使用 istringstream 处理这一行
        string word;
        while (iss >> word) {  // 从每一行中提取单词
            word = clean_word(word);  // 清理单词中的非字母字符
            if (!word.empty()) {  // 只有非空的单词才处理
                int index = find_word(word);  // 查找单词是否已经存在
                if (index != -1) {
                    word_count[index]._frequency++;  // 如果存在，增加频率
                } else {
                    word_count.push_back(Record(word));  // 否则将新单词添加到 vector 中
                }
            }
        }
    }

    ifs.close();  // 关闭文件
}

void Dictionary::store(const string &filename) {
    ofstream ofs(filename);  // 打开输出文件
    if (!ofs) {  // 检查文件是否成功打开
        cerr << "open file " << filename << " error" << endl;
        return;
    }

    // 使用 while 循环和索引来遍历 word_count
    int i = 0;
    while (i < word_count.size()) {  // 使用 while 循环遍历每个元素
        const auto &entry = word_count[i];  // 直接使用索引访问元素
        ofs << entry._word << " " << entry._frequency << endl;  // 将单词和频率写入文件
        i++;  // 移动到下一个元素
    }

    ofs.close();  // 关闭文件
}

int main() {
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");  // 读取文件并统计单词频率
    dict.store("dict.txt");  // 将结果保存到 dict.txt
    return 0;
}

