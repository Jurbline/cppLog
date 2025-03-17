#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::string;

class Person
{
public:
    Person(const string &name)
    :_name(name)
    ,_score(10,0)
    {

    }
    ~Person()
    {

    }
    string _name;
    deque<int> _score;
};

void test()
{
    vector<Person> per = {
        Person("A"),
        Person("B"),
        Person("C"),
        Person("D"),
        Person("E"),
    };
    vector<vector<int>> scr = {
        {81,80,83,94,82,86,82,80,95,92},
        {92,94,91,92,88,90,85,87,83,89},
        {88,82,84,82,89,90,97,92,91,87},
        {77,81,82,83,82,86,85,93,81,92},
        {81,82,81,80,82,89,91,80,90,92}
    };
    for(size_t i = 0;i < per.size();++i)
    {
        per[i]._score = deque<int>(scr[i].begin(),scr[i].end());
    }
    for(const auto &it : per)
    {
        deque<int> sortScore = it._score;
        sort(sortScore.begin(),sortScore.end());
        sortScore.pop_back();
        sortScore.pop_front();
        int totalScore = 0;
        for(const auto &it : sortScore)
        {
            totalScore += it;
        }
        double averageScore = totalScore / sortScore.size();
        cout << "Player: " << it._name << ",Score: " << averageScore << endl;
    }
}

int main()
{
    test();
    return 0;
}

