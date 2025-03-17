#include <iostream>
#include <string.h>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>

using std::shared_ptr;
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

//程序接口[可选]:
class TextQuery
{
public:
    //......
    void readFile(const string & filename)
    {
        ifstream ifs(filename);
        if(!ifs.good())
        {
            cerr << "File is broken" << endl;
            return;
        }
        string line;
        int lineNum = 0;
        while(getline(ifs,line))
        {
            _lines.push_back(line);
            istringstream iss(line);
            string word;
            while(iss >> word)
            {
                (*_wordNumbers[word]).insert(lineNum);
                ++(*_dict)[word];
            }
        ++lineNum;
        }
        ifs.close();
    }
    void query(const string & word)
    {
        string temp = word;
        auto it = _dict.find(temp);
        if(it == _dict.end())
        {
            cout << "Word not found!" << endl;
            return;
        }
        cout << temp << " occurs " << it->second << " times." << endl;
        const set<int>& lineNumber = _wordNumbers[temp];
        for(auto it = lineNumber.begin(); it!= lineNumber.end(); ++it)
        {
            int currentLine = *it;
            cout << "(line " << currentLine + 1 << ") " << _lines[currentLine] << endl;
        }
    }


private:
    //......
    shared_ptr<map<string,int>> _dict(new map<string,int>());
    shared_ptr<string> _lines;//O(1)
    map<string, shared_ptr<int> > _wordNumbers;//the the
};


//程序测试用例
int main(int argc, char *argv[])
{
    string queryWord;
    cout << "Pls input a word:";
    cin >> queryWord;

    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
    return 0;
}

