# -*- coding: utf-8 -*-
"""
Created on Mon Oct 14 23:18:49 2019

@author: Ethan
"""
# =============================================================================
# Q1 Max Subarray
# =============================================================================

class Solution(object):
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if max(nums) < 0:
            return max(nums)
        local_max, global_max = 0, 0
        for num in nums:
            local_max = max(0, local_max + num)
            global_max = max(local_max, global_max)
            
            
        return global_max
    
# =============================================================================
# Q2 Min cost climbing stairs
# =============================================================================

class Solution(object):
    def minCostClimbingStairs(self, cost):
        """
        :type cost: List[int]
        :rtype: int
        """
        N = len(cost)
        cost.append(0)
        dp = [0] * (N+1)
        for i in range(2, len(cost)):
            dp[0] = cost[0]
            dp[1] = cost[1]
            dp[i] = min(dp[i-2], dp[i-1]) + cost[i]
        return dp[-1]
        
        
#     
#if __name__ ==  "__main__":
#    cost = [1,2,3,4,5]
#    solu = Solution()    
#    print(solu.minCostClimbingStairs(cost))
#    print(dp)
#    
#cost = [1,2,3,4,5]
#N = len(cost)
#cost.append(0)
#dp = [0] * (N+1) 
#for i in range(2, len(cost)):
#    dp[0] = cost[0]
#    dp[1] = cost[1]
#    dp[i] = min(dp[i-2], dp[i-1]) + cost[i]

# =============================================================================
# Q3 House robber ii        
# =============================================================================
        
class Solution(object):
    def rob(self, nums):        
        if not nums:
            return 0
        if len(nums) <= 2: return max(nums)
        return max(self.rob_row(nums[1:]), self.rob_row(nums[:-1]))
    
    def rob_row(self, nums):
        dp = [0] * len(nums)
        dp[0] = nums[0]
        dp[1] = max(nums[0], nums[1])
        for i in range(2, len(nums)):
            dp[i] = max(dp[i-1], dp[i-2] + nums[i])
        return dp[-1]
        
        
        
        
# =============================================================================
# Q4 Longest Common Subsequence        
# =============================================================================
class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        n,m=len(text1),len(text2)
        dp=[[0]*(m+1) for _ in range(n+1)]
        for i in range(n):
            for j in range(m):
                if text1[i]==text2[j]:
                    dp[i+1][j+1]=dp[i][j]+1
                else:
                    dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j])
        return dp[-1][-1]
    
        
        
        
        
        
a = [[0 for i in range(5)] for j in range(3)]        
        
        
class Solution:        
    def shortestCommonSupersequence(self, A, B):
        def lcs(A, B):
            n, m = len(A), len(B)
            dp = [["" for _ in range(m + 1)] for _ in range(n + 1)]
            for i in range(n):
                for j in range(m):
                    if A[i] == B[j]:
                        dp[i + 1][j + 1] = dp[i][j] + A[i]
                    else:
                        dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1], key=len)
            return dp[-1][-1]
    
        res, i, j = "", 0, 0
        for c in lcs(A, B):
            while A[i] != c:
                res += A[i]
                i += 1
            while B[j] != c:
                res += B[j]
                j += 1
            res += c
            i, j = i + 1, j + 1
        return res + A[i:] + B[j:]        
        
        
        
        
        
        
        
        
        
        
        
        