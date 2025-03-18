class Solution {
public:
    long long countOfSubstrings(string word, int k) {
        set<char> yuan = {'a','e','i','o','u'};
        auto count = [&](int m)->long long{
            int n = word.size(),Fu = 0;
            long long res = 0;
            map<char,int> occur;//窗口中元音的种类和数量
            for(int i = 0,j = 0;i < n; ++i)//i为滑动窗口的左指针，j为滑动窗口的右指针
            {
                while(j < n && (Fu < m || occur.size() < yuan.size()))
                {
                    if(yuan.count(word[j]))
                    {
                        occur[word[j]]++;
                    }
                    else
                    {
                        Fu++;
                    }
                    j++;
                }
                if(Fu >= m && occur.size() == yuan.size())
                {
                    res+= n - j + 1;
                }
                if(yuan.count(word[i]))//i在窗口之外
                {
                    occur[word[i]]--;
                    if(occur[word[i]] == 0)
                    {
                        occur.erase(word[i]);
                    }
                }else{
                    Fu--;
                }
            }
            return res;
        };
        return count(k) - count(k + 1);
    }
};
