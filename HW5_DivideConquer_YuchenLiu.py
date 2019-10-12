# -*- coding: utf-8 -*-
"""
Created on Sat Oct 12 15:59:40 2019

@author: Ethan
"""

# =============================================================================
# Q1 LeetCode 167. Two Sum II
# =============================================================================
class Solution(object):
    def twosum(self, numbers, target):
        '''
        :type numbers: List[int]
        :type target: int
        :rtype: List[int]
        '''        
        i = 0
        j = len(numbers) - 1
        while i<j:
            two_sum = numbers[i] + numbers[j]
            if two_sum == target:
                break
            elif two_sum > target:
                j -=1
            else:
                i += 1
        return [i+1, j+1]
    
# =============================================================================
# Q2 LC 441. Arranging Coins
# =============================================================================
class Solution(object):
    def arrangeCoins(self, n):
        l, r = 0, n
        while l <= r:
            m = (l+r)/2
            if m* (m+1)/2 > n:
                r =m - 1
            else:
                l = m + 1
        return r
            
                
# =============================================================================
# Q3 LC 973. Medium K Closest Points to Origin
# =============================================================================
class Solution(object):
    def kClosest(self, points, K):
        points.sort(key = lambda x: x[0]**2 + x[1]**2)
        return points[:K]




# =============================================================================
# Q4 LC 932. Beautiful Array
# =============================================================================

class Solution(object):
    def beautifulArray(self, N):
        """
        :type N: int
        :rtype: List[int]
        """
        res = [1]
        while len(res) < N:
            res = [2 * i - 1 for i in res] + [2 * i  for i in res]
        return [i for i in res if i <= N]


# =============================================================================
# Q5 Count of Range Sum
# =============================================================================
class Solution(object):
    def countRangeSum(self, nums, lower, upper):
        """
        :type nums: List[int]
        :type lower: int
        :type upper: int
        :rtype: int
        """
        sums = nums[:]
        for x in range(1, len(sums)):
            sums[x] += sums[x - 1]
        osums = sorted(set(sums))
        ft = FenwickTree(len(osums))
        ans = 0
        for sumi in sums:
            left = bisect.bisect_left(osums, sumi - upper)
            right = bisect.bisect_right(osums, sumi - lower)
            ans += ft.sum(right) - ft.sum(left) + (lower <= sumi <= upper)
            ft.add(bisect.bisect_right(osums, sumi), 1)
        return ans

class FenwickTree(object):
    def __init__(self, n):
        self.n = n
        self.sums = [0] * (n + 1)
    def add(self, x, val):
        while x <= self.n:
            self.sums[x] += val
            x += self.lowbit(x)
    def lowbit(self, x):
        return x & -x
    def sum(self, x):
        res = 0
        while x > 0:
            res += self.sums[x]
            x -= self.lowbit(x)
        return res



# =============================================================================
# Q6 Count of Smaller Numbers After Self
# =============================================================================
class Solution(object):
    def countSmaller(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        idxes = {}
        for k, v in enumerate(sorted(set(nums))):
            idxes[v] = k + 1
        iNums = [idxes[x] for x in nums]
        ft = FenwickTree(len(iNums))
        ans = [0] * len(nums)
        for i in range(len(iNums) - 1, -1, -1):
            ans[i] = ft.sum(iNums[i] - 1)
            ft.add(iNums[i], 1)
        return ans

class FenwickTree(object):
    def __init__(self, n):
        self.n = n
        self.sums = [0] * (n + 1)

    def add(self, x, val):
        while x <= self.n:
            self.sums[x] += val
            x += self.lowbit(x)

    def lowbit(self, x):
        return x & -x

    def sum(self, x):
        res = 0
        while x > 0:
            res += self.sums[x]
            x -= self.lowbit(x)
        return res









            