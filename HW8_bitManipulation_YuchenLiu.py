# -*- coding: utf-8 -*-
"""
Created on Sat Nov  2 21:13:02 2019

@author: Ethan
"""


# =============================================================================
# Q1 Hamming Distance
# =============================================================================
class Solution(object):
    def hammingDistance(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        return bin(x ^ y).count('1')

# =============================================================================
# Q2 Reverse Bits
# =============================================================================
    
class Solution(object):
    def reverseBits(self, n):
        """
        :type n: int
        :rtype: int
        """
        b = bin(n)[:1:-1]
        return int(b + '0'*(32-len(b)), 2)


# =============================================================================
# Q3 Maximum XOR of Two Numbers in an Array
# =============================================================================

class Solution(object):
    def findMaximumXOR(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        ans = mask = 0
        for x in range(32)[::-1]:
            mask += 1 << x
            prefixSet = set([n & mask for n in nums])
            temp = ans | 1 << x
            for prefix in prefixSet:
                if temp ^ prefix in prefixSet:
                    ans = temp
                    break
        return ans

# =============================================================================
# Q4 Repeated DNA Sequences
# =============================================================================

class Solution(object):
    # @param s, a string
    # @return a list of strings
    def findRepeatedDnaSequences(self, s):
        ans = []
        valCnt = dict()
        map = {'A' : 0, 'C' : 1, 'G': 2, 'T' : 3}
        sum = 0
        for x in range(len(s)):
            sum = (sum * 4 + map[s[x]]) & 0xFFFFF
            if x < 9:
                continue
            valCnt[sum] = valCnt.get(sum, 0) + 1
            if valCnt[sum] == 2:
                ans.append(s[x - 9 : x + 1])
        return ans


# =============================================================================
# Q5 Bitwise AND of Numbers Range
# =============================================================================

class Solution(object):
    # @param m, an integer
    # @param n, an integer
    # @return an integer
    def rangeBitwiseAnd(self, m, n):
        p = 0
        while m != n:
            m >>= 1
            n >>= 1
            p += 1
        return m << p


# =============================================================================
# Q6 Number of Valid Words for Each Puzzle
# =============================================================================

class Solution(object):
    def findNumOfValidWords(self, words, puzzles):
        """
        :type words: List[str]
        :type puzzles: List[str]
        :rtype: List[int]
        """
        dic_words = {}
        for word in words:
            newword = ''.join(sorted(list(set(list(word)))))
            dic_words[newword] = dic_words.setdefault(newword,0) + 1
        res = []
        for puzzle in puzzles:
            count = 0
            first = puzzle[0]
            puzzle = ''.join(sorted(list(set(list(puzzle[1:])))))
            if puzzle.find(first) != -1:
                inx = puzzle.find(first)
                puzzle = puzzle[:inx] + puzzle[inx+1:]
            if first in dic_words:
                count += dic_words[first]
            queue = []
            for (i,v) in enumerate(puzzle):
                queue.append((v,i))
            while len(queue) > 0:
                v,i = queue.pop(0)
                if i == len(puzzle) - 1:
                    key = ''.join(sorted(list(first + v)))
                    if key in dic_words:
                        count += dic_words[key]
                    continue
                queue.append((v,i+1))
                queue.append((v + puzzle[i+1],i+1))
            res.append(count)
        return res
