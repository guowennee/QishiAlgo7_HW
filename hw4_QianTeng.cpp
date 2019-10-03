/*************************************
 * 401. Binary Watch
*************************************/
class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> times;
        watchHelper(times, num, 0, 0 ,0); 
        return times;
    }
private:
    void watchHelper(vector<string>& times, int num, int hour, int minute, int next_pos)
    {
        vector<int> hour_chart{8, 4, 2, 1};
        vector<int> minute_chart{32, 16, 8, 4, 2, 1};
        if(num == 0)
        {
            stringstream ss;
            ss << hour << ':' << setw(2) << setfill('0') << minute;
            times.push_back(ss.str());
        }
        else
        {
            for(int i{next_pos}; i < hour_chart.size() + minute_chart.size(); ++i)
            {
                if(i < hour_chart.size())
                {
                    if(hour + hour_chart[i] < 12)
                        watchHelper(times, num - 1, hour + hour_chart[i], minute, i + 1);
                }
                else
                {
                    if(minute + minute_chart[i - hour_chart.size()] < 60)
                        watchHelper(times, num - 1, hour, minute + minute_chart[i - hour_chart.size()], i + 1);
                }
            }
        }
    }
};

/***************************************
 * 39. Combination Sum
 ************************************/
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> outputs;
        sort(candidates.begin(), candidates.end());
        reverse(candidates.begin(), candidates.end());
        combinationSumHepler(outputs, candidates, target, vector<int>(), 0);
        return outputs;
    }
private:
    void combinationSumHepler(vector<vector<int>>& outputs, vector<int> candidates, int target, vector<int> output, int start)
    {
        if(target == 0)
        {
            outputs.push_back(output);
            return;
        }
        for(int i{start}; i < candidates.size(); ++i)
        {
            if(target >= candidates[i])
            {
                target -= candidates[i];
                output.push_back(candidates[i]);
                combinationSumHepler(outputs, candidates, target, output, i);
                target += candidates[i];
                output.pop_back();                
            }            
        }
    }
};

/***************************************
 * 46. Permutations
 ************************************/
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> outputs;
        vector<int> output;
        vector<bool> visited(nums.size(), false);
        permuteHelper(outputs, nums, output, visited, 0);
        return outputs;
    }
    
private:
    void permuteHelper(vector<vector<int>>& outputs, vector<int>& nums, vector<int> output, vector<bool> visited, int n_visited)
    {
        if(n_visited == nums.size())
        {
            outputs.push_back(output);
            return;
        }
        for(int i{0}; i < visited.size(); ++i)
        {
            if(!visited[i])
            {
                visited[i] = true;
                output.push_back(nums[i]);
                permuteHelper(outputs, nums, output, visited, n_visited + 1);
                visited[i] = false;
                output.pop_back();
            }
        }
    }
};

/***************************************
 * 47. Permutations II
 ************************************/
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> outputs;
        vector<int> output;
        vector<bool> visited(nums.size(), false);
        permuteUniqueHelper(outputs, nums, output, visited, 0);
        return outputs;
    }
    
private:
    void permuteUniqueHelper(vector<vector<int>>& outputs, vector<int>& nums, vector<int> output, vector<bool> visited, int n_visited)
    {
        if(n_visited == nums.size())
        {
            outputs.push_back(output);
            return;
        }
        int last_visited{-1};
        for(int i{0}; i < visited.size(); ++i)
        {
            if(!visited[i] && (last_visited == -1 || nums[i] != nums[last_visited]))
            {
                visited[i] = true;
                output.push_back(nums[i]);
                permuteUniqueHelper(outputs, nums, output, visited, n_visited + 1);
                visited[i] = false;
                output.pop_back();
                last_visited = i;
            }
        }
    }
};

/***************************************
 * 52. N-Queens II
 ************************************/
class Solution {
public:
    int totalNQueens(int n) {
        vector<vector<bool>> board(n, vector<bool>(n, false));
        int solutions{0};
        totalNQueensHelper(board, solutions, 0);
        return solutions;
    }
private:
    // queens have been placed in column 0, ... col - 1
    // check if row, col is a safe position to place a queen
    bool isSafe(vector<vector<bool>> board, int row, int col)
    {
        for(int c{0}; c < col; ++c)
            if(board[row][c]) return false;
        for(int r{row}, c{col}; r >= 0 && c >= 0; --r, --c)
            if(board[r][c]) return false;
        for(int r{row}, c{col}; r < board.size() && c >= 0; ++r, --c)
            if(board[r][c]) return false;
        return true;
    }
    void totalNQueensHelper(vector<vector<bool>> board, int& solutions, int col)
    {
        if(col == board.size())
        {
            solutions++;
            return;
        }
        for(int row{0}; row < board.size(); ++row)
        {
            if(isSafe(board, row, col))
            {
                board[row][col] = true;
                totalNQueensHelper(board, solutions, col + 1);
                board[row][col] = false;
            }
        }
    }
};

/***************************************
 * 232. Implement Queue using Stacks
 ************************************/
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        while(!nums.empty())
        {
            numsHelper.push(nums.top());
            nums.pop();            
        }
        nums.push(x);
        while(!numsHelper.empty())
        {
            nums.push(numsHelper.top());
            numsHelper.pop();                 
        }
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int num = nums.top();
        nums.pop();
        return num;
    }
    
    /** Get the front element. */
    int peek() {
        return nums.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return nums.empty();
    }
private:
    stack<int> numsHelper;
    stack<int> nums;
};
