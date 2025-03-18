#include<math.h>
bool isZhi(int num)
{
    if(num < 2) return false;
    for(int i = 2;i <= sqrt(num) ;++i)
    {
        if(num % i == 0)
        {
            return false;
        }
    }
    return true;
};
class Solution {
public:
    int diagonalPrime(vector<vector<int>>& nums) {
        int max = 0;
        int n = nums.size();
        for(int i = 0; i < n ;++i)
        {
            if(isZhi(nums[i][i]) && nums[i][i] > max)
            {
                max = nums[i][i];
            }
        }
        for(int i = 0,j = n - 1;i < n ;++i,--j)
        {
            if(isZhi(nums[i][j]) && nums[i][j] > max)
            {
                max = nums[i][j];
            }
        }
        return max;
    }
};
