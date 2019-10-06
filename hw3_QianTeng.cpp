/***********************************
 * 111. Minimum Depth of Binary Tree
************************************/

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        queue<pair<TreeNode*, int>> nodes;
        nodes.push(make_pair(root, 1));
        while(!nodes.empty())
        {
            TreeNode* current = nodes.front().first;
            int depth = nodes.front().second;
            nodes.pop();
            if(!current->left && !current->right)
                return depth;
            if(current->left)
                nodes.push(make_pair(current->left, depth + 1));
            if(current->right)
                nodes.push(make_pair(current->right, depth + 1));
        }
        return -1;
    }
};

/***********************************
* 112. Path Sum
************************************/
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        stack<pair<TreeNode*, int>> nodes;
        nodes.push(make_pair(root, 0));
        while(!nodes.empty())
        {
            TreeNode* current = nodes.top().first;
            int current_sum = nodes.top().second + current->val;
            nodes.pop();
            if(!current->left && !current->right && current_sum == sum)
                return true;
            if(current->left)
                nodes.push(make_pair(current->left, current_sum));
            if(current->right)
                nodes.push(make_pair(current->right, current_sum));
        }
        return false;
    }
};

/***********************************
* 102. Binary Tree Level Order Traversal
************************************/
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> values;
        if(!root) return values;
        queue<pair<TreeNode*, int>> nodes;
        int level{0};
        vector<int> values_by_level;
        nodes.push(make_pair(root, level));
        while(!nodes.empty())
        {
            TreeNode* current = nodes.front().first;
            int current_level = nodes.front().second;
            nodes.pop();
            if(current_level != level)
            {
                level = current_level;
                values.push_back(values_by_level);
                values_by_level = vector<int>{current->val};
            }
            else
            {
                values_by_level.push_back(current->val);
            }
            if(current->left)
                nodes.push(make_pair(current->left, current_level + 1));
            if(current->right)
                nodes.push(make_pair(current->right, current_level + 1));
        }
        values.push_back(values_by_level);
        return values;        
    }
};

/***********************************
* 841. Keys and Rooms
************************************/

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n_notvisited = rooms.size();
        vector<bool> visited(n_notvisited, false);
        queue<int> room_queue;
        room_queue.push(0);
        while(!room_queue.empty())
        {
            int cur_room = room_queue.front();
            room_queue.pop();
            if(!visited[cur_room])
            {
                visited[cur_room] = true;
                --n_notvisited;
                if(n_notvisited == 0) return true;
                for(int key{0}; key < rooms[cur_room].size(); ++key)
                    room_queue.push(rooms[cur_room][key]);
            }

        }
        return n_notvisited == 0;
    }
};

/***********************************
* 743. Network Delay Time
************************************/

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<int> distance(N + 1, INT_MAX);
        distance[K] = 0;
        for(int i{0}; i < N -1; ++i )
        {
            for(auto time : times)
            {
                int u = time[0];
                int v = time[1];
                int w = time[2];
                if(distance[u] != INT_MAX && distance[v] > distance[u] + w)
                    distance[v] = distance[u] + w;
            }            
        }
        
        int travel_time{INT_MIN};
        for( int i{1}; i <= N; ++i)
        {
            if(distance[i] == INT_MAX) return -1;
            travel_time = max(travel_time, distance[i]);
        }
        
        return travel_time;
    }
};

/***********************************
* 301. Remove Invalid Parentheses
************************************/
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> output;
        removeHelper(s, output, 0, 0, false);
        return output;
    }

private:
    void removeHelper(string s, vector<string>& output, int i_start, int j_start, bool isReverse)
    {
        int count{0};
        char open_paren = isReverse ? ')' : '(';
        char close_paren = isReverse ? '(' : ')';
        for(int i{i_start}; i < s.size(); ++i)
        {
            if(s[i] == open_paren) count++;
            else if(s[i] == close_paren) count--;
            if(count < 0)
            {
                for(int j{j_start}; j <= i; ++j)
                {
                    if(s[j] == close_paren && (j == j_start || s[j-1] != close_paren))
                        removeHelper(s.substr(0, j) + s.substr(j+1, s.size() - j - 1),
                                     output, i, j, isReverse);
                }
                return;
            }
        }
        
        reverse(s.begin(), s.end());
        if(isReverse)
            output.push_back(s);
        else
            removeHelper(s, output, 0, 0, true);
    }
};


