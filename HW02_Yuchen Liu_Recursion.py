# =============================================================================
# Q1 Minimum Distance Between BST Nodes
# =============================================================================

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
class Solution:
    def minDiffInBST(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        vals = []
        def inOrder(root):
            if not root:
                return 
            inOrder(root.left)
            vals.append(root.val)
            inOrder(root.right)
        inOrder(root)
        return min([vals[i + 1] - vals[i] for i in xrange(len(vals) - 1)])

# =============================================================================
# Q2 Reverse a Doubly linked list using recursion
# =============================================================================
# A node of the doublly linked list 
#class Node: 
#      
#    # Constructor to create a new node 
#    def __init__(self, data): 
#        self.data = data  
#        self.next = None
#        self.prev = None
  
class DoublyLinkedList: 
     # Constructor for empty Doubly Linked List 
    def __init__(self): 
        self.head = None
   
    # Function reverse a Doubly Linked List 
    def reverse(self): 
        temp = None
        current = self.head 
          
        # Swap next and prev for all nodes of  
        # doubly linked list 
        while current is not None: 
            temp = current.prev  
            current.prev = current.next
            current.next = temp 
            current = current.prev 
  
        # Before changing head, check for the cases like  
        # empty list and list with only one node 
        if temp is not None: 
            self.head = temp.prev 
            
            
            
    # Given a reference to the head of a list and an 
    # integer,inserts a new node on the front of list 
    def push(self, new_data): 
   
        # 1. Allocates node 
        # 2. Put the data in it 
        new_node = Node(new_data) 
   
        # 3. Make next of new node as head and 
        # previous as None (already None) 
        new_node.next = self.head 
   
        # 4. change prev of head node to new_node 
        if self.head is not None: 
            self.head.prev = new_node 
   
        # 5. move the head to point to the new node 
        self.head = new_node 
  
  
    def printList(self, node): 
        while(node is not None): 
            print (node.data)
            node = node.next
            
            
            
# Driver program to test the above functions 
dll = DoublyLinkedList() 
dll.push(2); 
dll.push(4); 
dll.push(8); 
dll.push(10); 
  
print ("\nOriginal Linked List")
dll.printList(dll.head) 
  
# Reverse doubly linked list 
dll.reverse() 
  
print ("\n Reversed Linked List")
dll.printList(dll.head)               





# =============================================================================
# Q3 Longest Univalue Path
# =============================================================================
class Solution:
    def longestUnivaluePath(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        self.max_path=0
        def TreeDepth(root):
            left_depth=0
            right_depth=0
            if root.left:
                left_depth=TreeDepth(root.left)
                if root.left.val!=root.val:
                    left_depth=0
            if root.right:
                right_depth=TreeDepth(root.right)
                if root.right.val!=root.val:
                    right_depth=0
            self.max_path=max(self.max_path,left_depth+right_depth)
            return max(left_depth,right_depth)+1
        if root:
            TreeDepth(root)
        return self.max_path

# =============================================================================
# Q4 Partition to K Equal Sum Subsets
# =============================================================================
class Solution:
    def canPartitionKSubsets(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        if not nums or len(nums) < k: return False
        _sum = sum(nums)
        div, mod = divmod(_sum, k)
        if _sum % k or max(nums) > _sum / k: return False
        nums.sort(reverse = True)
        target = [div] * k
        return self.dfs(nums, k, 0, target)
        
    def dfs(self, nums, k, index, target):
        if index == len(nums): return True
        num = nums[index]
        for i in range(k):
            if target[i] >= num:
                target[i] -= num
                if self.dfs(nums, k, index + 1, target): return True
                target[i] += num
        return False
        
    
# =============================================================================
# Q5 Valid Tic-Tac-Toe State
# =============================================================================

class Solution:
    def validTicTacToe(self, board):
        """
        :type board: List[str]
        :rtype: bool
        """
        xCount, oCount = 0, 0
        for i in range(3):
            for j in range(3):
                if board[i][j] == 'O':
                    oCount += 1
                elif board[i][j] == 'X':
                    xCount += 1
        if oCount != xCount and oCount != xCount - 1: return False
        if oCount != xCount and self.win(board, 'O'): return False
        if oCount != xCount - 1 and self.win(board, 'X'): return False
        return True
        
    def win(self, board, P):
        # board is list[str]
        # P is 'X' or 'O' for two players
        for j in range(3):
            if all(board[i][j] == P for i in range(3)): return True
            if all(board[j][i] == P for i in range(3)): return True
        if board[0][0] == board[1][1] == board[2][2] == P: return True
        if board[0][2] == board[1][1] == board[2][0] == P: return True
        return False
  
    
    
    
    
# =============================================================================
# Q6 Number of Atoms    
# =============================================================================
class Solution:
    def findGroup(self, formula):
        cnt = 1
        for x in range(1, len(formula)):
            if formula[x] == '(': cnt += 1
            elif formula[x] == ')': cnt -= 1
            if cnt == 0: return formula[:x+1], formula[x+1:]
    
    def findAtom(self, formula):
        upper = 0
        for x in range(len(formula)):
            if formula[x].isupper(): upper += 1
            if upper > 1 or not formula[x].isalpha():
                return formula[:x], formula[x:]
        return formula, ''
    
    def findNum(self, formula):
        for x in range(len(formula)):
            if not formula[x].isdigit():
                return int(formula[:x]), formula[x:]
        return int(formula), ''

    def count(self, formula):
        cnt = collections.Counter()
        while formula:
            if formula[0] == '(':
                group, formula = self.findGroup(formula)
                groupCnt = self.count(group[1:-1])
                num = 1
                if formula and formula[0].isdigit():
                    num, formula = self.findNum(formula)
                for k, v in groupCnt.iteritems():
                    cnt[k] += num * v
            else:
                atom, formula = self.findAtom(formula)
                num = 1
                if formula and formula[0].isdigit():
                    num, formula = self.findNum(formula)
                cnt[atom] += num
        return cnt

    def countOfAtoms(self, formula):
        """
        :type formula: str
        :rtype: str
        """
        cnt = self.count(formula)
        return ''.join(k + str(cnt[k] > 1 and cnt[k] or '') for k in sorted(cnt))
    
    
    
    


