
/************************************************************
783. Minimum Distance Between BST Nodes
************************************************************/
class Solution {
public:
    int minDiffInBST(TreeNode* root) {
        int min_diff{INT_MAX};
        if(!root)
            return INT_MAX;
        if(root->left)
        {
            TreeNode* p{root->left};
            while(p->right)
                p = p->right;
            min_diff = min(root->val - p->val, min_diff);
        }
            
        if(root->right)
        {
            TreeNode* p{root->right};
            while(p->left)
                p = p->left;
            min_diff = min(p->val - root->val, min_diff);
            
        }
        min_diff = min(minDiffInBST(root->left), min_diff);
        min_diff = min(minDiffInBST(root->right), min_diff);
        return min_diff;
    }
};

/************************************************************
Reverse a Doubly linked list using recursion
************************************************************/

#include <vector>
#include<iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode* prev;
    ListNode* next;
    
    ListNode(int x) : val(x), prev(nullptr), next(nullptr){};
};
ListNode* push_back(ListNode* head, ListNode* new_node)
{
    if(!head)
        head = new_node;
    else
    {
        ListNode* curr{head};
        while(curr->next) curr = curr->next;
        curr->next = new_node;
        new_node->prev = curr;
    }
    return head;
}

ListNode* reverse(ListNode* head)
{
    if(!head || !head->next )
        return head;
    ListNode* result = reverse(head->next);
    ListNode* temp = head->next;
    temp->next = head;
    head->prev = temp;
    head->next = nullptr;
    
    return result;
}

void printList(ListNode* head)
{
    while(head)
    {
        cout << head->val << "->";
        head = head->next;
    }
    cout << "null" << endl;
}

int main()
{
    ListNode* head{nullptr};
    head = push_back(head, new ListNode(1));
    head = push_back(head, new ListNode(3));
    head = push_back(head, new ListNode(5));
    head = push_back(head, new ListNode(7));
    cout<< "Original linked list:" << endl;
    printList(head);
    head = reverse(head);
    cout<< "Reversed linked list:" << endl;
    printList(head);
    return 0;
};

/************************************************************
687. Longest Univalue Path
************************************************************/
class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        if(!root) return 0;
        
        int longestPath{0};
        longestPathFromRoot(root, longestPath);
        
        return longestPath;
    }
    
private:
    int longestPathFromRoot(TreeNode* root, int& longestPath) {
        // return the longest single value path starting from root
        // and update longest single value path in the whole tree as longestPath
        if(!root) return 0;
        int left_path = longestPathFromRoot(root->left, longestPath);
        int right_path = longestPathFromRoot(root->right, longestPath);
        int left_path_root = (root->left && root->val == root->left->val) ? left_path + 1 : 0;
        int right_path_root = (root->right && root->val == root->right->val) ? right_path + 1 : 0;
        longestPath = max(longestPath, left_path_root + right_path_root);
        
        return max(left_path_root, right_path_root);
    }
};

/************************************************************
698. Partition to K Equal Sum Subsets
************************************************************/
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for(int num:nums)sum+=num;
        if(k <= 0 || sum%k != 0)return false;
        vector<int> visited(nums.size(), 0);
        return canPartition(nums, visited, 0, k, 0, 0, sum/k);
    }
    
private:
    bool canPartition(vector<int>& nums, vector<int>& visited, int start_index, int k, int cur_sum,
                      int cur_num, int target)
    {
        if(k==1)return true;
        if(cur_sum == target && cur_num >0 )return canPartition(nums, visited, 0, k-1, 0, 0, target);
        for(int i = start_index; i<nums.size(); i++){
            if(!visited[i]){
                visited[i] = 1;
                if(canPartition(nums, visited, i+1, k, cur_sum + nums[i], cur_num++, target))
                    return true;
                visited[i] = 0;
            }
        }
        return false;
    }
};


/************************************************************
794. Valid Tic-Tac-Toe State
************************************************************/
class Solution {
public:
    bool validTicTacToe(vector<string> board)
    {
        int n_O{0};
        int n_X{0};
        for(int row{0}; row < 3; ++row)
        {
            for(auto col{0}; col < 3; ++col)
            {
                if(board[row][col] == 'O')
                    ++n_O;
                else if(board[row][col] == 'X')
                    ++n_X;
            }
        }
        if(n_O == n_X)
            return !checkWin(board, 'X');
        else if(n_O + 1 == n_X)
            return !checkWin(board, 'O');
        else
            return false;
    }
private:
    
    bool checkWin(vector<string> board, char player)
    {
        for(int row{0}; row < 3; ++row)
        {
            if(board[row][0] == player && board[row][1] == player && board[row][2] == player)
                return true;
        }
        for(int col{0}; col < 3; ++col)
        {
            if(board[0][col] == player && board[1][col] == player && board[2][col] == player)
                return true;
        }
        if(board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;
        if(board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;
        return false;
    }
};

/************************************************************
726. Number of Atoms
************************************************************/
class Solution {
public:
    string countOfAtoms(string formula)
    {
        map<string, int> count_map;
        countHelper(formula, count_map, static_cast<int>(formula.size()) - 1, 1);
        string result{""};
        for(auto p{count_map.begin()}; p != count_map.end(); ++p)
        {
            result.append(p->first);
            if(p->second > 1) result.append(intToStr(p->second));
        }
        return result;
    }
    
private:
    string intToStr(int num)
    {
        string result{""};
        while(num)
        {
            result.insert(result.begin(), num % 10 + '0');
            num /= 10;
        }
        return result;
    }
    int countHelper(string& formula, map<string, int>& count_map, int last, int times)
    {
        while(last >= 0 && formula[last] != '(')
        {
            int n{0};
            int multiplier{1};
            while(formula[last] >= '0' && formula[last] <= '9')
            {
                n += (formula[last] - '0') * multiplier;
                multiplier *= 10;
                --last;
            }
            n = max(n, 1);
            if(formula[last] == ')')
            {
                last = countHelper(formula, count_map, last - 1, n * times);
            }
            else
            {
                int atom_start{last};
                while(formula[atom_start] >= 'a' && formula[atom_start] <= 'z')
                    --atom_start;
                count_map[formula.substr(atom_start, last - atom_start + 1)] += n * times;
                last = atom_start - 1;
            }
        }
        return --last;
    }
};


