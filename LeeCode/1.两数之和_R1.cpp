/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        int num_len=nums.size();
        for(int i=0; i < num_len;++i){
            for (int j = i+1; j < num_len; ++j)
            {
                /* code */
                if(nums.at(i)+nums.at(j)==target)
                {
                    return {i,j};
                }
            }
            
        }
        return {};
    }
};
// @lc code=end

