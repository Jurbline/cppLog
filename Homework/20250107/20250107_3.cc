#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace std;

struct Record
{
    string _word;
    int _frequency;
    Record(const string &word)
    :_word(word)
    ,_frequency(1)
    {

    }
};

class Dictionary
{
public:
    void read(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs.good())
        {
            cerr << "The File is broken!" << endl;
            return;
        }
        string line;
        while(getline(ifs,line))
        {
            istringstream iss(line);
            string word;
            while(iss >> word)
            {
                ++_dict[word];
            }
        }
    ifs.close();
    }
    void store(const string &filename)
    {
        ofstream ofs(filename);
        if(!ofs)
        {
            cerr << "Output File Error" << endl;
            return;
        }
        for(auto it = _dict.begin(); it !=_dict.end();++it)
        {
            ofs << it->first << " " << it->second << endl;
        }
        cout << "Store Success!" << endl;
    }
private:
    unordered_map<string,int> _dict;
};
int main()
{
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.store("dict.txt");
    return 0;
}

