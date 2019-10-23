/***************************************************
 * 1042. Flower Planting With No Adjacent
 * **************************************************/
class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        vector<vector<int>> adjacent(N);
        for(auto path : paths)
        {
            adjacent[path[0] - 1].push_back(path[1] - 1);
            adjacent[path[1] - 1].push_back(path[0] - 1);
        }
        vector<int> colors(N , 0);
        for(int i{0}; i < N; ++i)
        {
            vector<bool> used(5, false);
            for(auto garden : adjacent[i])
                used[colors[garden]] = true;
            for(auto j{1}; j <=4 ; ++j)
            {
                if(!used[j])
                {
                    colors[i] = j;
                    break;
                }
            }
        }
        
        return colors;
    }
};

/***************************************************
 * 133. Clone Graph
 * **************************************************/
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;
        queue<Node*> to_visit;
        unordered_map<Node*, Node*> copied;
        Node* copy = new Node(node->val, {});
        to_visit.push(node);
        copied[node] = copy;
        while(!to_visit.empty())
        {
            Node* cur = to_visit.front();
            to_visit.pop();
            for(auto neighbor : cur->neighbors)
            {
                if(copied.find(neighbor) == copied.end())
                {
                    copied[neighbor] = new Node(neighbor->val, {});
                    to_visit.push(neighbor);
                }
                copied[cur]->neighbors.push_back(copied[neighbor]);
            }
        }
        
        return copy;
    }
};

/***************************************************
 * 332. Reconstruct Itinerary
 * **************************************************/

/***************************************************
 * 210. Course Schedule II
 * **************************************************/

/***************************************************
 * 269. Alien Dictionary
 * **************************************************/

/***************************************************
 * 1136. Parallel Courses
 * **************************************************/