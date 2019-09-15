/***********************************************
744. Find Smallest Letter Greater Than Target
***********************************************/

class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left{0};
        int n = letters.size();
        int right{n};
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(letters[mid] <= target)
                left = mid + 1;
            else
                right = mid;
        }
        return letters[right%n];
    }
};

/***********************************************
475. Heaters
***********************************************/

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        if(heaters.size() == 1)
            return max(abs(heaters.front() - houses.front()), abs(heaters.front() - houses.back()));
        int min_radius{0};
        int left{0};
        int right{1};
        for(int i{0}; i < houses.size() && right < heaters.size(); ++i) {
            if(houses[i] < heaters[left])
                min_radius = max(min_radius, heaters[left] - houses[i]);
            else if(houses[i] <= heaters[right])
                min_radius = max(min_radius, min(houses[i] - heaters[left], heaters[right] - houses[i] ));
            else
            {
                ++left;
                ++right;
                --i;
            }
        }
        if(right == heaters.size())
            min_radius = max(min_radius, abs(houses.back() - heaters.back()));
        return min_radius;
    }
};

/***********************************************
74. Search a 2D Matrix
***********************************************/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(!matrix.size() || !matrix[0].size())
            return false;
        int left{0};
        int n_rows = matrix.size();
        int n_cols = matrix[0].size();
        int right{n_rows * n_cols - 1};
        while(left <= right) {
            int mid = left + (right - left) / 2;
            int num = matrix[mid/n_cols][mid%n_cols];
            if(num == target)
                return true;
            else if(num < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return false;
    }
};

/***********************************************
34. Find First and Last Position of Element in Sorted Array
***********************************************/

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = static_cast<int>(nums.size());
        // Find first position
        int left{0};
        int right{n - 1};
        vector<int> result{-1, -1};
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] >= target)
                right = mid;
            else
                left = mid + 1;
        }
        if( n < 1 || nums[left] != target)
            return result;
        result[0] = left;
        
        // Find last position
        right = n - 1;
        while(left < right) {
            int mid = left + (right - left + 1) / 2;
            if(nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }
        result[1] = left;
        return result;
    }
};

/***********************************************
719. Find K-th Smallest Pair Distance
***********************************************/

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int left{0};
        int right{nums.back() - nums.front()};
        while(left < right) {
            int mid = (left + right) / 2;
            int count{0}; // # of pairs with distance <= mid
            for(int i{0}, j{0}; i < n; ++i) {
                while( j < n && nums[j] - nums[i] <= mid )
                    ++j;
                count += j - i - 1;
            }
            if(count < k)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
};

/***********************************************
Google. Min Max Gas Station Distance
***********************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;
class Interval
{
private:
    int len;
    int n_station;
    
public:
    Interval( int _len, int _n_station = 0) {
        len = _len;
        n_station = _n_station;
    }
    
    double distance() const{
        return len / (n_station + 1.0);
    }
    
    int get_len () const
    {
        return len;
    }
    
    int get_n_station() const
    {
        return n_station;
    }
    
    void add_station() {
        ++n_station;
    }
};

struct interval_comparator
{
    bool operator() (const Interval& x, const Interval& y) const
    {
        return x.distance() < y.distance();
    }
};

double min_max_distance( int, int, vector<int>);
void print_heap(priority_queue<Interval, vector<Interval>, interval_comparator>);

int main()
{
    int road_length{125};
    int n_stations{8};
    vector<int> locations{5, 8, 10, 25, 28, 31, 72, 80, 85, 100};
    cout << setprecision(2) << min_max_distance(road_length, n_stations, locations) << endl;
    return 0;
};

double min_max_distance( int road_length, int n_stations, vector<int> locations)
{
    priority_queue<Interval, vector<Interval>, interval_comparator> heap;
    if(locations.empty())
    {
        heap.push(Interval(road_length));
    }
    else
    {
        heap.push(Interval(locations[0]));
        for(int i{1}; i < locations.size(); ++ i )
        {
            heap.push(Interval(locations[i] - locations[i - 1]));
        }
        heap.push(Interval(road_length - locations.back()));
    }

    while(n_stations)
    {
        Interval longest_interval = heap.top();
        longest_interval.add_station();
        --n_stations;
        heap.pop();
        heap.push(longest_interval);
    }
    print_heap(heap);

    return heap.top().distance();
}

void print_heap( priority_queue<Interval, vector<Interval>, interval_comparator> heap )
{
    while(!heap.empty())
    {
        cout << "Interval length: " << heap.top().get_len() << " Number of gas stations: " << heap.top().get_n_station() << endl;
        heap.pop();
    }
}