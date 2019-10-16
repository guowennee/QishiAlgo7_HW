/**********************************************************************
 * 167. Two Sum II - Input array is sorted
 * ********************************************************************/

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        size_t left{0};
        size_t right{numbers.size() - 1};
        while(left < right)
        {
            int cur_sum = numbers[left] + numbers[right];
            if( cur_sum == target)
                break;
            else if(cur_sum < target)
                ++left;
            else
                --right;
        }
        return vector<int>{left + 1, right + 1};
    }
};

/**********************************************************************
 * 441. Arranging Coins
 * ********************************************************************/
class Solution {
public:
    int arrangeCoins(int n) {
        long left{0};
        long right{n};
        while(left < right)
        {
            long mid = (left + right + 1) / 2;
            if( (mid + 1) * mid / 2 <= n )
                left = mid;
            else
                right = mid - 1;
        }
        
        return static_cast<int>(left);
    }
};

/**********************************************************************
 * 912. Sort an Array
 * ********************************************************************/
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
private:
    void quickSort(vector<int>& nums, int left, int right)
    {
        if(left >= right) return;
        int p = partition(nums, left, right);
        quickSort(nums, left, p - 1);
        quickSort(nums, p + 1, right);
    }
    int partition(vector<int>& nums, int left, int right)
    {
        int i{left};
        int pivot = nums[right];
        for(int j{left}; j < right; ++j)
        {
            if(nums[j] < pivot)
                swap(nums[i++], nums[j]);
        }
        swap(nums[i], nums[right]);
        return i;
    }
};

/**********************************************************************
 * 973. K Closest Points to Origin
 * ********************************************************************/
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        priority_queue<vector<int>, vector<vector<int>>, compare> pq(points.begin(), points.end());
        vector<vector<int>> closest_k;
        while(closest_k.size() < K)
        {
            closest_k.push_back(pq.top());
            pq.pop();
        }
            
        return closest_k;
    }
private:
    struct compare {
       bool operator()(vector<int>& p, vector<int> q) {
           return p[0] * p[0] + p[1] * p[1] > q[0] * q[0] + q[1] * q[1];
       } 
    };
    
};

/**********************************************************************
 * 932. Beautiful Array
 * ********************************************************************/
class Solution {
public:
    vector<int> beautifulArray(int N) {
        vector<int> ba{1};
        while(ba.size() < N)
        {
            vector<int> temp;
            for(auto x: ba) temp.push_back(2 * x - 1);
            for(auto x: ba) temp.push_back(2 * x);
            ba = temp;
        }
        while(ba.size() > N)
            ba.pop_back();
        return ba;
    }
};

/**********************************************************************
 * 315. Count of Smaller Numbers After Self
 * ********************************************************************/
class Solution {
protected:
    void merge_countSmaller(vector<int>& indices, int first, int last, 
                            vector<int>& results, vector<int>& nums) {
        int count = last - first;
        if (count > 1) {
            int step = count / 2;
            int mid = first + step;
            merge_countSmaller(indices, first, mid, results, nums);
            merge_countSmaller(indices, mid, last, results, nums);
            vector<int> tmp;
            tmp.reserve(count);
            int idx1 = first;
            int idx2 = mid;
            int semicount = 0;
            while ((idx1 < mid) || (idx2 < last)) {
                if ((idx2 == last) || ((idx1 < mid) &&
                       (nums[indices[idx1]] <= nums[indices[idx2]]))) {
					tmp.push_back(indices[idx1]);
                    results[indices[idx1]] += semicount;
                    ++idx1;
                } else {
					tmp.push_back(indices[idx2]);
                    ++semicount;
                    ++idx2;
                }
            }
            move(tmp.begin(), tmp.end(), indices.begin()+first);
        }
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> results(n, 0);
        vector<int> indices(n, 0);
        iota(indices.begin(), indices.end(), 0);
        merge_countSmaller(indices, 0, n, results, nums);
        return results;
    }
};

/**********************************************************************
 * 327. Count of Range Sum
 * ********************************************************************/
class Solution {
public:
    int mergeSort(vector<long>& sum, int lower, int upper, int low, int high)
    {
        if(high-low <= 1) return 0;
        int mid = (low+high)/2, m = mid, n = mid, count =0;
        count =mergeSort(sum,lower,upper,low,mid) +mergeSort(sum,lower,upper,mid,high);
        for(int i =low; i< mid; i++)
        {
            while(m < high && sum[m] - sum[i] < lower) m++;
            while(n < high && sum[n] - sum[i] <= upper) n++;
            count += n - m;
        }
        inplace_merge(sum.begin()+low, sum.begin()+mid, sum.begin()+high);
        return count;
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int len = nums.size();
        vector<long> sum(len + 1, 0);
        for(int i =0; i< len; i++) sum[i+1] = sum[i]+nums[i];
        return mergeSort(sum, lower, upper, 0, len+1);
    }
};