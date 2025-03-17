#include <iostream>
#include <list>
#include <string>

using std::string;
using std::list;
using std::endl;
using std::cout;

class Student
{
public:
    void TotalScore()
    {
        _sum = _chineseScore + _mathScore + _englishScore;
    }

    void print() const
    {
        cout << "Name = " << _name
        << " , Age = " << _age
        << " , Chinese = " << _chineseScore
        << " , Math = " << _mathScore
        << " , English = " << _englishScore
        << " , TotalScore = " << _sum << endl;
    }
    Student(const string &name,int age,int cns,int ms,int es)
    :_name(name)
    ,_age(age)
    ,_chineseScore(cns)
    ,_mathScore(ms)
    ,_englishScore(es)
    {
        TotalScore();
    }
    friend struct CompareList;
private:
    string _name;
    int _age;
    int _chineseScore;
    int _mathScore;
    int _englishScore;
    int _sum;
};
struct CompareList
{
    bool operator()(const Student &lhs,const Student &rhs)
    {
        if(lhs._sum == rhs._sum)
        {
            return lhs._chineseScore > rhs._chineseScore;
        }
        else
        {
            return lhs._sum > rhs._sum;
        }
    }
};

void test()
{
    list<Student> Stu;
    Stu.push_back(Student("Xiao Ming",19,109,107,133));
    Stu.push_back(Student("Xiao Hong",18,142,131,128));
    Stu.push_back(Student("Huang Hao",19,137,134,138));
    Stu.push_back(Student("Li Ming",17,127,114,123));
    Stu.push_back(Student("Zhang Wei",17,111,115,121));
    Stu.push_back(Student("Wang Fei",18,140,137,132));
    Stu.sort(CompareList());
    for(auto &item : Stu)
    {
        item.print();
    }
}
int main()
{
    test();
    return 0;
}

