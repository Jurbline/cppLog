#include <iostream>
#include <memory>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using std::vector;
using std::cerr;
using std::shared_ptr;
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::ifstream;
using std::istringstream;
using std::set;
using std::map;

class TextQuery
{
public:
    void readFile(const string filename)
    {
        ifstream ifs(filename);
        if(!ifs)
        {
            cerr << "File is broken" << endl;
            return;
        }
        string line;
        int lineNum = 0;
        _lines = shared_ptr<vector<string>>(new vector<string>());

        while(getline(ifs,line))
        {
            _lines->push_back(line);
            istringstream iss(line);
            string word;
            while(iss >> word)
            {
                processWord(word);
                if(!_word2Numbers[word])
                {
                    _word2Numbers[word] = shared_ptr<set<int>>(new set<int>());
                }
                _word2Numbers[word]->insert(lineNum);
                ++_dict[word];
            }
            ++lineNum;
        }
        ifs.close();
    }
    void query(const string &word)
    {
        string temp = word;
        auto it = _dict.find(temp);
        if(it == _dict.end())
        {
            cout << "Word not found" << endl;
            return;
        }
        cout << temp << " occurs " << it->second << " times." << endl;
        const shared_ptr<set<int>> &lineNumber = _word2Numbers[temp];
        for(auto it = lineNumber->begin();it != lineNumber->end();++it)
        {
            int currentLine = *it;
            cout << "(line " << currentLine + 1 << ") " << (*_lines)[currentLine] << endl;
        }

    }
    void processWord(string &word)
    {
        string processed;
        for (size_t i = 0;i < word.size(); ++i)
        {
            char ch = word[i];
            if(isalpha(ch))
            {
                processed += tolower(ch);
            }
        }
        word = processed;
    }
private:     
    map<string,int> _dict;
    shared_ptr<vector<string>> _lines; 
    map<string, shared_ptr<set<int>> > _word2Numbers;
};
int main()
{
    string queryWord;
    cout << "Pls input a word:";
    cin >> queryWord;
    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
    return 0;
}

