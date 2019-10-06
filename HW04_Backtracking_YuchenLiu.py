# -*- coding: utf-8 -*-
"""
Created on Thu Oct  3 22:35:06 2019

@author: Ethan
"""

# =============================================================================
# 1. Binary Watch
# =============================================================================
class Solution:
    def readBinaryWatch(self, num):
        """
        :type num: int
        :rtype: List[str]
        """
        ans = []
        for h in range(12):
            for m in range(60):
                if (bin(h)+ bin(m)).count('1') == num:
                    ans.append('%d:%02d' % (h, m))
        return ans

# =============================================================================
# 2. Combination Sum
# =============================================================================
class Solution:
    # @param candidates, a list of integers
    # @param target, integer
    # @return a list of lists of integers
    def DFS(self, candidates, target, start, valuelist):
        length = len(candidates)
        if target == 0:
            return Solution.ret.append(valuelist)
        for i in range(start, length):
            if target < candidates[i]:
                return
            self.DFS(candidates, target - candidates[i], i, valuelist + [candidates[i]])
        
    def combinationSum(self, candidates, target):
        candidates.sort()
        Solution.ret = []
        self.DFS(candidates, target, 0, [])
        return Solution.ret
    
    
# =============================================================================
# 3. Permutations
# =============================================================================
    
    
class Solution:
    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        visited = [0] * len(nums)
        res = []
        
        def dfs(path):
            if len(path) == len(nums):
                res.append(path)
            else:
                for i in range(len(nums)):
                    if not visited[i]:
                        visited[i] = 1
                        dfs(path + [nums[i]])
                        visited[i] = 0
        
        dfs([])
        return res
    
# =============================================================================
# 4. Permutations 2
# =============================================================================
    

class Solution:
    
    def permuteUnique(self, num):
        length = len(num)
        if length == 0: return []
        if length == 1: return [num]
        num.sort()
        res = []
        previousNum = None
        for i in range(length):
            if num[i] == previousNum: continue
            previousNum = num[i]
            for j in self.permuteUnique(num[:i] + num[i+1:]):
                res.append([num[i]] + j)
        return res
    
# =============================================================================
#  5. N-Queens 2   
# =============================================================================
class Solution:
    # @return an integer
    def __init__(self):
        self.count=0
    def check(self,k,j,board):
        for i in range(k):
            if board[i]==j or abs(k-i)==abs(board[i]-j):
                return False
        return True
    def dfs(self,depth,board,n):
        if depth==n:
            self.count+=1
        for row in range(n):
            if self.check(depth,row,board):
                s='.'*n
                board[depth]=row
                self.dfs(depth+1,board,n)
    def totalNQueens(self, n):
        board=[-1 for i in range(n)]
        self.dfs(0,board,n)
        return self.count



# =============================================================================
# 6. Implement a queue class given a stack class
# =============================================================================

class Queue:
    # initialize your data structure here.
    def __init__(self):
        self.inStack = []
        self.outStack = []

    # @param x, an integer
    # @return nothing
    def push(self, x):
        self.inStack.append(x)

    # @return nothing
    def pop(self):
        self.peek()
        self.outStack.pop()

    # @return an integer
    def peek(self):
        if not self.outStack:
            while self.inStack:
                self.outStack.append(self.inStack.pop())
        return self.outStack[-1]

    # @return an boolean
    def empty(self):
        return len(self.inStack) + len(self.outStack) == 0