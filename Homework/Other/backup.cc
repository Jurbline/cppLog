#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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
                int index = isWordExist(word);
                if (index != -1)
                {
                    _dict[index]._frequency++;
                }
                else
                {
                    _dict.push_back(Record(word));
                }
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
        for(int i = 0 ; i<_dict.size();++i)
        {
            const Record &temp = _dict[i];
            ofs << temp._word << " " << temp._frequency << endl;
        }
        cout << "Store Success!" << endl;
    }
private:
    vector<Record> _dict;
    int isWordExist(const string &word)
    {
        for(int i = 0;i < _dict.size();++i)
        {
            if (_dict[i]._word == word)
            {
                return i;
            }       
        }
        return -1;
    }
};
int main()
{
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.store("dict.txt");
    return 0;
}

