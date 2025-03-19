class Solution {
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        vector<vector<int>> results;
        /* results.push_back(vector<int>()); */
        /* results[0].push_back(nums[0]); */
        for(int i = 0;i < nums.size();++i)//for(int i = 1;i < nums.size();++i)
        {
            int key = nums[i];
            bool isInsert = false;
            for(int j = 0;j < results.size();++j)
            {
                auto it = std::find(results[j].begin(),results[j].end(),key);
                if(it == results[j].end() && !isInsert)
                {
                    results[j].push_back(key);
                    isInsert = true;
                }
            }
            if(!isInsert)
            {
                results.push_back(vector<int>{key});
                isInsert = true;
            }
        }
        return results;
    }
};
