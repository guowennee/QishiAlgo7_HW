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
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, multiset<string>> destinations;
        stack<string> airports;
        vector<string> itinerary;
        for(auto ticket : tickets)
            destinations[ticket[0]].insert(ticket[1]);
        airports.push("JFK");
        while(!airports.empty())
        {
            auto cur = airports.top();
            if(destinations[cur].empty())
            {
                airports.pop();
                itinerary.push_back(cur);
            }  
            else
            {
                string next = *destinations[cur].begin(); 
                destinations[cur].erase(destinations[cur].begin());
                airports.push(next);
            }
        }
        reverse(itinerary.begin(), itinerary.end());
        
        return itinerary;
    }
};

/***************************************************
 * 210. Course Schedule II
 * **************************************************/
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> childCourses(numCourses);
        vector<int> numParentCourse(numCourses);
        vector<int> rootCourses;
        vector<int> result;
        for(auto prerequisite : prerequisites)
        {
            childCourses[prerequisite[1]].push_back(prerequisite[0]);
            ++numParentCourse[prerequisite[0]];
        }
        for(int i{0}; i < numCourses; ++i)
        {
            if(!numParentCourse[i])
                rootCourses.push_back(i);
        }
        while(!rootCourses.empty())
        {
            int takeCourse = rootCourses.back();
            rootCourses.pop_back();
            result.push_back(takeCourse);
            for(int childCourse : childCourses[takeCourse])
                if(--numParentCourse[childCourse] == 0)
                    rootCourses.push_back(childCourse);
        }
        
        return result.size() == numCourses ? result : vector<int>();
    }
};

/***************************************************
 * 269. Alien Dictionary
 * **************************************************/
class Solution {
public:
    string alienOrder(vector<string>& words) {
        set<char> chars;
        unordered_map<char, set<char>> parent;
        unordered_map<char, set<char>> child;
        string first;
        for(auto word : words)
        {
            for(int i{0}; i < min(first.size(), word.size()); ++i)
            {
                if(first[i] != word[i])
                {
                    parent[word[i]].insert(first[i]);
                    child[first[i]].insert(word[i]);
                    break;
                }
            }
            chars.insert(word.begin(), word.end());
            first = word;
        }
        set<char> free(chars);
        string result;
        for(auto p : parent)
            free.erase(p.first);
        while(!free.empty())
        {
            char a = *free.begin();
            free.erase(a);
            result += a;
            for(char c : child[a])
            {
                parent[c].erase(a);
                if(parent[c].empty())
                    free.insert(c);
            }
        }
        
        return result.size() == chars.size() ? result : "";
    }
};

/***************************************************
 * 1136. Parallel Courses
 * **************************************************/
class Solution {
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        vector<int> nPre(N + 1);
        vector<vector<int>> child(N + 1);
        for(auto r : relations)
        {
            child[r[0]].push_back(r[1]);
            ++nPre[r[1]];
        }
        vector<int> free;
        for(int i{0}; i <= N; ++i)
        {
            if(!nPre[i])
                free.push_back(i);
        }
        int nSemsters{0};
        int taken{0};
        while(!free.empty())
        {
            ++nSemsters;
            taken += free.size();
            vector<int> nextFree;
            for(auto f : free)
            {
                for(auto c : child[f])
                {
                    if(--nPre[c] == 0) nextFree.push_back(c);
                }
            }
            free = nextFree;
        }
        
        return taken == N + 1 ? nSemsters : -1;
    }
};