//如果数组中某个元素的频率超过数组长度的一半，最小长度就是2 * maxfreq - n
//否则为n % 2
class Solution {
public:
    int minLengthAfterRemovals(vector<int>& nums) {
        int n = nums.size();
        //统计频率
        unordered_map<int,int> freq;
        for(auto num : nums)
        {
            freq[num]++;
        }
        int maxFreq = 0;
        for(auto &it : freq)
        {
            if(it.second > maxFreq) maxFreq = it.second;
        }
        if(maxFreq > (n/2)) return (2 * maxFreq - n);
        else return n % 2;
    }
};
