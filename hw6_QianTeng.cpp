/**************************************************
 * 53. Maximum Subarray
**************************************************/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_sum_before{0};
        int max_sum_global{INT_MIN};
        for(auto num: nums) 
        {
            max_sum_global = max(max_sum_global, max_sum_before + num);
            max_sum_before = max(max_sum_before + num, 0);
        }
        
        return max_sum_global;
    }
};

 /**************************************************
 * 746. Min Cost Climbing Stairs
****************************************************/
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        // The description is not clear. We need to return the cost to reach floor
        // indexed at n, i.e. the (n + 1)th floor.
        int cost_minus2{0};
        int cost_minus1{0};
        int minCost{0};      // min cost to reach floor indexed at i
        for(int i{2}; i <= cost.size(); ++i)
        {
            minCost = min(cost_minus1 + cost[i - 1], cost_minus2 + cost[i - 2]);
            cost_minus2 = cost_minus1;
            cost_minus1 = minCost;
        }
        return minCost;
    }
};

 /**************************************************
 * 213. House Robber II
****************************************************/
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if(!n) return 0;
        if(n == 1) return nums[0];
            
        return max(Helper(nums, 0, n - 2), Helper(nums, 1, n - 1));
    }
    
private:
    int Helper(vector<int>& nums, int low, int high)
    {
        int rob0{0};
        int rob1{0};
        int rob2{nums[low]};
        for(int i{low + 1}; i <= high; ++i)
        {
            rob0 = rob1;
            rob1 = rob2;
            rob2 = max(rob0 + nums[i], rob1);
        }
        
        return rob2;
    }
};

 /**************************************************
 * 1143. Longest Common Subsequence
****************************************************/
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if(text1.size() < text2.size())
            swap(text1, text2);
        vector<int> longestCS(text2.size(), 0);
        for(int i{0}; i < text1.size(); ++i)
        {
            int longest_prev{0}; // keeps LCS[i - 1][j - 1]
            for(int j{0}; j < text2.size(); ++j)
            {
                int temp{longestCS[j]};  
                if(text1[i] == text2[j])
                    longestCS[j] = longest_prev + 1;
                else if(j > 0)
                    longestCS[j] = max(longestCS[j - 1], longestCS[j]);
                longest_prev = temp; 
            }
        }
        
        return longestCS[text2.size() - 1];
    }
};

 /**************************************************
 * 1092. Shortest Common Supersequence
****************************************************/
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        if(str1.size() < str2.size())
            swap(str1, str2);
        int m = static_cast<int>(str1.size());
        int n = static_cast<int>(str2.size());
        vector<vector<int>> lcs(m + 1, vector<int>(n + 1, 0));
        for(int i{1}; i <= m; ++i)
        {
            for(int j{1}; j <= n; ++j)
            {
                if(str1[i - 1] == str2[j - 1])
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                else
                    lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
        
        string res;
        for(int i{m}, j{n}; i || j;)
        {
            if( i > 0 && lcs[i][j] == lcs[i - 1][j])
            {
                res = str1[--i] + res;
            }
            else if( j > 0 && lcs[i][j] == lcs[i][j - 1])
            {
                res = str2[--j] + res;
            }
            else 
            {
                res = str1[--i] + res;
                --j;
            }
        }
        
        return res;
    }
};