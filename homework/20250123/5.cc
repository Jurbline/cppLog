#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::ifstream;
using std::stringstream;
void readRules(const string &filename,unordered_map<string,string> &rules)
{
    ifstream ifs(filename);
    string oldWord,newWord;
    while(ifs >> oldWord)
    {
        getline(ifs,newWord);
        if(!newWord.empty() && newWord[0] == ' ')
        {
            newWord.erase(0,1);
        }
        rules[oldWord] = newWord;
    }
}

void processFile(const string &filename,const unordered_map<string,string> &rules)
{
    ifstream ifs(filename);
    string line;
    while(getline(ifs,line))
    {
        stringstream ss(line);
        string word;
        bool first_word = true;

        while(ss >> word)
        {
            if(!first_word)
            {
                cout << " ";
            }
            first_word = false;
            auto it = rules.find(word);
            if(it != rules.end())
            {
                cout << it->second;
            }
            else
            {
                cout << word;
            }
        }
        cout << endl;
    }
}

void test()
{
    unordered_map<string,string> um;
    readRules("map.txt",um);
    processFile("file.txt",um);
}
int main()
{
    test();
    return 0;
}

