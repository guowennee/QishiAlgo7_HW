# -*- coding: utf-8 -*-
"""
Created on Mon Sep  9 22:37:29 2019

@author: Ethan
"""

# =============================================================================
# Question 1 Find Smallest Letter Greater Than Target
#Time complexity: O(log N), Space complexity: O(1)
# =============================================================================

class Solution:
    def nextGreatestLetter(self, letters, target):
        """
        :type letters: List[str]
        :type target: str
        :rtype: str
        """
        left, right = 0, len(letters)
        while left < right:
            mid = left + (right - left)/2
            if letters[mid] <= target:
                left = mid +1
            else:
                right = mid
        return letters[left % len(letters)]
    
# =============================================================================
# Q2 Heaters
#Time complexity: O(N log N), Space complexity: O(1)
# =============================================================================
class Solution:
    """
    @param houses: positions of houses
    @param heaters: positions of heaters
    @return: the minimum radius standard of heaters
    """
    def findRadius(self, houses, heaters):
        heaters.sort()
        ans = 0
        for house in houses:
            ans = max(ans, self.closestHeater(house, heaters))
        return ans
    
    def closestHeater(self, house, heaters):
        start = 0
        end = len(heaters)-1
        while start +1 < end:
            mid = start + (end - start)//2
            if heaters[mid] == house:
                return 0
            elif heaters[mid] < house:
                start = mid
            else:
                end = mid
        return min(abs(house - heaters[start]), abs(heaters[end] - house))


# =============================================================================
# Question 3 Search a 2D Matrix
# O(log(m*n))
# =============================================================================
class Solution:
    def searchMatrix(self, matrix, target):
        """
        :type letters: List of lists of int
        :type target: int
        :rtype: boolean
        """        
        if len(matrix) == 0:
            return False
        n, m = len(matrix), len(matrix[0])
        start, end = 0, n*m -1
        while start +1 < end:
            mid = (start + end)//2  ##Py3 is difference from Py2 , /2 generates a float
            i,j = mid//m, mid % m
            if matrix[i][j] < target:
                start = mid
            else:
                end = mid
        i,j = start//m, start%m
        if matrix[i][j] == target:
            return True
        
        i,j = end//m, end%m
        if matrix[i][j] == target:
            return True
        
        return False


        
# =============================================================================
# Q4 Find First and Last Position of Element in Sorted Array   
# O(log(n))
# =============================================================================
class Solution:
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
    def searchRange(self, nums, target):
        left = self.lower_bound(nums, target)
        right = self.upper_bound(nums,target)
        if left == right:
            return [-1,-1]
        else:
            return [left, right-1]
    
    def lower_bound(self,nums, target):
        # find in range [left, right)
        left, right = 0, len(nums)
        while left < right:
            mid = (left + right)//2
            if nums[mid] < target:
                left = mid +1
            else:
                right = mid
        return left
    
    def upper_bound(self,nums, target):
        # find in range [left, right)
        left, right = 0, len(nums)
        while left < right:
            mid = (left + right)//2
            if nums[mid] <= target:
                left = mid +1
            else:
                right = mid
        return left       



# =============================================================================
# Q5 Find K-th Smallest Pair Distance
# O(n log(w) + n log(n))
# =============================================================================
class Solution:
    def smallestDistancePair(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """    
        nums.sort()
        start, end = 0, nums[-1] - nums[0]
        while start +1 < end:
            mid = (start + end)//2
            if self.count(nums, mid) < k:
                start = mid
            else:
                end = mid
        return start if self.count(nums, start) >= k else end

    def count(self, nums, mid):
        left, right, ans = 0,0,0
        while right != len(nums):
            while nums[right] - nums[left] > mid:
                left +=1
            ans += right - left
            right += 1
        return ans
        
# =============================================================================
# Q6 Google interview question    
# =============================================================================
class Solution:
    def minmaxGasDist(self, st, K):
        """
        :type stations: List[int]
        :type K: int
        :rtype: float
        """
        lf = 1e-6
        rt = st[-1] - st[0]
        eps = 1e-7
        while rt - lf > eps:
            mid = (rt + lf) / 2
            cnt = 0
            for a, b in zip(st, st[1:]):
               cnt += (int)((b - a) / mid)
            if cnt <= K: rt = mid
            else: lf = mid
        return rt

#if __name__ == '__main__':
#    solu = Solution()
#    st= [5,8,10,25,28,31,72,80,85,100]
#    K = 8
#    print(solu.minmaxGasDist(st,K))














           
          
        
        
        
        
        
        