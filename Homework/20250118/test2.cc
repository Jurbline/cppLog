#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>

using std::cin;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cerr;
using std::set;
using std::shared_ptr;

// 程序接口
class TextQuery {
public:
    // 读取文件并构建索引
    void readFile(const string &filename) {
        ifstream ifs(filename);
        if (!ifs.good()) {
            cerr << "File is broken" << endl;
            return;
        }

        string line;
        int lineNum = 0;

        // 使用 new 创建 shared_ptr
        _lines = shared_ptr<vector<string>>(new vector<string>());

        while (getline(ifs, line)) {
            _lines->push_back(line);
            istringstream iss(line);
            string word;

            // 对每行中的每个单词处理
            while (iss >> word) {
                // 初始化_word2Numbers为shared_ptr
                if (!_word2Numbers[word]) {
                    _word2Numbers[word] = shared_ptr<set<int>>(new set<int>());
                }
                _word2Numbers[word]->insert(lineNum);
                ++_dict[word];
            }
            ++lineNum;
        }
        ifs.close();
    }

    // 查询单词
    void query(const string &word) {
        string temp = word;
        auto it = _dict.find(temp);

        if (it == _dict.end()) {
            cout << "Word not found!" << endl;
            return;
        }

        // 输出单词出现的次数
        cout << temp << " occurs " << it->second << " times." << endl;

        // 获取该单词出现的行号集合
        const shared_ptr<set<int>> &lineNumber = _word2Numbers[temp];

        // 输出每次出现的行号及内容
        for (auto it = lineNumber->begin(); it != lineNumber->end(); ++it) {
            int currentLine = *it;
            cout << "(line " << currentLine + 1 << ") " << (*_lines)[currentLine] << endl;
        }
    }

private:
    shared_ptr<vector<string>> _lines; // 使用 shared_ptr 管理行内容
    map<string, shared_ptr<set<int>>> _word2Numbers; // 单词与行号集合的映射
    map<string, int> _dict; // 单词的出现次数
};

// 程序测试用例
int main(int argc, char *argv[]) {
    string queryWord;
    cout << "Pls input a word: ";
    cin >> queryWord;

    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
    return 0;
}

