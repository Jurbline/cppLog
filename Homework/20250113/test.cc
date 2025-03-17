#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

class TextQuery {
public:
    // 读取文件内容
    void readFile(const string &filename) {
        ifstream ifs(filename);
        if (!ifs) {
            cerr << "File could not be opened!" << endl;
            return;
        }

        string line;
        int lineNumber = 0;
        while (getline(ifs, line)) {
            _lines.push_back(line); // 保存每一行
            stringstream ss(line);
            string word;
            while (ss >> word) {
                // 手动将单词转为小写
                for (char &ch : word) {
                    ch = tolower(ch); // 转换每个字符为小写
                }
                _wordNumbers[word].insert(lineNumber);
                _dict[word]++; // 记录单词出现的次数
            }
            lineNumber++;
        }
        ifs.close();
    }

    // 查询某个单词出现的行号和次数
    void query(const string &word) {
        // 将查询单词转为小写
        string queryWord = word;
        for (char &ch : queryWord) {
            ch = tolower(ch); // 转换每个字符为小写
        }

        // 检查单词是否在字典中
        auto it = _dict.find(queryWord);
        if (it == _dict.end()) {
            cout << "Word not found!" << endl;
            return;
        }

        // 输出该单词出现的次数
        cout << queryWord << " occurs " << it->second << " times." << endl;

        // 输出该单词出现的行号及相应行内容
        const set<int>& lineNumbers = _wordNumbers[queryWord];
        for (int lineNumber : lineNumbers) {
            cout << "(line " << lineNumber + 1 << ") " << _lines[lineNumber] << endl;
        }
        cout << "---------------------------------------------" << endl;
    }

private:
    vector<string> _lines; // 存储文件每一行
    map<string, set<int>> _wordNumbers; // 记录每个单词所在的行号
    map<string, int> _dict; // 记录每个单词出现的次数
};

int main() {
    string queryWord;
    cout << "Enter word to query: ";
    cin >> queryWord;

    TextQuery tq;
    tq.readFile("china_daily.txt"); // 这里可以替换为其他文件名
    tq.query(queryWord);

    return 0;
}

