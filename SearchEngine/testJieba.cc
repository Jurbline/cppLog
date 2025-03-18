#include "WordSegmentation.h"
 #include <iostream>
 #include <string>
 #include <vector>
 using std::cout;
 using std::endl;
 using std::string;
 using std::vector;
 int main()
 {
    string str = "一战11408，然后进厂拧螺丝";
    WordSegmentation wordSeg;
    vector<string> results = wordSeg(str);
    cout << "分词结果如下:" << endl;
    for(auto it = results.begin(); it != results.end(); ++it)
    {
        cout << *it <<" ";
    }
    cout << endl;
    return 0;
 }
