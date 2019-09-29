# -*- coding: utf-8 -*-
"""
Created on Sat Sep 28 16:38:45 2019

@author: Ethan
"""

# =============================================================================
# Q1 Minimum Depth of Binary Tree
# =============================================================================
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def minDepth(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        if root == None:
            return 0

        if not root.left:
            return 1 + self.minDepth(root.right)
        elif not root.right:
            return 1 + self.minDepth(root.left)
        else:
            return 1 + min(self.minDepth(root.left), self.minDepth(root.right))




# =============================================================================
# Q2 Path Sum
# =============================================================================

class Solution(object):
    def hasPathSum(self, root, sum):
        """
        :type root: TreeNode
        :type sum: int
        :rtype: bool
        """
        if not root:
            return False
        if not root.left and not root.right:
            return True if sum == root.val else False
        else:
            return self.hasPathSum(root.left, sum-root.val) or self.hasPathSum(root.right, sum-root.val)


# =============================================================================
# Q3 Binary Tree Level Order Traversal
# =============================================================================
class Solution(object):
    def levelOrder(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        res = []
        self.dfs(root, 0, res)
        return res

    def dfs(self, root, depth, res):
        if root == None:
            return res
        if len(res) < depth+1:
            res.append([])
        res[depth].append(root.val)
        self.dfs(root.left, depth+1, res)
        self.dfs(root.right, depth+1, res)



# =============================================================================
# Q4 Keys and Rooms
# =============================================================================
class Solution(object):
    def canVisitAllRooms(self, rooms):
        """
        :type rooms: List[List[int]]
        :rtype: bool
        """
        visited = [0] * len(rooms)
        self.dfs(rooms, 0, visited)
        return sum(visited) == len(rooms)
        
    def dfs(self, rooms, index, visited):
        visited[index] = 1
        for key in rooms[index]:
            if not visited[key]:
                self.dfs(rooms, key, visited)





# =============================================================================
# Q5 Network Delay Time
# =============================================================================
class Solution(object):
    def networkDelayTime(self, times, N, K):
        aj_list = collections.defaultdict(list) 
        for u, v, w in times: 
            aj_list[u].append((w, v))
        
        dis = {} 
        pq = [(0, K)] 
        
        while pq:
            if len(dis)==N: break

            d, node = heapq.heappop(pq)
            if node in dis: continue

            dis[node] = d
            
            for d2, nb in aj_list[node]: 
                if nb not in dis: 
                    heapq.heappush(pq, (d+d2, nb)) 
                    
        return max(dis.values()) if len(dis)==N else -1 


# =============================================================================
# Q6 Remove Invalid Parentheses
# =============================================================================
class Solution(object):
    def removeInvalidParentheses(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        def dfs(s):
            mi = calc(s)
            if mi == 0:
                return [s]
            ans = []
            for x in range(len(s)):
                if s[x] in ('(', ')'):
                    ns = s[:x] + s[x+1:]
                    if ns not in visited and calc(ns) < mi:
                        visited.add(ns)
                        ans.extend(dfs(ns))
            return ans    
        def calc(s):
            a = b = 0
            for c in s:
                a += {'(' : 1, ')' : -1}.get(c, 0)
                b += a < 0
                a = max(a, 0)
            return a + b

        visited = set([s])    
        return dfs(s)

