/*********************************************
 * LC461. Hamming Distance
 *********************************************/
class Solution {
public:
    int hammingDistance(int x, int y) {
        int z = x ^ y;
        int count{0};
        while(z)
        {
            z = z & (z - 1);
            ++count;
        }
        
        return count;
    }
};

/*********************************************
 * LC190. Reverse Bits
 *********************************************/
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result{0};
        for(int i{0}; i < 32; ++i)
        {
            result = (result << 1) + ((n >> i) & 1);
        }
        
        return result;
    }
};

/*********************************************
 * LC421. Maximum XOR of Two Numbers in an Array
 *********************************************/
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int res = 0;
        unordered_set<int> pre;
        for (int i = 31; i >= 0; i--) {
            res <<= 1;
            pre.clear();
            for (auto n : nums) 
                pre.insert(n >> i);
            // if there are two prefixes tht (res + 1)^p1 = p2
            // then res + 1 = p1 ^ p2, we can get res + 1.
            for (auto p : pre)
                if (pre.find((res + 1) ^ p) != pre.end()) {
                    res++;
                    break;
                }
        }
        return res;
    }
};

/*********************************************
 * LC187. Repeated DNA Sequences
 *********************************************/
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if (s.size() <= 10)
            return vector<string>();
        
        unordered_map<char, int> char2val{{'A', 0}, {'G', 1}, {'C', 2}, {'T', 3}};

        vector<string> result;
        bitset<1<<20> seen;
        bitset<1<<20> added;

        int val = 0;
        for (int i{0}; i < 10; i++)
            val = (val << 2) | char2val[s[i]];
        seen.set(val);

        int mask = (1 << 20) - 1;
        for (int i{10}; i < s.size(); i++) {
            val = ((val << 2) & mask) | char2val[s[i]];  
            if (seen[val] && !added[val])
            {
                result.push_back(s.substr(i-9, 10));
                added.set(val);
            }   
            else
                seen.set(val);
        }
        return result;
    }

};

/*********************************************
 * LC201. Bitwise AND of Numbers Range
 *********************************************/
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        return (n > m) ? (rangeBitwiseAnd(m >> 1, n >> 1) << 1) : m;        
    }
};

/*********************************************
 * LC1178. Number of Valid Words for Each Puzzle
 *********************************************/
class Solution {
private:
    int getMask(string word) {
        int mask{0};
        for(auto c: word) {
            mask |= 1 << (c - 'a');
        }
        return mask;
    }
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int, int> count;
        for(auto word: words) {
            ++count[getMask(word)];
        }
        vector<int> nValid;
        for(auto puzzle: puzzles) {
            int n{0};
            int mask = getMask(puzzle);
            int firstMask = getMask(puzzle.substr(0, 1));
            for(auto word{mask}; word > 0; word = (word - 1) & mask) {
                if(word & firstMask) {
                    n += count[word];
                }
            }
            nValid.push_back(n);
        }
        
        return nValid;
    }

};