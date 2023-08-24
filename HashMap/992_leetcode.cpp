// 992. Subarrays with K Different Integers - Hard

// Given an integer array nums and an integer k, return the number of good subarrays of nums.
// A good array is an array where the number of different integers in that array is exactly k.
// For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
// A subarray is a contiguous part of an array.

// Example 1:

// Input: nums = [1,2,1,2,3], k = 2
// Output: 7
// Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
// Example 2:

// Input: nums = [1,2,1,3,4], k = 3
// Output: 3
// Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
 

// Constraints:

// 1 <= nums.length <= 2 * 104
// 1 <= nums[i], k <= nums.length

#include <bits/stdc++.h>
using namespace std;

int atMaxKDistinct(vector<int> &nums, int k) {
        unordered_map<int, int> numsFreq;
        int stIdx=0, res=0;

        for(int i=0;i<nums.size();i++) {
            numsFreq[nums[i]]++;

            while(numsFreq.size()>k) {
                numsFreq[nums[stIdx]]--;
                if(numsFreq[nums[stIdx]]==0)
                    numsFreq.erase(nums[stIdx]);
                stIdx++;
            }
            res += (i-stIdx+1);
        }
        return res;
    }

    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMaxKDistinct(nums, k) - atMaxKDistinct(nums, k-1);
    }