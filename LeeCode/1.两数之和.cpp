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
        vector<int> res;
        for(size_t i=0; i < nums.size();++i){
            for (size_t j = i+1; j < nums.size(); ++j)
            {
                /* code */
                if(nums.at(i)+nums.at(j)==target)
                {
                    res.push_back(i);
                    res.push_back(j);
                    break;
                }
            }
            
        }
        return res;
    }
};
// @lc code=end

